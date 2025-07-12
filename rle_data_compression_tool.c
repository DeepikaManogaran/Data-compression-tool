#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compress the file using RLE
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("Error opening files!\n");
        return;
    }

    char current, prev;
    int count = 1;

    prev = fgetc(in);

    while ((current = fgetc(in)) != EOF) {
        if (current == prev) {
            count++;
        } else {
            fprintf(out, "%d%c", count, prev);
            count = 1;
        }
        prev = current;
    }

    // Write the last sequence
    fprintf(out, "%d%c", count, prev);

    fclose(in);
    fclose(out);

    printf("Compression completed!\n");
}

// Function to decompress the file
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("Error opening files!\n");
        return;
    }

    int count;
    char ch;

    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);

    printf("Decompression completed!\n");
}

// Main program to select compression or decompression
int main() {
    int choice;
    char inputFile[100], outputFile[100];

    printf("DATA COMPRESSION TOOL - RLE\n");
    printf("1. Compress a file\n");
    printf("2. Decompress a file\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter input file name: ");
    scanf("%s", inputFile);
    printf("Enter output file name: ");
    scanf("%s", outputFile);

    if (choice == 1) {
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        decompressFile(inputFile, outputFile);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
