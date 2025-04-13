DOCKER_USER ?= "dsaenztagarro"
DOCKER_IMAGE = "ubuntu24.04-c"
DOCKER_CONTAINER = "devenv-c"

CURRENT_DIR := $(shell pwd)

.PHONY: third_party docker_image docker_container clean

third_party:
	@echo " Cleaning third_party folder"
	@rm -rf third_party
	@mkdir third_party
	@touch third_party/.gitkeep
	@echo " Copy starship.toml to third_party folder"
	@cp ~/.config/starship.toml third_party/starship.toml
	@echo " Copy NeoVim config to third_party folder"
	@cp -rf ~/.config/nvim third_party/nvim/
# @echo "Copy Nerd Font"
# @cp -rf ~/.config/nvim third_party/nvim/

docker_image: third_party
	@echo "  Building image $(DOCKER_IMAGE)..."
	@docker build -t $(DOCKER_USER)/$(DOCKER_IMAGE) .

docker_container: docker_image
	@echo "  Starting container $(DOCKER_CONTAINER)..."
	@docker run --name $(DOCKER_CONTAINER) --rm -v "$(CURRENT_DIR):/home/devuser/workdir" -p 2345:2345 -it $(DOCKER_USER)/$(DOCKER_IMAGE)
# ^
# --rm ,    Automatically remove the container and its associated anonymous volumes when it exits
# -v list , Bind mount a volume
# -p list , Publish a container port to the host (i.e. GDB port)
# -i ,      Keep STDIN open even if not attached (--interactive).
# -t ,      Allocate a pseudo-TTY (--tty).

docker_terminal:
	@echo "  Starting terminal on existing container $(DOCKER_CONTAINER)..."
	@docker exec -it $(DOCKER_CONTAINER) /bin/bash

docker_pause:
	@echo "  Pausing container $(DOCKER_CONTAINER)..."
	@docker pause $(DOCKER_CONTAINER)

docker_unpause:
	@echo "  Unpausing container $(DOCKER_CONTAINER)..."
	@docker unpause $(DOCKER_CONTAINER)

docker_clean:
	@echo "  Stopping container $(DOCKER_CONTAINER)..."
	@docker stop $(DOCKER_CONTAINER) || true
	@echo "  Removing container $(DOCKER_CONTAINER)..."
	@docker rm $(DOCKER_CONTAINER) || true
	@echo "  Removing image $(IMAGE_NAME)..."
	@docker rmi $(DOCKER_IMAGE) || true
	@echo "Cleanup complete."
