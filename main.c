#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/row.h"

void write_row(FILE *fptr, Row *row);
int find_row(int id);
void print_row(Row *row);
void read_file();
void update_row(int id, Row *new_row);
void delete_row(int id);

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

    printf("=== Writing 3 new rows ===\n\n");

    write_row(fptr, &entry);
    entry.id = 2;
    write_row(fptr, &entry);
    entry.id = 3;
    write_row(fptr, &entry);

    fclose(fptr);

    printf("=== Reading initial file ===\n\n");
    read_file();

    printf("=== Updating row ===\n");
    Row new_entry;

    new_entry.id = 10;
    strcpy(new_entry.name, "1111111");
    new_entry.age = 2;
    update_row(1, &new_entry);

    read_file();

    delete_row(10);

    printf("=== File after deleting first row ===\n\n");
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

int find_row(int id) {
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
    int pointer = find_row(id);

    printf("Pointer is at: %d\n", pointer);

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
