#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int binary_str_to_int(char * inp) {
        int ret = 0;
        for (unsigned long i = 0;; i++) {
                if (inp[i] == '\0')
                        break;
                ret <<= 1;
                ret |= inp[i] == '1' ? 1 : 0;
        }
        return ret;
}

int main() {
        FILE * file = fopen("input.txt", "r");
        size_t num_of_lines = 0;
        for (;;) {
                char out_ptr[13];
                int output = fscanf(file, "%s\n", out_ptr);
                if (output == EOF) {
                        break;
                }
                num_of_lines += 1;
        }
        puts("File count read");
        printf("Num of lines => %lu\n", num_of_lines);
        rewind(file);
        char ** lines = malloc(sizeof(char*) * num_of_lines);
        for (int i = 0; i < num_of_lines; i++) {
                char out_ptr[13];
                int output = fscanf(file, "%s\n", out_ptr);
                if (output == EOF)
                        break;
                size_t len = strlen(out_ptr) + 1;
                // printf("Len => %lu\n", len);
                lines[i] = malloc(sizeof(char) * len);
                if (lines[i] == NULL)
                        puts("Here is a nullpointer");
                strcpy(lines[i], out_ptr);
        }


        char ** oxygen_lines = malloc(sizeof(char *) * num_of_lines);
        memcpy(oxygen_lines, lines, num_of_lines);
        for (int i = 0; i < num_of_lines; i++) {
                size_t len = strlen(lines[i]);
                oxygen_lines[i] = malloc(sizeof(char) * (len + 1));
                strcpy(oxygen_lines[i], lines[i]);
        }
        size_t oxygen_num_lines = num_of_lines;
        bool * oxygen_enabled_lines = malloc(sizeof(bool) * num_of_lines);
        for (int i = 0; i < num_of_lines; i++)
                oxygen_enabled_lines[i] = true;
        size_t correct_line_oxygen;

        for (int count = 0; count < 12; count++) {
                size_t zeros = 0;
                size_t ones = 0;
                for (size_t i = 0; i < oxygen_num_lines; i++) {
                        if (!oxygen_enabled_lines[i])
                                continue;
                        char * line = oxygen_lines[i];
                        char first = line[count];
                        if (first == '0')
                                zeros++;
                        else if (first == '1')
                                ones++;
                }


                char rev_char = zeros > ones ? '0' : '1';
                if (zeros == ones)
                        rev_char = '1';
                size_t common_count = zeros > ones ? zeros : ones;


                for (size_t i = 0; i < oxygen_num_lines; i++) {
                        if (!oxygen_enabled_lines[i])
                                continue;
                        char * line = oxygen_lines[i];
                        char first = line[count];
                        if (first == rev_char) {
                                oxygen_enabled_lines[i] = true;
                        } else {
                                oxygen_enabled_lines[i] = false;
                        }
                }

                if (common_count == 1 || count == 11) {
                        for (int i = 0; i < oxygen_num_lines; i++) {
                                if (!oxygen_enabled_lines[i])
                                        continue;
                                char * line = oxygen_lines[i];
                                correct_line_oxygen = i;
                        }
                }
        }

        free(oxygen_lines);

        char ** co2_lines = malloc(sizeof(char *) * num_of_lines);
        memcpy(co2_lines, lines, num_of_lines);
        for (int i = 0; i < num_of_lines; i++) {
                size_t len = strlen(lines[i]);
                co2_lines[i] = malloc(sizeof(char) * (len + 1));
                strcpy(co2_lines[i], lines[i]);
        }
        size_t co2_num_lines = num_of_lines;
        bool * co2_enabled_lines = malloc(sizeof(bool) * num_of_lines);
        for (int i = 0; i < num_of_lines; i++)
                co2_enabled_lines[i] = true;
        size_t correct_line_co2;

        for (int count = 0; count < 12; count++) {
                size_t zeros = 0;
                size_t ones = 0;
                for (size_t i = 0; i < co2_num_lines; i++) {
                        if (!co2_enabled_lines[i])
                                continue;
                        char * line = co2_lines[i];
                        char first = line[count];
                        if (first == '0')
                                zeros++;
                        else if (first == '1')
                                ones++;
                }


                char rev_char = zeros > ones ? '1' : '0';
                if (zeros == ones)
                        rev_char = '0';
                size_t common_count = zeros > ones ? zeros : ones;


                for (size_t i = 0; i < co2_num_lines; i++) {
                        if (!co2_enabled_lines[i])
                                continue;
                        char * line = co2_lines[i];
                        char first = line[count];
                        if (first == rev_char) {
                                co2_enabled_lines[i] = true;
                        } else {
                                co2_enabled_lines[i] = false;
                        }
                }

                if (common_count == 1 || count == 11) {
                        for (int i = 0; i < co2_num_lines; i++) {
                                if (!co2_enabled_lines[i])
                                        continue;
                                char * line = co2_lines[i];
                                correct_line_co2 = i;
                        }
                }
        }

        free(co2_lines);

        for (size_t i = 0; i < num_of_lines; i++)
                free(lines[i]);

        free(lines);

        int oxygen = binary_str_to_int(oxygen_lines[correct_line_oxygen]);
        int co2 = binary_str_to_int(co2_lines[correct_line_co2]);


        printf("Oxygen => %i\n", oxygen);
        printf("CO2 => %i\n", co2);

        int consumption = oxygen * co2;

        printf("Consumption => %i\n", consumption);

        return 0;
}
