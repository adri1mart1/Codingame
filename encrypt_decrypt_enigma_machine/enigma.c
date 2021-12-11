#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define OP_SIZE 257 // operation
#define ROT_SIZE 27 // rotor
#define MSG_SIZE 50 // max message size

typedef struct {
    char operation[OP_SIZE];
    int shift;
    char rotor1[ROT_SIZE];
    char rotor2[ROT_SIZE];
    char rotor3[ROT_SIZE];
    char input[50];
    char output[50];
    int length; // intput/output length
} message;

void dump(message *m)
{
    fprintf(stderr, " -- Message --\n");
    fprintf(stderr, "shift  :%d\n", m->shift);
    fprintf(stderr, "rotor1 :%.*s\n", ROT_SIZE-1, m->rotor1);
    fprintf(stderr, "rotor2 :%.*s\n", ROT_SIZE-1, m->rotor2);
    fprintf(stderr, "rotor3 :%.*s\n", ROT_SIZE-1, m->rotor3);
    fprintf(stderr, "input  :%.*s\n", m->length, m->input);
    fprintf(stderr, "output :%.*s\n", m->length, m->output);
}

void cesar_shift(char in[], char out[], int shift, int len, char sign)
{
    for (int i=0; i<len; i++) {
        char d = in[i] + (shift + sign*i)%26;
        if (d < 'A')
            d += 26;
        if (d > 'Z')
            d -= 26;
        out[i] = d;
    }
}

void rotor_encode(char in[], int len, char rotor[])
{
    char *tmp = malloc(len*sizeof(char));

    for (int i=0; i<len; i++) {
        char in_letter = in[i];

        for (int j=0; j<ROT_SIZE-1; j++) {
            char d = 'A' + j;
            if (d == in_letter) {
                tmp[i] = rotor[j];
                break;
            }
        }
    }

    memcpy(in, tmp, len);
    free(tmp);
}

void rotor_decode(char in[], int len, char rotor[])
{
    char *tmp = malloc(len*sizeof(char));

    for (int i=0; i<len; i++) {
        char in_letter = in[i];

        for (int j=0; j<ROT_SIZE-1; j++) {
            if (rotor[j] == in_letter) {
                tmp[i] = (char)'A'+j;
                break;
            }
        }        
    }

    memcpy(in, tmp, len);
    free(tmp);
}

void encode(message *m)
{
    m->length = strlen(m->input);
    cesar_shift(m->input, m->output, m->shift, m->length, 1);
    rotor_encode(m->output, m->length, m->rotor1);
    rotor_encode(m->output, m->length, m->rotor2);
    rotor_encode(m->output, m->length, m->rotor3);
}

void decode(message *m)
{
    m->length = strlen(m->output);
    rotor_decode(m->output, m->length, m->rotor3);
    rotor_decode(m->output, m->length, m->rotor2);
    rotor_decode(m->output, m->length, m->rotor1);
    cesar_shift(m->output, m->input, -m->shift, m->length, -1);
}

int main()
{
    message m = {0};

    char operation[OP_SIZE];
    fgets(m.operation, OP_SIZE, stdin);

    scanf("%d", &m.shift); fgetc(stdin);

    fgets(m.rotor1, ROT_SIZE, stdin); fgetc(stdin);
    fgets(m.rotor2, ROT_SIZE, stdin); fgetc(stdin);
    fgets(m.rotor3, ROT_SIZE, stdin); fgetc(stdin);

    if (strcmp(m.operation, "ENCODE\n") == 0) {
        fgets(m.input, MSG_SIZE, stdin);
        encode(&m);
        printf("%.*s\n", m.length, m.output);
    } else {
        fgets(m.output, MSG_SIZE, stdin);
        decode(&m);
        printf("%.*s\n", m.length, m.input);
    }

    return 0;
}