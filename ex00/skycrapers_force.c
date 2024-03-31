/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skycrapers_force.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejhern <alejhern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:12:31 by alejhern          #+#    #+#             */
/*   Updated: 2024/03/31 19:23:04 by alejhern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define N 4 // Tamaño del tablero (NxN)

void print_board(int **board);
void get_row_hints(int **board, int row_hints[N][2]);
int *ft_atoi(const char *argv);
void fill_hints(int **board, int hints[N * 4]);

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void print_board(int **board)
{
    int i;
    int j;
    char num_char;

    i = 0;
    while (i < N)
    {
        j = 0;
        while (j < N)
        {
            num_char = board[i][j] + '0';
            ft_putchar(num_char);
            if (j < N - 1)
                ft_putchar(' ');
            j++;
        }
        ft_putchar('\n');
        i++;
    }
    ft_putchar('\n');
}

int is_valid(int **board, int row, int col, int num)
{
    int x = 0;
    while (x < N)
    {
        if (board[row][x] == num || board[x][col] == num)
        {
            return 0;
        }
        x++;
    }
    return 1;
}

int is_same_pattern(int **board, int *hints_args)
{
    int hints[N * 4] = {0};
    fill_hints(board, hints);
    int i = 0;
    while (i < 16)
    {
        if (hints[i] != hints_args[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

void generate_skyscrapers(int **board, int row, int col, int *hints_args)
{
    // Check if all rows have been filled
    if (row == N)
    {
        // Check if the current board matches the hints
        if (is_same_pattern(board, hints_args))
        {
            print_board(board);
        }
        return;
    }

    // Check if all columns in the current row have been filled
    if (col == N)
    {
        // Move to the next row
        generate_skyscrapers(board, row + 1, 0, hints_args);
        return;
    }

    // Try placing each possible number in the current cell
    int num;
    for (num = 1; num <= N; num++)
    {
        if (is_valid(board, row, col, num))
        {
            // Place the number in the current cell
            board[row][col] = num;

            // Move to the next column
            generate_skyscrapers(board, row, col + 1, hints_args);

            // Reset the current cell after exploring all possibilities
            board[row][col] = 0;
        }
    }
}


int **init_board(int rows, int cols)
{
    int **board = (int **)malloc(rows * sizeof(int *));
    if (board == NULL)
    {
        return NULL; // Manejo del error si la asignación de memoria falla
    }

    int i = 0;
    while (i < rows)
    {
        board[i] = (int *)malloc(cols * sizeof(int));
        if (board[i] == NULL)
        {
            // Liberación de la memoria asignada anteriormente
            while (i > 0)
            {
                free(board[i - 1]);
                i--;
            }
            free(board);
            return NULL; // Manejo del error si la asignación de memoria falla
        }
        i++;
    }

    return board;
}

int main(int argc, char **argv)
{
    int **board;
    int *hints_args = NULL;
    int i;

    if (argc != 2)
    {
        return 1;
    }

    board = init_board(N, N);
    if (board == NULL)
    {
        return EXIT_FAILURE;
    }

    hints_args = ft_atoi(argv[1]);
    if (hints_args == NULL)
    {
        return EXIT_FAILURE;
    }

    generate_skyscrapers(board, 0, 0, hints_args);

    // Liberar memoria de la matriz board
    i = 0;
    while (i < N)
    {
        free(board[i]);
        i++;
    }
    free(board);

    return 0;
}

