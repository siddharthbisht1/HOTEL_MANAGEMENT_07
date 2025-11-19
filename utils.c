#include "utils.h"
#include <stdio.h>
#include <string.h>

int input_int(const char *prompt, int min, int max){
    int x;
    char line[128];

    while(1){
        printf("%s", prompt);

        if(!fgets(line, sizeof(line), stdin))
            return min;

        if(sscanf(line, "%d", &x) == 1){
            if(x < min || x > max)
                printf("Enter value between %d and %d\n", min, max);
            else
                return x;
        } else {
            printf("Invalid integer. Try again.\n");
        }
    }
}

void input_string(const char *prompt, char *buf, int size){
    printf("%s", prompt);

    if(fgets(buf, size, stdin) == NULL)
        buf[0] = '\0';

    buf[strcspn(buf, "\n")] = '\0';   // << THIS FIXES THE ISSUE
}

void pause_console(){
    printf("Press Enter to continue...");
    getchar();
}
