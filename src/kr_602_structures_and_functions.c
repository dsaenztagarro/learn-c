#include <stdio.h>

#define XMAX 100
#define YMAX 100

struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};


int main()
{
    struct rect screen;
    struct point middle __attribute__((unused));
    struct point makepoint(int x, int y);

    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    middle = makepoint((screen.pt1.x + screen.pt2.x)/2,
                       (screen.pt1.y + screen.pt2.y)/2);

    struct point origin, *pp;

    pp = &origin;
    printf("origin is (%d,%d)\n", (*pp).x, (*pp).y);
    /* The expression *pp.x means *(pp.x),
     * which is illegal here because x is not a pointer */
    printf("origin is (%d,%d)\n", pp->x, pp->y);
    /*                            ^ alternative notation to (*pp).x */

    struct rect r, *rp = &r;

    printf("%d", r.pt1.x);
    printf("%d", rp->pt1.x);
    printf("%d", (r.pt1).x);
    printf("%d", (rp->pt1).x);

    return 0;
}

/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

/* addpoint: add two points */
struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

/* canonrect: canonicalize coordinates of rectangles */
struct rect canonrect(struct rect r)
{
    struct rect temp;

    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}
