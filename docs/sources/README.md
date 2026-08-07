# Sources index

Walk the material **by source** (book chapter) as an alternative to the
concept-first `src/` tree.

- [`sources.tsv`](sources.tsv) — `prefix → human name` table. Edit by hand.
- `*.md` (one per source) — reverse-index mapping locator → file.
  **Generated** by `learn index`. Do not hand-edit.

Regenerate after adding/moving/renaming units:

```bash
learn index
```
