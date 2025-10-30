#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Declare all variables
    int start, len;
    char symbol[10], symaddr[10];
    char address[10], label[10], opcode[10], operand[10];
    char mnemonic[10], machcode[10];

    // Open all files
    FILE *intermediate, *symtab, *optab, *length, *assembled, *objc;
    intermediate = fopen("intermediate.asm", "r");
    symtab = fopen("sym.tab", "r");
    optab = fopen("op.tab", "r");
    length = fopen("length.txt", "r");
    assembled = fopen("assembled.asm", "w");
    objc = fopen("objc.obj", "w");

    // Exit if any file could not be opened
    if (!intermediate || !optab || !symtab || !length || !assembled || !objc) {
        printf("Error opening files\n");
        return 1;
    }

    // Read program length and first line
    fscanf(length, "%d", &len);
    fscanf(intermediate, "%s %s %s %s", address, label, opcode, operand);

    // Write the header record
    if (strcmp(opcode, "START") == 0) {
        start = (int)strtol(operand, NULL, 16);
        fprintf(assembled, "%-6s%-6s%-6s%-6s%-10s\n", "~", label, opcode, operand, "~");
        fprintf(objc, "H^%-6s^%06X^%06X\n", label, start, len);
        fscanf(intermediate, "%s %s %s %s", address, label, opcode, operand);
    } else {
        start = 0;
    }

    // Write everything else before the end record in a single text record
    fprintf(objc, "T^%06X^", start);

    // Loop until the end record
    while (strcmp(opcode, "END") != 0) {

        // Loop to find the machcode from optab
        int foundOpcode = 0;
        rewind(optab);
        while (fscanf(optab, "%s %s", mnemonic, machcode) == 2) {
            if (strcmp(opcode, mnemonic) == 0) {
                foundOpcode = 1;

                // Loop to find the symbol from symtab
                int foundSymbol = 0;
                rewind(symtab);
                while (fscanf(symtab, "%s %s", symbol, symaddr) == 2) {
                    if (strcmp(operand, symbol) == 0) {
                        foundSymbol = 1;

                        // Concat the machcode and the symaddr to form the obcode 
                        char obcode[10];
                        sprintf(obcode, "%s%s", machcode, symaddr);
                        fprintf(objc, "%s^", obcode);
                        fprintf(assembled, "%-6s%-6s%-6s%-6s%-10s\n", address, label, opcode, operand, obcode);
                        break;
                    }
                }

                // If symbol was not found then assume symaddr as 0000
                if (!foundSymbol) {
                    char obcode[10];
                    sprintf(obcode, "%s0000", machcode);
                    fprintf(objc, "%s^", obcode);
                    fprintf(assembled, "%-6s%-6s%-6s%-6s%-10s\n", address, label, opcode, operand, obcode);
                }
                break;
            }
        }

        // If opcode was not found then it is either WORD or BYTE
        if (!foundOpcode) {
            if (strcmp(opcode, "WORD") == 0) {
                int val = atoi(operand);
                fprintf(objc, "%06X^", val);
                fprintf(assembled, "%-6s%-6s%-6s%-6s%06X\n", address, label, opcode, operand, val);
            } else if (strcmp(opcode, "BYTE") == 0) {
                fprintf(assembled, "%-6s%-6s%-6s%-6s", address, label, opcode, operand);

                if (operand[0] == 'C') {
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        fprintf(assembled, "%02X\n", operand[i]);
                        fprintf(objc, "%02X", operand[i]);
                    }
                } else if (operand[0] == 'X') {
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        fprintf(assembled, "%c\n", operand[i]);
                        fprintf(objc, "%c", operand[i]);
                    }
                }

                fprintf(objc, "^");
                fprintf(assembled, "\n");
            } else {
                fprintf(assembled, "%-6s%-6s%-6s%-6s\n", address, label, opcode, operand);
            }
        }

        fscanf(intermediate, "%s %s %s %s", address, label, opcode, operand);
    } // Loop until end record

    fprintf(assembled, "%-6s%-6s%-6s%-6s%-10s\n", "~", label, opcode, operand, "~");
    fprintf(objc, "\nE^%06X\n", start);

    // Close all files
    fclose(optab);
    fclose(symtab);
    fclose(intermediate);
    fclose(length);
    fclose(assembled);
    fclose(objc);

    printf("Pass 2 completed successfully");

    return 0;
}