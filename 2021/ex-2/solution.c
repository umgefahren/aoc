#include <stdint.h>
#include <stdio.h>

int main() {
        int forward = 0;
        int depth = 0;
        int aim = 0;

        FILE * file = fopen("input.txt", "r");

        for (;;) {
                char command[10];
                int num;
                int out = fscanf(file, "%s %i\n", command, &num);
                if (out == EOF) {
                        break;
                }
                switch (command[0]) {
                        case 'f':
                                forward += num;
                                depth += aim * num;
                                break;
                        case 'd':
                                aim += num;
                                break;
                        case 'u':
                                aim -= num;
                                break;
                }
        }
        int res = forward * depth;
        printf("Out => %i", res);
        return 0;
}
