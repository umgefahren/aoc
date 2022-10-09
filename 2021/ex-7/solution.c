#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t abs_int64(int64_t inp) { return inp < 0 ? inp * -1 : inp; }

int64_t distance(int64_t a, int64_t b) {
        int64_t n = abs_int64(a - b);
        return (n * (n + 1)) / 2;
}

int cmpfunc(const void * a, const void * b) {
        int a_i = *(int *)a;
        int b_i = *(int *)b;
        if (a_i > b_i)
                return 1;
        else if (a_i < b_i)
                return -1;
        else
                return 0;
}

uint64_t min(uint64_t a, uint64_t b) { return a < b ? a : b; }

uint64_t calc_fuel(const int64_t * crabs, int64_t crab_count, int64_t middle) {
        uint64_t fuel_middle_total = 0;

        for (uint64_t i = 0; i < crab_count; i++) {
                fuel_middle_total += distance(middle, crabs[i]);
        }
        return fuel_middle_total;
}

int main(int argc, char ** argv) {
        char * line_buffer = NULL;
        size_t len;
        FILE * file = fopen("input.txt", "r");
        if (file == NULL) perror("Opening file can't open file");
        getline(&line_buffer, &len, file);
        char * token = strtok(line_buffer, ",");

        uint64_t crab_count = 0;
        int64_t * crabs = malloc(sizeof(int64_t) * 1);

        while (token != NULL) {
                int64_t crab_pos = atoi(token);
                crab_count += 1;
                crabs = realloc(crabs, sizeof(int64_t) * crab_count);
                crabs[crab_count - 1] = crab_pos;
                token = strtok(NULL, ",");
        }

        qsort(crabs, crab_count, sizeof(int64_t), cmpfunc);

        int64_t lower_limit = crabs[0];
        int64_t upper_limit = crabs[crab_count - 1];
        int64_t step_size = (upper_limit - lower_limit) / 2;

        uint64_t total_fuel = UINT64_MAX;

        for (int64_t pos = lower_limit; pos < upper_limit; pos++) {
                total_fuel = min(total_fuel, calc_fuel(crabs, crab_count, pos));
        }

        printf("Total fuel => %llu\n", total_fuel);

        // This solution is insultingly simple

        return 0;
}
