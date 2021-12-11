#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* All couples of characters are assimilated to human couples
 * with the first character being the man, the second the 
 * woman. 
 */
typedef enum {
    MAN = 0,
    WOMAN = 1,
    NONE = 2
} gender;

const char couples[] = {
    // First column -> MAN
    // Second column -> WOMAN
    '(', ')',
    '[', ']',
    '{', '}'
};

// Return the character type (either MAN/WOMAN or NONE)
gender get_type(char c) {
    for (int i=0; i<(sizeof(couples)/sizeof(char)); i++) {
        if (c == couples[i]) {
            if (i%2 == 0)
                return MAN;
            else
                return WOMAN;
        }
    }
    return NONE;
}

// return true if the woman is the wife of the man
bool is_half(char husband, char woman)
{
    for (int i=0; i<(sizeof(couples)/sizeof(char)); i+=2) {
        if (husband == couples[i] && woman == couples[i+1])
            return true;
    } 
    return false;
}

// return +n index from start to its husband
// return -1 if not found or invalid
int find_associations(char *b, bool reach_the_end)
{
    int idx = 0;
    char *current = b;
    char man = 0;

    while (*current != '\0') {
        gender g = get_type(*current);

        if (g == WOMAN) {

            if (is_half(man, *current)) { // Successfully found maried woman
                
                // This part is to handle the case where the initial sentence
                // is not finished but till now, all mens have found their
                // maried woman. We need to check the remaining characters though
                if (reach_the_end && *(current+1) != '\0')
                    man = 0;
                else
                    return idx;         
            } else
                return -1; // Wrong woman, this pattern is wrong !!

        } else if (g == MAN) {
            if (man == 0)
                man = *current; // first time we meet a man, saving its value

            else {
                int ret = find_associations(current, false);
                if (ret == -1)
                    return -1; // sub recursive actions failed so abording too

                else {
                    // sub recursive actions were successful
                    // checking next characters from the point where the last
                    // woman was found
                    current += ret; 
                    idx += ret;
                }
            }
        }

        current++;
        idx++;
    }

    if (man == 0)
        return 1;

    // reaching the end of the function means a man didn't find it wife
    return -1;
}

int main()
{
    char expression[2049] = {0};
    scanf("%s", expression);

    if (find_associations(expression, true) > 0) 
        printf("true\n");
    else
        printf("false\n");
}