#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /* isdigit */
#include "ritchie_util.h" /* getch ungetch */

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER '0'      /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
/* expression `(1 - 2) * (4 + 5)` is entered as `1 2 - 4 5 + *` */
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            /*         ^ Because + and * are commutative operators, the order
             *           in which the popped operands are combined is irrelevant,
             *           but for - and / the left and right operands must be
             *           distinguished. In
             *
             *           push(pop() - pop());  // WRONG
             *
             *           the order in which the two calls of pop are evaluated
             *           is not defined.
             *           To guarantee the right order, it is necessary to pop
             *           the first value into a temporary variable.
             */
            break;
        case '/':
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL  100     /* maximum depth of the val stack */
int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
/* ^ external variables for push and pop
 *   A variable is external if it is defined outside of any function
 */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}
/*                                             ^
 *         How %g Works:
 *         - If the number is small or fits compactly in decimal notation,
 *           %g uses %f style (e.g., 123.45 → 123.45).
 *         - If the number is large or very small, %g uses %e (scientific)
 *           notation (e.g., 1234567.0 → 1.23457e+06).
 *         - It prints up to 6 significant digits by default, omits unnecessary
 *           trailing zeros, and drops the decimal point if not needed
 */

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;   /* not a number */
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
