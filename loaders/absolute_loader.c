#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Open all files
    FILE *input, *output;
    input = fopen("input.obj", "r");
    output = fopen("output.load", "w");

    // Read the header
    char header[30];
    fscanf(input, "%s", header);

    // Get the name and display it
    char name[30];
    int h, n;
    for (h=2, n=0; header[h] != '^'; h++, n++) {
        name[n] = header[h];
    }
    name[n] = '\0';
    printf("Program Name: %s\n", name);

    // Read each line until the end record
    char line[50];
    fscanf(input, "%s", line);

    while (line[0] != 'E') {
        // Get the starting address of the text record
        char start[30];
        strncpy(start, line + 2, 6);
        start[6] = '\0';
        printf("%s\n", start);
        int locctr = strtol(start, NULL, 16);

        // Find the next 2 characters and load them to an address
        char c1 = '$';
        for (int i=11; i<strlen(line); i++) {
            if (line[i] == '^') {
                continue;
            }
            if (line[i] == '$') {
                break;
            }

            if (c1 == '$') {
                c1 = line[i];
            } else if (c1 != '$') {
                fprintf(output, "%06X %c%c\n", locctr, c1, line[i]);
                c1 = '$';
                locctr++;
            }
        }

        fscanf(input, "%s", line);
    }

    // Close all files
    fclose(input);
    fclose(output);

    return 0;
}