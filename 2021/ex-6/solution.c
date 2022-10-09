#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef unsigned _ExtInt(128) uint128_t;

struct Swarm {
        uint128_t counters[9];
        uint128_t count;
};

struct Swarm new_swarm(FILE * file) {
        struct Swarm ret;

        char * line = NULL;
        size_t n;
        getline(&line, &n, file);

        char * token = strtok(line, ",");

        for (unsigned i = 0; i < 9; i++)
                ret.counters[i] = 0;

        ret.count = 1;
        ret.counters[atoi(token)] += 1;

        while (token != NULL) {
                token = strtok(NULL, ",");
                if (token == NULL) break;
                unsigned timer_value = atoi(token);
                ret.count += 1;
                ret.counters[timer_value] += 1;
        }

        return ret;
}

void print_swarm(const struct Swarm * swarm) {
        for (unsigned i = 0; i < 9; i++)
                for (unsigned j = 0; j < swarm->counters[i]; j++)
                        printf("%u,", i);
        puts("");
}

void calculate_cycle(struct Swarm * swarm) {
        uint128_t new_counters[9] = {0};
        uint128_t new_count = swarm->count;
        for (unsigned i = 0; i < 9; i++) {
                uint128_t number = swarm->counters[i];
                if (i == 0) {
                        new_counters[8] += number;
                        new_count += number;
                        new_counters[6] += number;
                } else {
                        new_counters[i - 1] += number;
                }
        }

        for (unsigned i = 0; i < 9; i++)
                swarm->counters[i] = new_counters[i];
        swarm->count = new_count;
}



int main(int argc, char ** argv) {
        if (argc != 3) {
                fputs("not correct number of arguments passed.", stderr);
                return 1;
        }
        char * file_path = argv[1];
        unsigned days = atoi(argv[2]);
        FILE * file = fopen(file_path, "r");
        struct Swarm swarm = new_swarm(file);
        for (unsigned i = 0; i < days; i++) {
                calculate_cycle(&swarm);
        }
        printf("Num of fish => ");
        char * count_str = "";
        do {
                int digit = swarm.count % 10;
                asprintf(&count_str, "%d%s", digit, count_str);
                swarm.count /= 10;

        } while (swarm.count != 0);
        puts(count_str);
        return 0;
}
