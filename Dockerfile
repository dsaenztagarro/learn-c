# syntax=docker/dockerfile:1
# Needs BuildKit (default in Docker Desktop) for the RUN --mount=type=cache below.

# Uses the decoupled base (non-root $DEV_USER, project bind-mounted at /workspace,
# /workspace/bin already on PATH). Rebuild+push dsaenztagarro/dev-env at this tag
# before building this image.
FROM dsaenztagarro/dev-env:2.0.1

# Names the base's user so $DEV_USER expands here too (default matches its ENV).
ARG DEV_USER=me

USER root

# Keep .debs for the apt cache mount (Ubuntu's docker-clean discards them).
RUN rm -f /etc/apt/apt.conf.d/docker-clean && \
    echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' > /etc/apt/apt.conf.d/keep-cache

# gcc/gdb/valgrind: the C toolchain, debugger, and memory checker. clangd: the
# C/C++ LSP. gcc emits DWARF debug info that gdb reads.
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y \
      gcc gdb valgrind clangd

USER $DEV_USER

# Interactive-shell aliases.
RUN echo 'alias gcc="gcc -std=c11 -pedantic -Wall"' >> ${BASHRC_PATH}
RUN echo 'alias gdb="gdb --quiet"' >> ${BASHRC_PATH}   # --quiet: skip GDB banner

# The base already puts /workspace/bin on PATH, so no PATH override is needed here
# (the units build to bin/<book>/<unit>; run them by explicit path).

# Set default shell to Bash
ENTRYPOINT ["/bin/bash"]
