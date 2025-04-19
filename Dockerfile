FROM dsaenztagarro/dev-env:1.0.1

RUN sudo apt-get install -y gcc gdb
#                            ^ GCC emits debugging information (DWARF format)
#                              that GDB is specifically designed to understand
#                              Only If cc is a link to gcc, there is no
#                              difference in the debugging experience

RUN sudo apt-get install -y clangd # LSP engine for C, C++

RUN echo 'alias gcc="gcc -std=c11 -pedantic -Wall"' >> ${BASHRC_PATH}
RUN echo 'alias gdb="gdb --quiet"' >> ${BASHRC_PATH}
# ^
# --quiet : skip GDB licensing information

# Only uncomment once this becomes final
# RUN sudo rm -rf /var/lib/apt/lists/*

# Set default shell to Bash
ENTRYPOINT ["/bin/bash"]
