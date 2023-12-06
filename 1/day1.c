#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <ctype.h>

#define NOP 0

int main() {
    FILE *fp = fopen("input.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    (fp == NULL) ? exit(EXIT_FAILURE) : NOP;

    int lines = 0;
    int ch;

    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n') {
            lines++;
        }
    }

    rewind(fp);
    int result = 0;

    const char *errstr;
    char firstNumber = NULL;
    char lastNumber = NULL;

    lines = 0;

    while ((read = getline(&line, &len, fp)) != -1) {

        firstNumber = NULL;
        lastNumber = NULL;
        lines++;
        for(int i = 0; i < len; i++) {
            if(!isspace(line[i]) && !((int)line[i] == 0)) {
                //printf("line: %d, char %d: %c (%d)\n", lines, i, line[i], (int)line[i]);
                if((isdigit(line[i]) != 0) && firstNumber == NULL) {
                    firstNumber = line[i];
                    lastNumber = line[i];
                } else if(isdigit(line[i]) != 0 && firstNumber != NULL) {
                    lastNumber = line[i];
                }
            }
        }

        char endNum[5] = {firstNumber, lastNumber};

        printf("line %d: %s", lines, line);
        printf("number in line %d: %c & ", lines, firstNumber);
        printf("%c\t", lastNumber);
        printf("endnum: %s\n", endNum);

        result += atoi(endNum);

        line = NULL;
    }

    printf("result: %d\n", result);

}