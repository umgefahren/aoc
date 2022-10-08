#include <stdint.h>
#include <stdio.h>

int main() {
        FILE * inp_file = fopen("input.txt", "r");
        uint64_t a = 0;
        uint64_t b = 0;
        uint64_t c = 0;
        uint64_t slider = 0;
        uint64_t incremented = 0;
        for (;;) {
                uint64_t current_depth;
                int output = fscanf(inp_file, "%llu\n", &current_depth);
                if (output == EOF) {
                        break;
                }
                uint64_t last_sum = a + b + c;
                a = b;
                b = c;
                c = current_depth;
                uint64_t current_sum = a + b + c;
                if (current_sum > last_sum && slider >= 3) incremented += 1;
                slider += 1;
        }
        printf("Counter => %llu", incremented);
        return 0;
}
