FROM ubuntu:24.04

# https://hub.docker.com/_/ubuntu
RUN apt-get update
RUN apt-get install -y locales
RUN apt-get install -y build-essential # provides C headers, and dev tools
RUN apt-get install -y curl git gdb gcc
RUN apt-get install -y vim # provides vim shortcuts to shell
RUN rm -rf /var/lib/apt/lists/*
RUN localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8


## Permissions

# Create a non-root user
RUN useradd -m -s /bin/bash devuser && \
    echo "devuser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Switch to non-root user
USER devuser

# Create a subfolder inside /home/devuser and set permissions
RUN mkdir -p /home/devuser/.config && chown -R devuser:devuser /home/devuser/.config
RUN mkdir -p /home/devuser/workdir && chown -R devuser:devuser /home/devuser/workdir
RUN mkdir -p /home/devuser/bin && chown -R devuser:devuser /home/devuser/bin

WORKDIR /home/devuser/workdir

# Add the new directory to the PATH
ENV PATH="/home/devuser/bin:${PATH}"
ENV BASHRC_PATH="/home/devuser/.bashrc"
ENV TERM="xterm-256color"


## Third-party

### Prompt

# Switch to root user for installation
USER root

# Install Starship
RUN curl -sS https://starship.rs/install.sh | sh -s -- -y

# Switch to non-root user
USER devuser

#                                             ^
# We pass "-y" to say "yes to all prompts" on "curl ...| sh", preceeded with
# "--" to indicate "-y" is an argument of the script, not a "sh" argument.
# But as soon as sh receive any parameter (i.e. "-- -y"), it assumes is not
# reading from STDIN, but from a filename passed as argument.
# So we pass "-s" option to explicitly indicate that we are reading from STDIN.

# Add Starship init to bash
RUN echo 'eval "$(starship init bash)"' >> ${BASHRC_PATH}

# Copy a Starship config
COPY ./third_party/starship.toml /home/devuser/.config/starship.toml

# Enable vi mode in the bashrc for the user
RUN echo 'set -o vi' >> ${BASHRC_PATH}

# Set default shell to Bash
ENTRYPOINT ["/bin/bash"]
