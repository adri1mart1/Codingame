#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define ALPHABET_TOTAL_DIGIT 20
#define MAX_CHAR_SIZE 100

typedef struct {
    int h;
    int w;
    int v; // value
    char d[MAX_CHAR_SIZE][MAX_CHAR_SIZE]; 
} Digit_t;

typedef struct {
    int h;
    int w;
    Digit_t digits[ALPHABET_TOTAL_DIGIT];
} Alphabet_t;

void display_digit(Digit_t *d)
{
    fprintf(stderr, "digit w:%d h:%d v:%d\n", d->w, d->h, d->v);
    for (int i=0; i<d->h; i++)
        fprintf(stderr, "%.*s\n", d->w, d->d[i]);
}

void display_alphabet(Alphabet_t *a)
{
    fprintf(stderr, "displaying alphabet w:%d h:%d\n", a->w, a->h);
    for (int i=0; i<ALPHABET_TOTAL_DIGIT; i++)
        display_digit(&a->digits[i]);
}

void init_digits(Alphabet_t *a) {
    for (int i=0; i<ALPHABET_TOTAL_DIGIT; i++) {
        a->digits[i].h = a->h;
        a->digits[i].w = a->w;
        a->digits[i].v = i;
    }
}

void feed_digit(int row, Digit_t *d, char n[]) {
    int i=0, j=0;
    while (n[i] != '\0')
        d->d[row][j++] = n[i++];
}

void feed_digits(int row, Alphabet_t *a, char n[])
{
    int i=0, ds=0, d=0;

    while (n[i] != '\0') {
        a->digits[ds].d[row][d++] = n[i++];
        if (((i)%a->w) == 0) {
            ds++;
            d=0;
        }
    }
}

bool digits_are_equal(Digit_t *a, Digit_t *b)
{
    for (int i=0; i<a->h; i++) {
        for (int j=0; j<a->w; j++) {
            if (a->d[i][j] != b->d[i][j])
                return false;
        }
    }
    return true;
}

void find_digit_value(Alphabet_t *a, Digit_t *d)
{
    for (int i=0; i<ALPHABET_TOTAL_DIGIT; i++) {
        if (digits_are_equal(&a->digits[i], d)) {
            d->v = a->digits[i].v;
            break;
        }
    }
}

// return the digit value in based 20.
// first argument is the digit index (most
// significant digit first), the second arg
// is the total digit expected
long long retrieve_nth_digit_value(Alphabet_t *a, Digit_t *d, int n, int tot)
{
    find_digit_value(a, d);
    return pow(ALPHABET_TOTAL_DIGIT, tot - n) * d->v;
}

long long make_calculation(long long a, long long b, char op)
{
    if (op == '*')
        return a*b;
    else if (op == '/')
        return a/b;
    else if (op == '+')
        return a+b;
    return a-b; 
}

void print_mayan_num(Alphabet_t *a, long long int v)
{
    int dig_n;
    if (v == 0)
        dig_n = 0;
    else
        dig_n = (floor)(log(v)/log(20));

    for (int i=dig_n; i>=0; i--) {
        long long n = v / pow(ALPHABET_TOTAL_DIGIT, i);
        
        for (int i=0; i<a->w; i++)
            printf("%.*s\n", a->h, a->digits[n].d[i]);

        v = v - (n * pow(ALPHABET_TOTAL_DIGIT, i));
    }
}

int main()
{
    Alphabet_t a = {0};
    scanf("%d%d", &a.w, &a.h);
    init_digits(&a);

    for (int i = 0; i < a.h; i++) {
        char n[2049] = {0};
        scanf("%s", n);
        feed_digits(i, &a, n);
    }

    // display_alphabet(&a);

    long long value1 = 0;
    int S1;
    scanf("%d", &S1);
    Digit_t d1;
    d1.h = a.h;
    d1.w = a.w;
    int dn = S1/a.h;

    for (int j = 0; j < dn; j++) {
        for (int i = 0; i < S1/dn; i++) {
            char n[a.h+1];
            scanf("%s", n);
            feed_digit(i, &d1, n);
        }
        // display_digit(&d1);
        value1 += retrieve_nth_digit_value(&a, &d1, j+1, dn);
    }

    long long value2 = 0;
    int S2;
    scanf("%d", &S2);
    Digit_t d2;
    d2.h = a.h;
    d2.w = a.w;
    dn = S2/a.h; // digit number

    for (int j=0; j<dn; j++) {
        for (int i=0; i<S2/dn; i++) {
            char n[a.h+1];
            scanf("%s", n);
            feed_digit(i, &d2, n);
        }
        //display_digit(&d2);
        value2 += retrieve_nth_digit_value(&a, &d2, j+1, dn);
    }

    char op[2];
    scanf("%s", op);

    long long result = make_calculation(value1, value2, op[0]);

    print_mayan_num(&a, result);

    return 0;
}