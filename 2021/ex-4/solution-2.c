#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Board
{
        bool marked[5][5];
        int numbers[5][5];
        bool won;
};

struct Board read_from_file(FILE *file, int *error)
{
        struct Board ret;
        for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                        ret.marked[i][j] = false;
        for (int i = 0; i < 5; i++)
                *error = fscanf(file, "%i %i %i %i %i\n", ret.numbers[i], ret.numbers[i] + 1, ret.numbers[i] + 2, ret.numbers[i] + 3, ret.numbers[i] + 4);
        ret.won = false;
        return ret;
}

void print_board(const struct Board *board)
{
        for (int i = 0; i < 5; i++)
                printf("%2i%c %2i%c %2i%c %2i%c %2i%c\n", board->numbers[i][0], board->marked[i][0] ? '*' : ' ', board->numbers[i][1], board->marked[i][1] ? '*' : ' ', board->numbers[i][2], board->marked[i][2] ? '*' : ' ', board->numbers[i][3], board->marked[i][3] ? '*' : ' ', board->numbers[i][4], board->marked[i][4] ? '*' : ' ');
}

void enter_number(struct Board *board, int number)
{
        for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                {
                        if (board->numbers[i][j] == number)
                        {
                                board->marked[i][j] = true;
                        }
                }
}

bool won(const struct Board *board)
{
        for (int i = 0; i < 5; i++)
        {
                bool line_valid = board->marked[i][0] && board->marked[i][1] && board->marked[i][2] && board->marked[i][3] && board->marked[i][4];
                if (line_valid)
                {
                        return true;
                }
        }
        for (int i = 0; i < 5; i++)
        {
                bool line_valid = board->marked[0][i] && board->marked[1][i] && board->marked[2][i] && board->marked[3][i] && board->marked[4][i];
                if (line_valid)
                {
                        return true;
                }
        }
        return false;
}

int sum_of_unmarked(const struct Board *board)
{
        int ret = 0;
        for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                        if (!board->marked[i][j])
                                ret += board->numbers[i][j];
        return ret;
}

int main()
{
        FILE *file = fopen("input.txt", "r");
        char *first_line_buffer = NULL;
        size_t cap;
        if (getline(&first_line_buffer, &cap, file) == -1)
                perror("Erro reading first line");
        puts(first_line_buffer);
        int *random_nums = malloc(0);
        unsigned random_nums_count = 0;
        char *token = strtok(first_line_buffer, ",");
        while (token != NULL)
        {
                random_nums_count++;
                random_nums = realloc(random_nums, sizeof(int) * random_nums_count);
                random_nums[random_nums_count - 1] = atoi(token);
                token = strtok(NULL, ",");
        }
        fscanf(file, "\n");
        struct Board *boards = malloc(0);
        size_t boards_num;
        for (size_t i = 0;; i++)
        {
                boards = realloc(boards, sizeof(struct Board) * (i + 1));
                int error;
                struct Board board = read_from_file(file, &error);
                if (error == EOF)
                        break;
                boards[i] = board;
                print_board(&board);
                boards_num = i;
        }
        for (int i = 0; i < boards_num; i++)
        {
                puts("");
                struct Board board = boards[i];
                print_board(&board);
        }

        int value;

        for (unsigned i = 0; i < random_nums_count; i++)
        {
                // if (i == 5) break;
                int random_num = random_nums[i];
                for (unsigned j = 0; j <= boards_num; j++)
                {
                        struct Board *board = boards + j;
                        enter_number(board, random_num);
                        if (won(board) && !board->won)
                        {
                                value = sum_of_unmarked(board) * random_num;
                                board->won = true;
                        }
                }
        }
        printf("Last Value => %i\n", value);
        return 0;
}
