# AGENTS.md — learn-c study repo

> Replicated from `~/Code/learn-repo/template/`. Full rationale:
> `~/Code/learn-repo/STANDARD.md`. **Do not invent a different layout here.**

This is a **study repo** for C: organized for *recall*, not for shipping. Its job
is to answer "what do I already know about X, and how do I refresh it fast?"

## Layout (source-first)

Knowledge is found by an **index** (`exidx`), not by the folder tree, so the tree
is arranged **physically by source** — the book each unit came from:

- `src/<source>/…` — code grouped by the book it came from:
  `src/kr/` (K&R), `src/deitel/` (Deitel), `src/linux/` (Kerrisk),
  `src/udemy/` (courses), plus `src/shared/` — the `kr_util` library + scratch
  `main.c`, built once and reachable from any unit via `-Isrc/shared`.
- `docs/ROADMAP.md` — staged spine with exit checkpoints; each stage lists the
  concepts (tags) it covers.
- `docs/REFRESH-LOG.md` — last-refreshed date per stage.
- `.learnrc` — repo config (`LANG=c`, `TAG_MODE=filename`, build verbs).

## Tags — filename mode

The filename carries the **source** citation; the header carries the **concept**.

- New unit → `src/<source>/<source>_<locator>_<short_concept>.c`, e.g.
  `src/deitel/deitel_0712_pointers_ptr_2_const_data.c` → source tag **`deitel:0712`**
  (Deitel §7.12); `src/kr/kr_604_pointers_to_structures.c` → **`kr:604`**.
- The `<source>` prefix MUST exist in `docs/sources/sources.tsv`.
- Intentionally non-compiling teaching examples end in `.err.c` (the Makefile
  excludes them from build targets).
- `kr_util.c`/`.h` live in `src/shared/` — the shared library, built once,
  excluded from program targets, reachable via `-Isrc/shared`.

## Per-unit header

Open every `.c` with a block using **C89-clean `/* … */` comments, one per key**
(`//` is non-conforming under `-std=c89`), so exidx can index it:

```
/* Concept: <the ideas this demonstrates — comma-separated, indexed by exidx> */
/* Source:  <source:locator — optional; the folder + filename already carry it> */
```

`Concept:` is **required** — it is the retrieval axis exidx groups by. Teaching
comments explaining how C works are encouraged (that's the point of this repo) but
must be accurate.

## When you add or change material

1. Place under the right `src/<source>/`; the book it came from.
2. Name it `source_locator_concept.c`; ensure the source prefix is in
   `sources.tsv`; add a `/* Concept: … */` header.
3. Make sure a ROADMAP stage covers the capability; add a checkpoint line if new.
4. Reindex so it's findable: `exidx index` (retrieval is exidx, not a repo file).

## Build & check (Linux/glibc via Docker)

- Build everything: `make all`
- Run checks: `make test` (building every example IS the test; `.err.c` excluded)

The build runs in the Linux/glibc container (see `README.md`) — some units use
glibc/Linux APIs that don't compile on macOS. Keep every non-`.err.c` unit
compiling.

## Finding code

- **By concept / topic / full text** — `exidx search concept=pointers lang=c`, or
  the Neovim Telescope picker. This is the axis the tree no longer encodes.
- **By source** — browse `src/<source>/`, or grep the tag: `rg "deitel:0712"`.

## Drill repos are separate

`exercism`, etc. are not part of this repo. Connect a drill to a concept with a
`Drills:` line in the unit header: `Drills: exercism/c/<slug>`.
