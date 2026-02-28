#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "row.h"

void write_row(Row *row, bool is_update);
void update_row(int id, Row *new_row);
void delete_row(int id);

int find_row_pos(int id);
void print_row(Row *row);

void write_row(Row *row, bool is_update) {
    FILE *fptr = fopen("data.bin", "r+b");

    fseek(fptr, 0, SEEK_END);
    fwrite(row, sizeof(Row), 1, fptr);

    // Update num rows
    // if (!is_update) {
    //     int row_count;
    //     fseek(fptr, 0, SEEK_SET);
    //     fread(&row_count, sizeof(int), 1, fptr);
    //     row_count++;

    //     fseek(fptr, 0, SEEK_SET);
    //     fwrite(&row_count, sizeof(int), 1, fptr);
    // }

    fclose(fptr);
}

int find_row_pos(int id) {
    FILE *fptr = fopen("data.bin", "rb");

    Row curr_row;

    int pointer = 0;

    fseek(fptr, sizeof(int), SEEK_SET);

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
    int pos = find_row_pos(id);

    FILE *fptr = fopen("data.bin", "r+b");

    fseek(fptr, sizeof(int) + sizeof(Row) * pos, SEEK_SET);

    fwrite(new_row, sizeof(Row), 1, fptr);

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
