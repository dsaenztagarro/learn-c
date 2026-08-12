/* Concept: types */
/* Source: deitel:ch10_03 */
#include <stdio.h>
#include <stdlib.h> /* srand */
#include <time.h> /* time */

struct card {
    char *face;
    char *suit;
};

typedef struct card Card;
/* ^ makes `Card` a synonym for `struct card`
 *   Use capitalized names for typedefs
 *   It must be emphasized that a typedef declaration does not create a new
 *   type in any sense; it merely adds a new name for some existing type. */

void fillDeck(Card *, char *[], char *[]);
void shuffle(Card *);
void deal(Card *);

int main()
{
    Card deck[52];
    char *face[] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven",
                     "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    char *suit[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

    srand(time(NULL));
    /* ^ `srand` expects an `unsigned int` seed, but `time(NULL)` returns a
     *   `time_t`.
     *   The C compiler implicitly converts the time_t value to unsigned int
     *   when passing it to srand.
     *   This conversion is allowed in C, even if it might truncate the value
     *   (if time_t is larger than unsigned int).
     */

    fillDeck(deck, face, suit);
    shuffle(deck);
    deal(deck);
    return 0;
}

void fillDeck(Card *wDeck, char *wFace[], char *wSuit[])
{ /*                ^ "w" stands for variables that store a "word" (String) */
    int i;

    for (i = 0; i <= 51; i++) {
        wDeck[i].face = wFace[i % 13];
        wDeck[i].suit = wSuit[i / 13];
    }
}

void shuffle(Card *wDeck)
{
    int i, j;
    Card temp;

    for (i = 0; i <= 51; i++) {
        j = rand() % 52;
        temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void deal(Card *wDeck)
{
    int i;

    for(i = 0; i < 52; i++)
        printf("%5s of %-8s%c", wDeck[i].face, wDeck[i].suit,
               (i + 1) % 2 ? '\t' : '\n');
}
