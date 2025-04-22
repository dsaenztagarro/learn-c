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

# Automatically detect all source files and their target executables
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
#             ^ $(wildcard pattern…)
#               Wildcard expansion happens automatically in rules. But wildcard
#               expansion does not normally take place when a variable is set,
#               or inside the arguments of a function. If you want to do wildcard
#               expansion in such places, you need to use the wildcard function
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


# Default target: build all executables
all: $(TARGETS)

# Pattern rule to build each executable
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<
#                       ^ represents the source file path (src/foo.c)
#                    ^ represents the target file path (bin/foo)

clean:
	rm -rf $(BIN_DIR)

##############################################################################
# DOCKER TASKS
##############################################################################

image:
	@echo "  Building image $(IMAGE)..."
	@docker build -t $(IMAGE) .
# -q , quiet

container: image
	@echo "  Starting container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/workdir" -it $(IMAGE)
# ^
# --rm ,    Automatically remove the container and its associated anonymous volumes when it exits
# -v list , Bind mount a volume
# -p list , Publish a container port to the host (i.e. GDB port)
# -i ,      Keep STDIN open even if not attached (--interactive).
# -t ,      Allocate a pseudo-TTY (--tty).

start:
	@echo "  Starting detached container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/workdir" -it $(IMAGE)

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
