#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "row.h"
#include <stdio.h>

void write_row(FILE *fptr, Row *row);
void update_row(int id, Row *new_row);
void delete_row(int id);

int find_row_pos(int id);
void print_row(Row *row);

#endif
