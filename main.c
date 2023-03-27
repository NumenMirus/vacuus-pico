#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 50
#define MAX_COL_LEN 200

/* This function reads a CSV file and stores its contents in a 2D array.
   It returns the number of rows read. */
int parse_csv(char *filename, char data[MAX_COLS][MAX_COL_LEN], char delim) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    int row = 0, col = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        col = 0;
        token = strtok(line, &delim);
        while (token != NULL) {
            strcpy(data[row][col], token);
            token = strtok(NULL, &delim);
            col++;
        }
        row++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
    return row;
}
