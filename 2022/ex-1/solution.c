#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Top {
        uint_fast32_t one, two, three;
};

void insert_into_top(struct Top * p, uint_fast32_t number) {
        if (number > p->one) {
                p->three = p->two;
                p->two = p->one;
                p->one = number;
        } else if (number > p->two) {
                p->three = p->two;
                p->two = number;
        } else if (number > p->three) {
                p->three = number;
        }
}

uint_fast32_t sum_top(const struct Top * p) { return p->one + p->two + p->three; }

int main() {
        uint64_t start = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);

        FILE * fileptr;
        char * buffer;
        long filelen;

        fileptr = fopen("input.txt", "rb");
        fseek(fileptr, 0, SEEK_END);
        filelen = ftell(fileptr);
        rewind(fileptr);

        buffer = (char *)malloc(filelen * sizeof(char));
        fread(buffer, filelen, 1, fileptr);
        fclose(fileptr);

        struct Top top = {.one = 0, .two = 0, .three = 0};
        uint_fast32_t current = 0;

        char * curLine = buffer;

        while (curLine) {
                char * nextLine = strchr(curLine, '\n');
                if (nextLine) *nextLine = '\0';
                if (curLine[0] == '\0') {
                        insert_into_top(&top, current);
                        current = 0;
                } else {
                        current += atoi(curLine);
                }
                if (nextLine) *nextLine = '\n';
                curLine = nextLine ? (nextLine+1) : NULL;
        }

        insert_into_top(&top, current);

        printf("Max => %u\n", top.one);
        printf("Sum Top => %u\n", sum_top(&top));


        uint64_t stop = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
        uint64_t delta = stop - start;

        printf("Took => %llu ns\n", delta);

        double delta_f = delta;
        printf("Equivalent to => %f ms\n", delta / 1.0E6);
        return 0;
}
