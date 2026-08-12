DOCKER_USER ?= "dsaenztagarro"
IMAGE = "$(DOCKER_USER)/dev-env-c" # docker image
CONTAINER = "dev-env-c" # docker container

CURRENT_DIR := $(shell pwd)

.PHONY: all linux test check-errors clean \
				image container start stop terminal rmi pause unpause \
				release analyze

##############################################################################
# BUILD
#
# Design: one shared skeleton, per-book overrides — never one rigid flag set,
# never a Makefile per book. The doctrine and its rationale live in the sibling
# repo ~/Code/learn-repo (referenced below as ../learn-repo/…): see
# ../learn-repo/STANDARD.md §7 and ../learn-repo/docs/guides/build.md.
#
#   * Books are DISCOVERED, not listed: drop a new src/<book>/ folder and it is
#     picked up automatically.
#   * Common flags live in BASE_CFLAGS. A book only appears below if it needs
#     DIFFERENT flags — via GNU make *pattern-specific variables* keyed on its
#     bin/<book>/ output path. Books with no override (deitel, udemy) just use
#     the default. Today only two books genuinely differ: K&R (strict ANSI) and
#     Linux (glibc/TLPI).
#   * Portable books build by default (`make all`, green on any host); the one
#     platform-bound book (src/linux) is opt-in (`make linux`), because
#     portability is tiered (../learn-repo/docs/guides/portability.md).
##############################################################################

CC = gcc

# BASE_CFLAGS: flags shared by every book. -I src/shared so any unit can
# `#include "kr_util.h"` — that header is the repo's shared library glue and
# lives in src/shared/, not next to the units that use it.
BASE_CFLAGS = -Wall -g -I$(SRC_DIR)/shared

# Default standard for a book with no override below.
CFLAGS = $(BASE_CFLAGS) -std=c11

# LDLIBS — libraries handed to the linker (ld). -lm is the math library.
#   It costs nothing when unused: the linker only pulls object code for symbols
#   a program actually references, so linking -lm into a unit that never calls
#   a <math.h> function leaves the executable unchanged.
LDLIBS = -lm

SRC_DIR   = src
BIN_DIR   = bin
BUILD_DIR = build

