FROM dsaenztagarro/dev-env:1.0.1

RUN sudo apt-get install -y gcc

RUN echo 'alias gcc="gcc -std=c11 -pedantic -Wall"' >> ${BASHRC_PATH}
RUN echo 'alias gdb="gdb --quiet"' >> ${BASHRC_PATH}
# ^
# --quiet : skip GDB licensing information

RUN sudo rm -rf /var/lib/apt/lists/*

# Set default shell to Bash
ENTRYPOINT ["/bin/bash"]
