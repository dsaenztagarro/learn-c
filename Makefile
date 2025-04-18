DOCKER_USER ?= "dsaenztagarro"
IMAGE = "$(DOCKER_USER)/dev-env-c" # docker image
CONTAINER = "devenv-c" # docker container

CURRENT_DIR := $(shell pwd)

.PHONY: docker_image CONTAINER docker_pause docker_unpause \
				docker_terminal docker_clean

docker_image:
	@echo "  Building image $(IMAGE)..."
	@docker build -t $(IMAGE) .
# -q , quiet

docker_container: docker_image
	@echo "  Starting container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/workdir" -it $(IMAGE)
# ^
# --rm ,    Automatically remove the container and its associated anonymous volumes when it exits
# -v list , Bind mount a volume
# -p list , Publish a container port to the host (i.e. GDB port)
# -i ,      Keep STDIN open even if not attached (--interactive).
# -t ,      Allocate a pseudo-TTY (--tty).

docker_start:
	@echo "  Starting detached container $(CONTAINER)..."
	@docker run --detach --name $(CONTAINER) --rm -v "$(CURRENT_DIR):/home/dev/workdir" -it $(IMAGE)

docker_stop:
	@echo "  Stopping container $(CONTAINER)..."
	@docker stop $(CONTAINER) || true
	@echo "  Removing container $(CONTAINER)..."
	@docker rm $(CONTAINER) || true

docker_terminal:
	@echo "  Starting terminal on existing container $(CONTAINER)..."
	@docker exec -it $(CONTAINER) /bin/bash

docker_pause:
	@echo "  Pausing container $(CONTAINER)..."
	@docker pause $(CONTAINER)

docker_unpause:
	@echo "  Unpausing container $(CONTAINER)..."
	@docker unpause $(CONTAINER)

docker_clean: docker_stop
	@echo "  Removing image $(IMAGE_NAME)..."
	@docker rmi $(IMAGE):latest || true
	@echo "Cleanup complete."
