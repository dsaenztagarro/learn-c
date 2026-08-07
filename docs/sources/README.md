# Sources

- [`sources.tsv`](sources.tsv) — the `prefix → human name` table. Edit by hand.
  Every source cited in `src/` has a row here; the table also feeds exidx's
  `[books]` map, so `deitel` resolves to a display name.

Walking the material **by source** is now just the tree: `src/kr/`, `src/deitel/`,
`src/linux/`, `src/udemy/`. Cross-cutting retrieval — by concept, topic, or full
text, across every `learn-*` repo — is [`exidx`](../../../exidx/README.md):

```bash
exidx search concept=pointers lang=c
rg "deitel:0712"     # or just grep the source:locator tag
```

(The former generated `docs/sources/{kr,deitel,linux,udemy}.md` reverse-indexes
are retired — under a source-first tree they duplicated the directory. See
`~/Code/learn-repo/STANDARD.md` §5.)