# --- Book discovery (source-first tree; ../learn-repo/STANDARD.md §1) --------
# $(wildcard src/*) expands to the book directories (src/deitel, src/kr, …).
# $(filter-out …) drops src/shared, which is library glue, not a book.
#   Wildcards expand automatically inside rules, but NOT when a variable is set,
#   so we call the wildcard *function* explicitly here.
#   https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
BOOK_DIRS := $(filter-out $(SRC_DIR)/shared,$(wildcard $(SRC_DIR)/*))

# Every unit across every book, minus the intentional-error demos.
#   $(addsuffix /*.c,…) turns "src/kr" into "src/kr/*.c"; the outer wildcard
#   then expands those globs. $(filter-out %.err.c,…) removes the *.err.c files,
#   which are meant to FAIL to compile (see check-errors below).
#   https://www.gnu.org/software/make/manual/html_node/Text-Functions.html
ALL_SRC := $(filter-out %.err.c,$(wildcard $(addsuffix /*.c,$(BOOK_DIRS))))

# Split portable (Tier 1: any C compiler, any OS) from the one platform-bound
# book. src/linux uses glibc-only headers (<gnu/libc-version.h>) and the TLPI
# library, so it is separated out and excluded from the default build.
PLATFORM_DIR := $(SRC_DIR)/linux
PORTABLE_SRC := $(filter-out $(PLATFORM_DIR)/%,$(ALL_SRC))
PLATFORM_SRC := $(filter     $(PLATFORM_DIR)/%,$(ALL_SRC))

# Map each src/<book>/<unit>.c to its bin/<book>/<unit> executable.
#   $(patsubst pattern,replacement,text): the % matches across the slash, so
#   src/kr/kr_101_hello_world.c becomes bin/kr/kr_101_hello_world.
PORTABLE_BIN := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(PORTABLE_SRC))
PLATFORM_BIN := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(PLATFORM_SRC))

# --- Per-book flag overrides (pattern-specific variables) --------------------
# A pattern-specific variable applies to every target matching the pattern, so
# these give a whole book its own flags without a separate Makefile or any
# per-file special-casing. A book not named here simply uses the default CFLAGS.
#   https://www.gnu.org/software/make/manual/html_node/Pattern_002dspecific.html
#
# K&R predates POSIX and reimplements getline()/strdup() itself. Build it as
# strict ANSI C and add -D_ANSI_SOURCE, which asks the platform's headers to
# hide those POSIX names so the book's own versions don't clash with libc.
# (On glibc -std=c89 already hides them; -D_ANSI_SOURCE is what makes it work on
# macOS/BSD too — a portable, per-book flag, not a per-unit patch.)
$(BIN_DIR)/kr/%    : CFLAGS = $(BASE_CFLAGS) -std=c89 -D_ANSI_SOURCE

# The Linux book uses glibc/TLPI extensions (Tier 3; built via `make linux`).
$(BIN_DIR)/linux/% : CFLAGS  = $(BASE_CFLAGS) -std=gnu11 -D_GNU_SOURCE -I$(TLPI_INC)
$(BIN_DIR)/linux/% : LDLIBS += $(TLPI_LIB)

# The Linux book's TLPI (The Linux Programming Interface) helpers live in the
# sibling repo learn-linux. Override on the CLI if it's elsewhere:
#   make linux TLPI_DIR=/path/to/learn-linux
TLPI_DIR ?= $(HOME)/Code/learn-linux
TLPI_INC  = $(TLPI_DIR)/lib
TLPI_LIB  = $(TLPI_DIR)/libtlpi.a

# --- Shared library glue -----------------------------------------------------
# src/shared/kr_util.c is compiled once into one object and linked ONLY into the
# units that #include it (LINK_UTIL below), so self-contained units don't drag
# it in. UTIL_USERS is discovered by grepping for the include — no hand-kept
# list to fall out of date.
UTIL_OBJ = $(BUILD_DIR)/kr_util.o
UTIL_USERS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,\
                $(shell grep -lR --include='*.c' 'kr_util\.h' $(SRC_DIR) 2>/dev/null | grep -v '/shared/'))
# Target-specific variable + prerequisite: only these targets see LINK_UTIL set
# and depend on the object.
$(UTIL_USERS): LINK_UTIL = $(UTIL_OBJ)
$(UTIL_USERS): $(UTIL_OBJ)

# --- Targets -----------------------------------------------------------------
# Default: the portable books. Green on any C compiler, any OS.
all: $(PORTABLE_BIN)

# Opt-in: the Linux/glibc-only book. Meant for the dev-env Docker container;
# won't compile natively on macOS (glibc headers), and the fileio unit needs the
# external TLPI library. See ../learn-repo/docs/guides/portability.md (Tier 3).
linux:
	@echo ">> src/linux/ is Linux/glibc-bound (Tier 3): build inside the dev-env container."
	@echo ">> The fileio unit also needs $(TLPI_LIB) (from ~/Code/learn-linux)."
	@$(MAKE) --no-print-directory $(PLATFORM_BIN)

# Pattern rule: compile + link one unit into bin/<book>/<unit>.
#   $<        the first prerequisite  (the .c source)
#   $@        the target              (the executable)
#   $(@D)     the target's directory  — made on demand so bin/<book>/ exists
#   $(CFLAGS) resolves to the book's pattern-specific value (set above)
#   LINK_UTIL the shared object, but only for the units that use it (else empty)
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $< $(LINK_UTIL) $(LDLIBS)

# The shared helper is K&R code, so it compiles with the same strict-ANSI flags
# as the kr book. The order-only prerequisite `| $(BUILD_DIR)` guarantees the
# directory exists without forcing a rebuild whenever its timestamp changes.
#   https://www.gnu.org/software/make/manual/html_node/Prerequisite-Types.html
$(UTIL_OBJ): $(SRC_DIR)/shared/kr_util.c $(SRC_DIR)/shared/kr_util.h | $(BUILD_DIR)
	$(CC) $(BASE_CFLAGS) -std=c89 -D_ANSI_SOURCE -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

# --- Checks (../learn-repo/STANDARD.md §7's second verb) ---------------------
# Build everything, confirm the intentional-error demos still fail to compile,
# and smoke-run a unit that needs no input.
ERR_SRC = $(wildcard $(SRC_DIR)/*/*.err.c)

check-errors:
	@echo "Verifying intentional-error units still fail to compile..."
	@for f in $(ERR_SRC); do \
		if $(CC) $(BASE_CFLAGS) -std=c11 -fsyntax-only $$f >/dev/null 2>&1; then \
			echo "  UNEXPECTED: $$f compiled but should fail"; exit 1; \
		else echo "  ok (fails as intended): $$f"; fi; \
	done

test: all check-errors
	@echo "Smoke-running bin/kr/kr_101_hello_world:"
	@./$(BIN_DIR)/kr/kr_101_hello_world
	@echo "OK: portable build + error demos + smoke run."

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

##############################################################################
# DOCKER TASKS
##############################################################################

image:
	@echo "  Building image $(IMAGE)..."
	@docker build -t $(IMAGE) .
# -q , quiet

container: image
	@echo "  Starting container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/wokrdir" -it $(IMAGE)
# ^
# --rm ,    Automatically remove the container and its associated anonymous volumes when it exits
# -v list , Bind mount a volume
# -p list , Publish a container port to the host (i.e. GDB port)
# -i ,      Keep STDIN open even if not attached (--interactive).
# -t ,      Allocate a pseudo-TTY (--tty).

start:
	@echo "  Starting detached container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/wokrdir" -it $(IMAGE)

stop:
	@echo "  Stopping container $(CONTAINER)..."
	@docker stop $(CONTAINER) || true
	@echo "  Removing container $(CONTAINER)..."
	@docker rm $(CONTAINER) || true

terminal:
	@echo "  Starting terminal on running container $(CONTAINER)..."
	@docker exec -it $(CONTAINER) /bin/bash

pause:
	@echo "  Pausing container $(CONTAINER)..."
	@docker pause $(CONTAINER)

unpause:
	@echo "  Unpausing container $(CONTAINER)..."
	@docker unpause $(CONTAINER)

rmi: stop
	@echo "  Removing image $(IMAGE_NAME)..."
	@docker rmi $(IMAGE):latest || true
	@echo "Cleanup complete."

# make release DOCKER_VERSION=1.0.2
release:
	@git tag -f $(DOCKER_VERSION) head
	@docker tag $(IMAGE):latest $(IMAGE):$(DOCKER_VERSION)
	@docker push -f $(IMAGE):$(DOCKER_VERSION)

analyze:
	@echo "  Analyzing..."
	@docker scout quickview
	@docker scout cves local://dsaenztagarro/dev-env-c:latest
