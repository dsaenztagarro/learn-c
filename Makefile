DOCKER_USER ?= "dsaenztagarro"
IMAGE = "$(DOCKER_USER)/dev-env-c" # docker image
CONTAINER = "dev-env-c" # docker container

CURRENT_DIR := $(shell pwd)

.PHONY: all clean \
				image container start stop terminal rmi pause unpause \
				release analyze

# Compiler and flags
CC = gcc
CFLAGS = -std=c89 -Wall -g

# Directories
SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build

LDLIBS = -lm
# ^ Libraries to pass to the linker/loader
# 	The name comes from traditional Unix build tool terminology,
# 	where "ld" is the name of the system linker/loader program.
#
# 	What Happens If You Link a Library But Don't Use It?
# 	If you add -lm (or any other -l<lib>) to your linker command but your
# 	program does not use any functions or symbols from that library:
#
# 	Static Libraries:
# 	The linker will not include any code from the library in your executable,
# 	so the size of your executable will not increase. The linker only pulls in
# 	object code for symbols that are actually referenced by your program.
#
# 	Shared Libraries:
# 	The executable will have a reference to the shared library, but if no
# 	symbols are used, there is no practical impact on size or runtime.
# 	The dynamic linker may still note the dependency,
# 	but it has negligible effect if unused.

# LDFLAGS = ...
# ^ For linker flags that are not libraries (like -L for library search paths
# 	or other linker options)

# Automatically detect all source files and their target executables
SRC_FILES = $(filter-out %.err.c $(SRC_DIR)/kr_util.c, $(wildcard $(SRC_DIR)/*.c))
#																                              ^
# 	                $(wildcard pattern…)
# 	                Wildcard expansion happens automatically in rules. But wildcard
# 	                expansion does not normally take place when a variable is set,
# 	                or inside the arguments of a function. If you want to do wildcard
# 	                expansion in such places, you need to use the wildcard function
#
#                   4.4.3 The Function wildcard
#               		https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
#
#           ^
#   $(filter-out pattern…,text)
#   Returns all whitespace-separated words in text that do not match any of
#   the pattern words, removing the words that do match one or more.
#   This is the exact opposite of the filter function.
#
#	  8.2 Functions for String Substitution and Analysis
#   https://www.gnu.org/software/make/manual/html_node/Text-Functions.html

TARGETS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC_FILES))
#           ^ $(patsubst pattern,replacement,text)
#             Finds whitespace-separated words in text that match pattern and
#             replaces them with replacement. Here pattern may contain a ‘%’
#             which acts as a wildcard, matching any number of any characters
#             within a word.
#             If replacement also contains a ‘%’, the ‘%’ is replaced by the text
#             that matched the ‘%’ in pattern. Words that do not match the
#             pattern are kept without change in the output. Only the first ‘%’
#             in the pattern and replacement is treated this way; any subsequent
#             ‘%’ is unchanged.
#
#           	8.2 Functions for String Substitution and Analysis
#           	https://www.gnu.org/software/make/manual/html_node/Text-Functions.html

UTIL_OBJ = $(BUILD_DIR)/kr_util.o


# Default target: build all executables
all: $(TARGETS)

# Pattern rule to build each executable
$(BIN_DIR)/%: $(SRC_DIR)/%.c $(UTIL_OBJ) | $(BIN_DIR)
#                                          ^
#                        order-only-prerequisites: ensure a prerequisite
#                        exists before building a target but do not trigger
#                        rebuilds if the prerequisite changes.
#                        Purpose: Avoid unnecessary rebuilds caused by
#                        timestamp changes (e.g., directories updating when
#                        files are added).
#
	$(CC) $(CFLAGS) -o $@ $< $(UTIL_OBJ) $(LDLIBS);
#                     	^ refers to the first prerequisite in the list
#                     		represents the source file path (src/foo.c)
#                  	 ^ represents the target file path (bin/foo)


$(UTIL_OBJ): $(SRC_DIR)/kr_util.c $(SRC_DIR)/kr_util.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
#                    ^

$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

##############################################################################
# DOCKER TASKS
##############################################################################

image:
	@echo "  Building image $(IMAGE)..."
	@docker build -t $(IMAGE) .
# -q , quiet

container: image
	@echo "  Starting container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/wokrdir" -it $(IMAGE)
# ^
# --rm ,    Automatically remove the container and its associated anonymous volumes when it exits
# -v list , Bind mount a volume
# -p list , Publish a container port to the host (i.e. GDB port)
# -i ,      Keep STDIN open even if not attached (--interactive).
# -t ,      Allocate a pseudo-TTY (--tty).

start:
	@echo "  Starting detached container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/wokrdir" -it $(IMAGE)

stop:
	@echo "  Stopping container $(CONTAINER)..."
	@docker stop $(CONTAINER) || true
	@echo "  Removing container $(CONTAINER)..."
	@docker rm $(CONTAINER) || true

terminal:
	@echo "  Starting terminal on running container $(CONTAINER)..."
	@docker exec -it $(CONTAINER) /bin/bash

pause:
	@echo "  Pausing container $(CONTAINER)..."
	@docker pause $(CONTAINER)

unpause:
	@echo "  Unpausing container $(CONTAINER)..."
	@docker unpause $(CONTAINER)

rmi: stop
	@echo "  Removing image $(IMAGE_NAME)..."
	@docker rmi $(IMAGE):latest || true
	@echo "Cleanup complete."

# make release DOCKER_VERSION=1.0.2
release:
	@git tag -f $(DOCKER_VERSION) head
	@docker tag $(IMAGE):latest $(IMAGE):$(DOCKER_VERSION)
	@docker push -f $(IMAGE):$(DOCKER_VERSION)

analyze:
	@echo "  Analyzing..."
	@docker scout quickview
	@docker scout cves local://dsaenztagarro/dev-env-c:latest
