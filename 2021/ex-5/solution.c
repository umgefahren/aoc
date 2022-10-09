#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum Part {
        One,
        Two,
};

unsigned max_u(unsigned a, unsigned b) { return a > b ? a : b; }

struct Field {
        unsigned x_max;
        unsigned y_max;
        unsigned ** field;
        unsigned max_field_value;
};

struct Field new_field(unsigned x_max, unsigned y_max) {
        struct Field ret;
        ret.x_max = x_max;
        ret.y_max = y_max;
        ret.max_field_value = 0;
        ret.field = malloc(sizeof(unsigned *) * x_max);
        for (unsigned i = 0; i <= y_max; i++) {
                ret.field[i] = malloc(sizeof(unsigned) * x_max);
                for (unsigned j = 0; j <= x_max; j++) ret.field[i][j] = 0;
        }
        return ret;
}

void print_field(const struct Field * field) {
        for (int i = 0; i <= field->y_max; i++) {
                for (int j = 0; j <= field->x_max; j++) {
                        unsigned val = field->field[i][j];
                        if (val == 0)
                                putchar('.');
                        else
                                printf("%u", val);
                }
                putchar('\n');
        }
}

unsigned count_occur(const struct Field * field, unsigned num) {
        unsigned counter = 0;
        for (unsigned i = 0; i <= field->x_max; i++)
                for (unsigned j = 0; j <= field->y_max; j++)
                        if (field->field[i][j] >= num) counter++;
        return counter;
}

struct Arrow {
        unsigned start_x;
        unsigned start_y;
        unsigned end_x;
        unsigned end_y;
};

void print_arrow(const struct Arrow * arrow) {
        printf("%3u,%3u -> %3u,%3u\n", arrow->start_x, arrow->start_y, arrow->end_x, arrow->end_y);
}

struct Arrow read_from_file(FILE * file, int * error) {
        struct Arrow ret;
        int start_x;
        int start_y;
        int end_x;
        int end_y;
        *error = fscanf(file, "%u,%u -> %u,%u\n", &start_x, &start_y, &end_x, &end_y);
        ret.start_x = start_x;
        ret.start_y = start_y;
        ret.end_x = end_x;
        ret.end_y = end_y;
        return ret;
}

bool is_straight(struct Arrow arrow) {
        return arrow.start_x == arrow.end_x || arrow.start_y == arrow.end_y;
}

void enter_arrow(struct Field * field, struct Arrow arrow, enum Part part) {
        if (arrow.start_x == arrow.end_x) {
                unsigned start = arrow.start_y < arrow.end_y ? arrow.start_y : arrow.end_y;
                unsigned end = arrow.start_y > arrow.end_y ? arrow.start_y : arrow.end_y;
                for (unsigned i = start; i <= end; i++) {
                        field->field[arrow.start_x][i] += 1;
                        field->max_field_value =
                            max_u(field->max_field_value, field->field[arrow.start_x][i]);
                }
        } else if (arrow.start_y == arrow.end_y) {
                unsigned start = arrow.start_x < arrow.end_x ? arrow.start_x : arrow.end_x;
                unsigned end = arrow.start_x > arrow.end_x ? arrow.start_x : arrow.end_x;
                for (unsigned i = start; i <= end; i++) {
                        field->field[i][arrow.start_y] += 1;
                        field->max_field_value =
                            max_u(field->max_field_value, field->field[i][arrow.start_y]);
                }
        } else {
                if (part == One) return;
                int mod_x = arrow.start_x < arrow.end_x ? 1 : -1;
                int mod_y = arrow.start_y < arrow.end_y ? 1 : -1;
                int start_x = arrow.start_x;
                int end_x = arrow.end_x;
                int start_y = arrow.start_y;
                int diff = abs(end_x - start_x);

                for (int i = 0; i <= diff; i++) {
                        int x = start_x + (i * mod_x);
                        int y = start_y + (i * mod_y);
                        field->field[x][y] += 1;
                }
        }
}

int main(int argc, char ** argv) {
        if (argc != 3)
                puts("didn't pass enough arguments");
        char * file_path = argv[1];
        enum Part part;
        if (argv[2][0] == '1')
                part = One;
        else if (argv[2][0] == '2')
                part = Two;
        FILE * file = fopen(file_path, "r");
        size_t arrows_count = 0;
        struct Arrow * arrows = malloc(sizeof(struct Arrow) * 0);
        unsigned x_max = 0;
        unsigned y_max = 0;
        for (;;) {
                int error;
                struct Arrow arrow = read_from_file(file, &error);
                if (error == EOF) break;
                x_max = max_u(x_max, arrow.start_x);
                x_max = max_u(x_max, arrow.end_x);
                y_max = max_u(y_max, arrow.start_y);
                y_max = max_u(y_max, arrow.end_y);
                arrows = realloc(arrows, sizeof(struct Arrow) * (arrows_count + 1));
                arrows[arrows_count] = arrow;
                arrows_count++;
        }
        struct Field field = new_field(x_max, y_max);

        printf("arrows count => %lu\n", arrows_count);

        for (unsigned i = 0; i < arrows_count; i++) {
                struct Arrow arrow = arrows[i];
                enter_arrow(&field, arrow, part);
        }

        unsigned occur = count_occur(&field, 2);

        printf("occured => %u\n", occur);

        return 0;
}
