#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/row.h"
#include "utils/operations.h"

void read_file();

int main() {
    FILE *fptr;

    fptr = fopen("data.bin", "wb");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Creating new row\n");

    // Write num rows is 0 for header
    int num_rows = 0;
    fwrite(&num_rows, sizeof(int), 1, fptr);

    return 0;
}

void read_file() {
    FILE *fptr = fopen("data.bin", "rb");

    // Read number of rows
    int num_rows;

    fread(&num_rows, sizeof(int), 1, fptr);

    printf("Num rows: %d\n", num_rows);

    Row new_row; 

    while (fread(&new_row, sizeof(Row), 1, fptr) == 1) {
        if (new_row.id == -1) {
            continue;
        }

        printf("Row id: %d\n", new_row.id);
        printf("Row name: %s\n", new_row.name);
        printf("Row age: %d\n", new_row.age);
        printf("\n");
    }
}
