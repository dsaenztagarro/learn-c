# AGENTS.md — learn-c study repo

> Replicated from `~/Code/learn-repo/template/`. Full rationale:
> `~/Code/learn-repo/STANDARD.md`. **Do not invent a different layout here.**

This is a **study repo** for C: organized for *recall*, not for shipping. Its job
is to answer "what do I already know about X, and how do I refresh it fast?"

## Layout (concept-first)

- `src/<concept>/…` — code grouped by **concept**, never by book/chapter.
  Current concepts: `basics/`, `control-flow/`, `types/`, `arrays/`, `strings/`,
  `functions/`, `pointers/`, `structures/`, `char-io/`, `bit-manipulation/`,
  `file-io/`, `system/`, plus `shared/` (the `kr_util` library + scratch `main.c`).
- `docs/ROADMAP.md` — staged spine with exit checkpoints.
- `docs/REFRESH-LOG.md` — last-refreshed date per stage.
- `docs/sources/` — reverse-index per source. **Generated** — see below.

## Source tagging — filename mode

The filename **is** the citation: `source_locator_concept.c`.
Examples:

- `deitel_0712_pointers_ptr_2_const_data.c` → tag **`deitel:0712`** (Deitel §7.12)
- `kr_604_pointers_to_structures.c` → tag **`kr:604`** (K&R §6.4)

Rules:

- New unit → `src/<concept>/<source>_<locator>_<short_concept>.c`.
- The `<source>` prefix MUST exist in `docs/sources/sources.tsv`.
- Intentionally non-compiling teaching examples end in `.err.c` (the Makefile
  excludes them from build targets).
- `kr_util.c`/`.h` live in `src/shared/` and are the shared library — built once,
  excluded from program targets, reachable from any concept via `-Isrc/shared`.

## Per-unit header

Keep/extend the teaching comment header at the top of each `.c`. The filename
carries `Source`, so the header focuses on:

```
Stage:    <ROADMAP stage>
Concept:  <one line: the idea>
Example:  <one line: what the code does>
Exercise: <one line: a from-scratch variation for refresh>
```

(C teaching comments explaining how the language works are encouraged — that's
the point of this repo — but must be accurate, per the comment rule below.)

## When you add or change material

1. Place under the right `src/<concept>/`; new concept folder only if none fits.
2. Name it `source_locator_concept.c`; ensure the source prefix is in
   `sources.tsv`.
3. Make sure a ROADMAP stage covers the capability; add a checkpoint line if new.
4. Regenerate indexes: `learn index`.
5. Never hand-edit `docs/sources/*.md` — it is overwritten.

## Build & check (Linux/glibc via Docker)

- Build everything: `make all`
- Run checks: `make test`  (compiling every example IS the test)

This repo builds under **Linux + glibc with `-std=c89`** (the Docker image). It
does **not** build on native macOS clang, because `kr_util` reimplements `getline`
and `strdup` (K&R exercises) which the macOS SDK headers redeclare; glibc hides
those POSIX names under `__STRICT_ANSI__`, the macOS SDK does not. Build in the
container:

```bash
make container   # start the Linux dev container
make terminal    # shell in; then: make all
```

## Drill repos are separate

`exercism/c`, etc. are not part of this repo. To link a drill to a concept, add a
`Drills:` line to the unit header:

```
Drills: exercism/c/<slug>
```

## Code comments

Comments describe what exists, not what doesn't. Only name a symbol, file, or
header that is actually present. Teaching comments are welcome but must be
accurate.
