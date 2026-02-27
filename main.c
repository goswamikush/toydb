#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/row.h"

void write_row(FILE *fptr, Row *row);
void read_file();

int main() {
    FILE *fptr;

    fptr = fopen("data.bin", "wb");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Creating new row\n");

    Row entry;

    entry.id = 1;
    strcpy(entry.name, "1234567");
    entry.age = 0;

    printf("Writing new row\n");

    write_row(fptr, &entry);
    write_row(fptr, &entry);
    write_row(fptr, &entry);

    fclose(fptr);

    read_file();

    printf("Success writing to file!\n");

    return 0;
}

void write_row(FILE *fptr, Row *row) {
    fwrite(row, sizeof(Row), 1, fptr);
}

void read_file() {
    FILE *fptr = fopen("data.bin", "rb");
   
    Row new_row;

    fread(&new_row, sizeof(Row), 1, fptr);

    printf("Row id: %d\n", new_row.id);
    printf("Row name: %s\n", new_row.name);
    printf("Row age: %d\n", new_row.age);
}
