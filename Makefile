DOCKER_USER ?= "dsaenztagarro"
IMAGE = "$(DOCKER_USER)/dev-env-c" # docker image
CONTAINER = "dev-env-c" # docker container

CURRENT_DIR := $(shell pwd)

.PHONY: image container start stop terminal clean pause unpause \
				release analyze

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

clean: stop
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
