## learn-c

### Bookmark
- 5.12 Complicated Declarations

### Running examples

`Ctrl+d` at an empty prompt sends the ASCII "End of Transmission" (i.e. `EOF`).

```
$ ./bin/<executable>
....<Enter>
...<Enter>
<Ctr+D>
```

### Complex declarations

```c
char (*(*f())[])();
```

* Decomposition:
  - 1. `f()`: f is a function (no arguments).
  - 2. `*f()`: Returns a pointer.
  - 3. `(*f())[]`: Pointer points to an array.
  - 4. `*(*f())[]`: Array elements are pointers.
  - 5. `(*(*f())[])()`: Pointers are functions (no arguments) returning char.
* Result: f is a function returning a pointer to an array of pointers to functions returning char.

#### Key rules
* **Parentheses** `()` override precedence.
  Example: `int (*p)[5]` → `p` is a pointer to an array of 5 ints (not an
  array of pointers).
* **Right-Left Rule**: Start at the identifier, move right for `[]`/`()`, then
  left for *, alternating.

#### Practice problems

```c
char (*(*x())[])()
```

x: function returning a pointer to array[] of pointer to function returning char.

```c
char (*(*x[3])())[5]
```

x: array[3] of pointer to function returning pointer to array[5] of char.

```c
int (*(*foo)(int))[5]
```

`foo` is a **pointer to a function** taking `int` and returning a
**pointer to an array of 5 ints**.

```c
void (*signal(int, void (*)(int)))(int)
```

`signal` is a **function** taking `int` and a **pointer to a function**
taking `int`, returning a **pointer to a function** taking `int` and returning
`void`.

In short: Declarators define nested type relationships.
Start with the identifier, apply operators by precedence (parentheses first),
and build the type outward.

### Compiling manually

```bash
gcc -g -O0 -o bin/factorial -o src/main.c
# ^
# -O0 means no optimisation is done
#     gdb > info functions
#     ^ it will return many functions from other *.c files

gcc -g -o bin/factorial -o src/main.c
# ^
# Without -O0 we get only reference to our function: `(gdb) info functions`.
# -std=c11 ,  Ensure C11 standard
# -pedantic , Ensures that the code strictly adheres to the C11 standard and raises errors for non-standard code, such as some compiler extensions.
# -Werror ,   Turn warnings into errors

gdb -q ./bin/factorial
# ^
# -q , --quiet : skip GDB licensing information

gdb -q --args executable arg1 arg2 arg3
gdb -q --args ./bin/factorial 3
#         ^ for passing command line arguments to program
```

### GDB

```bash
file executable_path
break main   # set breakpoint at main function

r, run
r arg1 arg2 arg3                  # run program with arguments
set args                          # with no args clear arguments of last run
n next    # step over
s step    # step into a function
f finish  # steps out of the current function, stopping at the caller
q quit    # quit GDB

info functions <regex> # list functions match regex
break <function_name>
list
list                   # to continue listing the file
list .                 # to return to original debugging position
list <line_number>
list <start>,<end>     # print lines in range
list <function_name>   # print lines after a function
info breakpoints       # list active breakpoints
delete
continue

backtrace  # list stack of functions with SIGSEV
frame <n>  #

(gdb) frame [N]     # Select frame N (e.g., `frame 2`)
(gdb) frame         # Show details of the current frame
(gdb) info frame    # Detailed info about the current frame

(gdb) frame 1       # Switch to frame #1 (caller of the current function)
(gdb) info locals   # Show local variables in the selected frame
(gdb) print x       # Print variable `x` in the selected frame

p [/format] [expression]
(gdb) print i
(gdb) print /x i   # print number as hexadecimal
(gdb) print /o i   # print number as octal
(gdb) print sizeof(i)
(gdb) print sizeof(&i)
```

GDB comes with a powerful tool for directly examing memory: the x command.

The x command examines memory, starting at a particular address.

```bash
(gdb) x &i
(gdb) x/4xb &i
        ^ I want to examine 4 bytes with hexadecimal format

x/[N][F][U] ADDRESS
```

`x/4xw ptr`	Show 4 words (4 bytes each) in hex at address ptr
`x/8xb arr`	Show 8 bytes in hex at address arr
`x/5c arr`	Show 5 bytes as ASCII characters
`x/s ptr`	  Show a null-terminated string at address ptr
`x/i $pc`	  Show the instruction at the current program counter
`x/10d arr`	Show 10 integers in decimal at address arr
`x/2hf arr`	Show 2 halfwords (2 bytes each) as floats at address arr
`x`	        Show memory at the last address used (advances automatically)


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

The value of `buf` is `0x0`, which is the `NULL` pointer.
malloc returns NULL when it cannot allocate the amount of memory requested.
So our malloc must have failed.

Examples:

```c
int *ptr = NULL;
*ptr = 42; // Dereferencing a null pointer triggers SIGSEGV

int arr[10];
arr[20] = 5; // Accessing out-of-bounds memory triggers SIGSEGV
```
