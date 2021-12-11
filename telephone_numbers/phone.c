#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    int N, res = 0; 
    scanf("%d", &N);

    char phonelist[N][21];
    memset(phonelist, 0, 21*sizeof(char));
    
    for (int i=0; i<N; i++) {
        scanf("%s", phonelist[i]);
        res += strlen(phonelist[i]);

        int best_res = 0;

        for (int j=0; j<i; j++) {

            char *a = phonelist[j];
            char *b = phonelist[i];
            
            int current_res = 0;

            while (*a == *b && *a != '\0' && *b != '\0') {
                a++; b++;
                current_res++;
            }

            if (current_res > best_res)
                best_res = current_res;
        }
        res -= best_res;
    }

    printf("%d\n", res);
    return 0;
}