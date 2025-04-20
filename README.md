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

gdb -q --args executablename arg1 arg2 arg3
gdb -q --args ./bin/factorial 3
#         ^ for passing command line arguments to program
```

### GDB

```bash
file executable_path

r, run
r arg1 arg2 arg3                  # run program with arguments
set args                          # with no args clear arguments of last run
finish                            # run until it completes the function
n, next # step over
s, step # step into
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


ubuntu:25.04
359 ⬢ [Docker] ❯ gdb --version
  1 GNU gdb (Ubuntu 16.2-8ubuntu1) 16.2
  2 Copyright (C) 2024 Free Software Foundation, Inc.
  3 License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
  4 This is free software: you are free to change and redistribute it.
  5 There is NO WARRANTY, to the extent permitted by law.


### Debugging segmentation fault

```
⬢ [Docker] ❯ gdb ./bin/segmentation_fault
Reading symbols from ./bin/segmentation_fault...
(gdb) r
Starting program: /home/dev/workdir/bin/segmentation_fault
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/aarch64-linux-gnu/libthread_db.so.1".
Linux

Program received signal SIGSEGV, Segmentation fault.
0x0000fffff7e60f58 in __GI__IO_getline_info (fp=fp@entry=0xfffff7fa0880 <_IO_2_1_stdin_>, buf=buf@entry=0x0, n=n@entry=1023, delim=delim@entry=10,
    extract_delim=extract_delim@entry=1, eof=eof@entry=0x0) at ./libio/iogetline.c:77
warning: 77     ./libio/iogetline.c: No such file or directory

(gdb) backtrace
#0  0x0000fffff7e60f58 in __GI__IO_getline_info (fp=fp@entry=0xfffff7fa0880 <_IO_2_1_stdin_>, buf=buf@entry=0x0, n=n@entry=1023, delim=delim@entry=10,
    extract_delim=extract_delim@entry=1, eof=eof@entry=0x0) at ./libio/iogetline.c:77
#1  0x0000fffff7e61014 in __GI__IO_getline (fp=fp@entry=0xfffff7fa0880 <_IO_2_1_stdin_>, buf=buf@entry=0x0, n=n@entry=1023, delim=delim@entry=10,
    extract_delim=extract_delim@entry=1) at ./libio/iogetline.c:34
#2  0x0000fffff7e5fa74 in _IO_fgets (buf=0x0, n=1024, fp=0xfffff7fa0880 <_IO_2_1_stdin_>) at ./libio/iofgets.c:53
#3  0x0000aaaaaaaa0890 in main (argc=1, argv=0xfffffffff4f8) at src/segmentation_fault.c:11

So we received the SIGSEV signal from the operating system.
SIGSEV = Signal Segmentation Violation
That means we tried to access an invalid memory address.

(gdb) frame 3
#3  0x0000aaaaaaaa0890 in main (argc=1, argv=0xfffffffff4f8) at src/segmentation_fault.c:11
warning: Source file is more recent than executable.
11      //                 Problem: On 32-bit systems, this exceeds the maximum allocatable

(gdb) print buf
$1 = 0x0
```

When `buf` pointer contains `0x0`, it means has `NULL` value.

Examples:

```c
int *ptr = NULL;
*ptr = 42; // Dereferencing a null pointer triggers SIGSEGV

int arr[10];
arr[20] = 5; // Accessing out-of-bounds memory triggers SIGSEGV
```

