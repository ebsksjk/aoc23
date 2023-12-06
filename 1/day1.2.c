#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <ctype.h>
#include <string.h>

#define NOP 0
#define MAX_SIZE 100

typedef struct number {
    char number;
    int position;
}
number;

int main(int argc, char **argv[]) {
    //const char* filename = argv[1];
    FILE * fp = fopen("tinput.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    (fp == NULL) ? exit(EXIT_FAILURE): NOP;

    int result = 0;

    const char * errstr;

    int lines = 0;

    char words[10][10] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };

    while ((read = getline( & line, & len, fp)) != -1) {
        lines++;

        //printf("Processing line %d: %s", lines, line);

        number* fnumbers = malloc(sizeof(number) * 100);
        if (fnumbers == NULL) {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        //printf("Before searching for characters\n");
        int pnumber = 0;
        //find all occurences of 0..9 oder zero..nine in the line and record them in a number struct
        for (int x = 48; x <= 57; x++) {
            char * e;
            int index;

            e = strchr(line, x);
            if(e == NULL){
                continue;
            }

            index = (int)(e - line);

            if (index < 0 || index > len) {
                // printf("not found!\n");
                continue;
            }

            number j;
            j.number = x;
            j.position = index;
            fnumbers[pnumber] = j;
            pnumber++;
            //printf("found char %c (%d)(%d) at position %d in line %d!\n", (char) x, x, x - 48, index, lines);

            e = strrchr(line, x); //53889
            if(e == NULL){
                continue;
            }

            index = (int)(e - line);

            if (index < 0 || index > len) {
                // printf("not found!\n");
                continue;
            }

            number l;
            l.number = x;
            l.position = index;
            fnumbers[pnumber] =l;
            pnumber++;
        }

        //printf("Before searching for strings\n");
        for (int j = 0; j < 10; j++) {
            char * e;
            int index = 0;

            
            e = strstr(line, words[j]);
            if(e == NULL){
               continue;
            }

            index = (int)(e - line);

            if (index < 0 || index > len) {
                //printf("not found!\n");
                continue;
            }

            number x;
            x.number = j + 48;
            x.position = index;
            fnumbers[pnumber] = x;
            pnumber++;
            printf("found string %s (%d) at position %d in line %d! Equivalent to: %c!\n", words[j], j, index, lines, j + 48);
        }

        //printf("Before finding lowest and highest numbers\n");
        //find the number with the min and max position and assign them to first and last number
        int lowestPos = 100;
        number * lowestNumber = NULL;
        int highestPos = -1;
        number * highestNumber = NULL;

        for (int k = 0; k < pnumber; k++) {
            //printf("k: %d\n", k);
            int currentPos = fnumbers[k].position;

            if (currentPos < lowestPos) {
                //printf("pos %d is lower than current %d!\n", currentPos, lowestPos);
                lowestPos = currentPos;
                lowestNumber = &fnumbers[k];
            }
            if (currentPos > highestPos) {
                //printf("pos %d is higher than current %d!\n", currentPos, highestPos);
                highestPos = currentPos;
                highestNumber = &fnumbers[k];
            }
        }

        //proceed as expected
        char endNum[5] = {lowestNumber->number, highestNumber->number, '\0'};
        //printf("lowest Pos: %d\n", lowestPos);
        //printf("highest Pos: %d\n", highestPos);
        printf("line %d: %s", lines, line);
        printf("number in line %d: %c (%d) & ", lines, lowestNumber->number, (int)lowestNumber->number);
        printf("%c (%d)\n", highestNumber->number, (int)highestNumber->number);
        printf("endnum: %s\n------\n\n", endNum);

        result += atoi(endNum);

        line = NULL;
        free(fnumbers);
    }

    printf("result: %d\n", result);

}