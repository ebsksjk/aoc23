#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <ctype.h>
#include <string.h>

typedef struct number {
    char number;
    char position;
} number;

#define NOP 0

int main() {
  FILE *fp = fopen("input.txt", "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  (fp == NULL) ? exit(EXIT_FAILURE) : NOP;


  int result = 0;

  const char *errstr;
  char firstNumber = NULL;
  char lastNumber = NULL;

  int lines = 0;

  char words[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  while ((read = getline(&line, &len, fp)) != -1) {

    lines++;

    number *fnumbers = malloc(sizeof(number)*100);
    int pnumber = 0;

            //find all occurences of 0..9 oder zero..nine in the line and record them in a number struct
            for(int x = 48; x < 57; x++){
                char *e;
                int index;

                e = strchr(line, x);
                index = (int)(e - line);

                if(index < 0){
                    //printf("not found!\n");
                    continue;
                }

                /*number j = {(char)x, index};
                fnumbers[pnumber] = j;
                pnumber++;*/
                printf("%s", line);
                printf("found char %c (%d) at position %d in line %d!\n", (char)x, x, index, lines);
            }

            for(int j = 0; j < 10; j++){
                char *e;
                int index;

                e = strstr(line, words[j]);
                index = (int)(e - line);

                if(index < 0){
                    //printf("not found!\n");
                    continue;
                }

                /*number j = {(char)x, index};
                fnumbers[pnumber] = j;
                pnumber++;*/
                printf("%s", line);
                printf("found string %s at position %d in line %d!\n", words[j], index, lines);
            }

    //find the number with the min and max position and assign them to first and last number


    //proceed as expected
    /*char endNum[5] = {firstNumber, lastNumber};

    printf("line %d: %s", lines, line);
    printf("number in line %d: %c & ", lines, firstNumber);
    printf("%c\t", lastNumber);
    printf("endnum: %s\n", endNum);

    result += atoi(endNum);*/

    line = NULL;
    free(fnumbers);
  }

  //printf("result: %d\n", result);

}