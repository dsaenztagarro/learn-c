DOCKER_USER ?= "dsaenztagarro"
DOCKER_IMAGE = "ubuntu24.04-c"
DOCKER_CONTAINER = "devenv-c"

CURRENT_DIR := $(shell pwd)

.PHONY: third_party docker_image docker_container clean

third_party:
	@echo "Copy starship.toml to third_party folder"
	cp ~/.config/starship.toml third_party/starship.toml

docker_image: third_party
	@echo "Building image $(DOCKER_IMAGE)..."
	docker build -t $(DOCKER_USER)/$(DOCKER_IMAGE) .

docker_container: docker_image
	@echo "Starting container $(DOCKER_CONTAINER)..."
	docker run --name $(DOCKER_CONTAINER) --rm -v "$(CURRENT_DIR):/home/devuser/workdir" -it $(DOCKER_USER)/$(DOCKER_IMAGE)
# ^
# [--rm]    Automatically remove the container and its associated anonymous volumes when it exits
# [-v list] Bind mount a volume
# [-i]      Keep STDIN open even if not attached (--interactive).
# [-t]      Allocate a pseudo-TTY (--tty).

clean:
	@echo "Stopping container $(DOCKER_CONTAINER)..."
	docker stop $(DOCKER_CONTAINER) || true
	@echo "Removing container $(DOCKER_CONTAINER)..."
	docker rm $(DOCKER_CONTAINER) || true
	@echo "Removing image $(IMAGE_NAME)..."
	docker rmi $(IMAGE_NAME) || true
	@echo "Cleanup complete."
