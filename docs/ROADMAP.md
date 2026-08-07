# learn-c — ROADMAP

The staged path through C. Refresh = jump to the lowest stage that feels rusty and
pass its **exit checkpoint**. Stamp the date in [`REFRESH-LOG.md`](REFRESH-LOG.md)
when you do.

Stages map to `src/<concept>/` folders. Checkpoints are "I can …" statements you
verify by *writing code*, not by nodding.

---

## Stage 01 — Fundamentals

- **Concepts:** `src/basics/`, `src/control-flow/`, `src/types/`
- **Exit checkpoint:**
  - [ ] I can write, compile, and run a program from a blank file using only the
        toolchain (`gcc -std=c89 -Wall`).
  - [ ] I can explain `int`/`char`/`unsigned`, `sizeof`, and how a `#define`
        symbolic constant differs from a `const`.
  - [ ] I can write the classic `for`/`while` character-processing loop idiom.

## Stage 02 — Arrays & strings

- **Concepts:** `src/arrays/`, `src/strings/`
- **Exit checkpoint:**
  - [ ] I can declare and initialize 1-D and multi-dimensional arrays.
  - [ ] I can write `strcpy`/`strcmp` from scratch, both array- and
        pointer-indexed, and explain the null terminator.

## Stage 03 — Functions & scope

- **Concepts:** `src/functions/`
- **Exit checkpoint:**
  - [ ] I can explain call-by-value vs simulating call-by-reference.
  - [ ] I can reason about `extern`/external variables and write a recursive
        function with a correct base case.

## Stage 04 — Pointers

- **Concepts:** `src/pointers/`
- **Exit checkpoint:**
  - [ ] I can read any of the four `const`/pointer combinations and predict which
        assignments the compiler rejects (see the `.err.c` examples).
  - [ ] I can use pointer arithmetic, arrays of pointers, and pointers to
        functions, and decode a "complicated declaration".

## Stage 05 — Structures & user types

- **Concepts:** `src/structures/`, plus `typedef`/`union` in `src/types/`
- **Exit checkpoint:**
  - [ ] I can define structs, arrays of structs, and self-referential structs.
  - [ ] I can build a table lookup and explain `typedef`, `union`, and bit-fields.

## Stage 06 — I/O

- **Concepts:** `src/char-io/`, `src/file-io/`
- **Exit checkpoint:**
  - [ ] I can write character-counting, line-counting, and word-counting filters.
  - [ ] I can copy a file with low-level `read`/`write` (needs `tlpi_hdr.h` from
        the `tlpi-dist` repo — see note in REFRESH-LOG).

## Stage 07 — Bit-level & systems

- **Concepts:** `src/bit-manipulation/`, `src/system/`
- **Exit checkpoint:**
  - [ ] I can print an integer in binary and use the bitwise operators with masks.
  - [ ] I can recognize what triggers a segmentation fault and check the glibc
        version at runtime.

---

### Cadence

Default: fundamentals (Stages 01–04) every ~90 days, the rest every ~180 days.
Tune per row in [`REFRESH-LOG.md`](REFRESH-LOG.md).
