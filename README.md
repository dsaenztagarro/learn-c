## learn-c

```bash
gcc -g -O0 -o bin/factorial -o src/main.c
# ^
# -O0 means no optimisation is done
#     gdb > info functions
#     ^ it will return many functions from other *.c files

gcc -g -o bin/factorial -o src/main.c
# ^
# Without -O0 we get only reference to our function (gdb > info functions)
# -std=c11 ,  Ensure C11 standard
# -pedantic , Ensures that the code strictly adheres to the C11 standard and raises errors for non-standard code, such as some compiler extensions.
# -Werror ,   Turn warnings into errors

gdb -q ./bin/factorial
# ^
# -q , --quiet : skip GDB licensing information

gdb -q --args ./bin/factorial 3
#         ^ for passing command line arguments to program
```

### GDB

```bash
file executable_path

r, run
r arg1 arg2 ...                    # run program with arguments
finish                             # run until it completes the function
n, next
s, step # inside
q, quit

info functions <regex> # list functions match regex
break <function_name>
list
list                   # to continue listing the file
list .                 # to return to original debugging position
list <line_number>
list <start>,<end>     # print lines in range
info breakpoints       # list active breakpoints
delete
continue
```

## Tasks
- [ ] Configure DAP adapter in NeoVim so it interacts with GDB running on Docker Container
