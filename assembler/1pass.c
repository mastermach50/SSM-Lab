#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Declare all variables
    char label[10], opcode[10], operand[10];
    char optab_opcode[10], optab_value[10];
    int locctr, start, len;

    // Open all files
    FILE *input, *symtab, *optab, *intermediate, *length;
    input = fopen("input.asm", "r");
    symtab = fopen("sym.tab", "w");
    optab = fopen("op.tab", "r");
    intermediate = fopen("intermediate.asm", "w");
    length = fopen("length.txt", "w");

    // Exit if any file could not be opened
    if (!input || !symtab || !optab || !intermediate || !length) {
        printf("Error opening files\n");
        return -1;
    }

    // Read the first line from the input to set starting address
    fscanf(input, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = (int)strtol(operand, NULL, 16);
        locctr = start;

        fprintf(intermediate, "%-6X%-6s%-6s%-6s\n", locctr, label, opcode, operand);
        fscanf(input, "%s %s %s", label, opcode, operand);
    } else {
        start = 0;
        locctr = 0;
    }

    // Repeat until the end record
    while (strcmp(opcode, "END") != 0) {
        // If there is a label then add it to symtab
        if (strcmp(label, "~") != 0) {
            fprintf(symtab, "%-8s%04X\n", label, locctr);
        }
        fprintf(intermediate, "%-6X%-6s%-6s%-6s\n", locctr, label, opcode, operand);

        // If the opcode is present in the optab then increment locctr by 3
        rewind(optab);
        int found = 0;
        while (fscanf(optab, "%s %s", optab_opcode, optab_value) == 2) {
            if (strcmp(opcode, optab_opcode) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    locctr += strlen(operand) - 3;
                } else if (operand[0] == 'X') {
                    locctr += (strlen(operand) - 3) / 2;
                }
            } else if (strcmp(opcode, "RESB")) {
                locctr += atoi(operand);
            }
        }

        fscanf(input, "%s %s %s", label, opcode, operand);
    }

    // Write the end record to intermediate file
    fprintf(intermediate, "%-6X%-6s%-6s%-6s\n", locctr, label, opcode, operand);

    // Write program length to the length file
    len = locctr - start;
    fprintf(length, "%X", len);

    // Close all files
    fclose(input);
    fclose(symtab);
    fclose(optab);
    fclose(intermediate);
    fclose(length);

    printf("Pass 1 completed successfully\n");

    return 0;
}
