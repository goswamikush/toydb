#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../utils/operations.h"

void test_insert();
void test_update();
void test_delete();
void test_find();
void setup(Row *rows);

Row get_row(int pointer);
bool assert_row_equals(int id, Row *ground_truth);

void test_insert() {
    printf("=== Beginning row insertion tests ===\n\n");

    Row rows[3];
    setup(rows);

    assert_row_equals(rows[0].id, &rows[0]);
    assert_row_equals(rows[1].id, &rows[1]);
    assert_row_equals(rows[2].id, &rows[2]);

    printf("\n=== End of row insertion tests ===\n\n");
}

void test_update() {
    printf("\n=== Beginning row update tests ===\n\n");

    Row rows[3];
    setup(rows);

    // Create new row
    Row new_entry;

    new_entry.id = 10;
    strcpy(new_entry.name, "0000000");
    new_entry.age = 2;

    update_row(1, &new_entry);

    assert_row_equals(10, &new_entry);

    printf("\n=== Ending row update tests\n\n");
}

void test_delete() {
    printf("\n=== Beginning row delete tests ===\n\n");

    Row rows[3];
    setup(rows);

    delete_row(rows[0].id);

    if (find_row_pos(rows[0].id) == -1) {
        printf("Successfully deleted row\n");
    } else {
        printf("Failed to delete row\n");
    }

    printf("\n=== Ending row delete tests\n\n");
}

void test_find() {
    printf("\n=== Beginning row find tests ===\n\n");

    Row rows[3];
    setup(rows);

    assert_row_equals(rows[0].id, &rows[0]);
    assert_row_equals(rows[1].id, &rows[1]);
    assert_row_equals(rows[2].id, &rows[2]);

    printf("\n=== Ending row find tests\n\n");
}

bool assert_row_equals(int target_id, Row *ground_truth) {
    int pointer = find_row_pos(target_id);
    Row row = get_row(pointer);

    if (ground_truth->id != row.id) {
        printf("Expected id of %d but got id of %d\n", ground_truth->id, row.id);
        return false;
    }

    if (strcmp(ground_truth->name, row.name) != 0) {
        printf("Expected name of %s but got name of %s\n", ground_truth->name, row.name);
        return false;
    } 

    if (ground_truth->age != row.age) {
        printf("Expected age of %d but got age of %d\n", ground_truth->age, row.age);
        return false;
    }

    printf("Both rows are equal\n");

    return true;
}

Row get_row(int pointer) {
    Row res;

    FILE *fptr = fopen("data.bin", "r+b");
    fseek(fptr, sizeof(Row) * pointer, SEEK_SET);\
    
    fread(&res, sizeof(Row), 1, fptr);

    return res;
}

void setup(Row *rows) {
    FILE *fptr = fopen("data.bin", "wb");

    rows[0] = (Row){1, "Alice", 25};
    rows[1] = (Row){2, "Bob", 30};
    rows[2] = (Row){3, "Charlie", 35};

    write_row(fptr, &rows[0]);
    write_row(fptr, &rows[1]);
    write_row(fptr, &rows[2]);
    fclose(fptr);
}

int main() {
    test_insert();
    test_update();
    test_delete();
    test_find();

    return 0;
}
