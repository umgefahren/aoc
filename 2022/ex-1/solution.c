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

void solve() {
        FILE * fileptr;
        char buffer[1000000];
        long filelen;

        fileptr = fopen("input.txt", "rb");

        fread(buffer, 1000000, 1, fileptr);
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
                curLine = nextLine ? (nextLine + 1) : NULL;
        }

        insert_into_top(&top, current);

        printf("Max => %u\n", top.one);
        printf("Sum Top => %u\n", sum_top(&top));
}

int main(int argc, char ** argv) {
        double t = 0.0;
        for (int i = 0; i < 10000; ++i) {
                double startTime = (double)clock() / CLOCKS_PER_SEC;

                solve();

                double endTime = (double)clock() / CLOCKS_PER_SEC;

                double timeElapsed = endTime - startTime;
                t += timeElapsed;
        }
        t /= 100000;
        printf("Took %f ms\n", t * 1000);

        return 0;
}
