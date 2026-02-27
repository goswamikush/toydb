#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/row.h"

int write_row(FILE *fptr, Row *row);

int main() {
    FILE *fptr;

    fptr = fopen("data.txt", "w");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Creating new row\n");

    Row *new_data = malloc(sizeof(Row));

    new_data->id = 1;
    strcpy(new_data->name, "1234567");
    new_data->age = 0;

    printf("Writing new row\n");

    write_row(fptr, new_data);

    fclose(fptr);

    printf("Success writing to file!\n");

    return 0;
}

int write_row(FILE *fptr, Row *row) {
    fprintf(fptr, "%d", row->id);
    fprintf(fptr, "%s", row->name);
    fprintf(fptr, "%d", row->age);

    return 0;
}
