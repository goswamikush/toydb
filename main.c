#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/row.h"

void write_row(FILE *fptr, Row *row);

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

    printf("Success writing to file!\n");

    return 0;
}

void write_row(FILE *fptr, Row *row) {
    fseek(fptr, 0L, SEEK_END);
    fwrite(row, sizeof(Row), 1, fptr);
}
