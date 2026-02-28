#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "row.h"

void write_row(FILE *fptr, Row *row);
void update_row(int id, Row *new_row);
void delete_row(int id);

int find_row_pos(int id);
void print_row(Row *row);

void write_row(FILE *fptr, Row *row) {
    fwrite(row, sizeof(Row), 1, fptr);
}

int find_row_pos(int id) {
    FILE *fptr = fopen("data.bin", "rb");

    Row curr_row;

    int pointer = 0;

    while (fread(&curr_row, sizeof(Row), 1, fptr) == 1) {
        if (curr_row.id == id) {
            fclose(fptr);
            return pointer;
        }

        pointer++;
    }

    return -1;
}

void update_row(int id, Row *new_row) {
    int pointer = find_row_pos(id);

    FILE *fptr = fopen("data.bin", "r+b");
    fseek(fptr, sizeof(Row) * pointer, SEEK_SET);
    write_row(fptr, new_row);
    fclose(fptr);
}

void delete_row(int id) {
    Row new_row;

    new_row.id = -1;

    update_row(id, &new_row);
}

void print_row(Row *row) {
    printf("Row id: %d\n", row->id);
    printf("Row name: %s\n", row->name);
    printf("Row age: %d\n", row->age);
}
