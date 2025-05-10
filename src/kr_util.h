/* 4.3 External variables */
int getch(void);
void ungetch(int);

/* 5.4 Address Arithmethic */
char *alloc(int n);
void afree(char *p);

/* 5.6 Pointers to Arrays; Pointers to Pointers */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

/* 5.11 Pointers to Functions */
int numcmp(const char *, const char *);

/* 6.4 Pointers to Structures */
/* 6.5 Self-referential Structures */
int getword(char *word, int lim);
