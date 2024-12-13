#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** alloc_matrix_int(int row, int *col)
{
    int **matrix = malloc(sizeof(int*) * row);

    for(int i = 0; i < row; i++)
    {
        matrix[i] = malloc(sizeof(int) * col[i]);
    }

    return matrix;
}

void* free_matrix_int(int **matrix, int row)
{
    for(int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return NULL;
}

int nearest_int_matrix(int **matrix, int row, int *col, int value)
{    
    int **matrix_diff = alloc_matrix_int(row, col);

    // calculate matrix_diff
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col[i]; j++)
        {
            matrix_diff[i][j] = abs(matrix[i][j] - value);
        }
    }

    int diff_low_row = 0;
    int diff_low_col = 0;

    // find index lowest matrix_diff
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col[i]; j++)
        {
            if(matrix_diff[i][j] < matrix_diff[diff_low_row][diff_low_col])
            {
                diff_low_row = i;
                diff_low_col = j;
            }
        }
    }

    int nearest_int = matrix[diff_low_row][diff_low_col];

    matrix_diff = free_matrix_int(matrix_diff, row);

    return nearest_int;
}

int compare_int(const void *p_num1, const void *p_num2)
{
    int num1 = *(int*) p_num1;
    int num2 = *(int*) p_num2;

    return num1 - num2;
}

int median_int_matrix(int **matrix, int row, int *col)
{
    int total_elements = 0;

    for(int i = 0; i < row; i++)
        total_elements += col[i];

    int *vector = malloc(sizeof(int) * total_elements);
    int vec_size = 0;

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col[i]; j++)
        {
            vector[vec_size] = matrix[i][j];
            vec_size++;
        }
    }

    qsort(vector, vec_size, sizeof(int), compare_int);

    int median;

    if((vec_size % 2) == 0)
    {
        median = (vector[(int) floor(vec_size / 2.0)] + vector[(int) ceil(vec_size / 2.0)]) / 2;
    }
    else
    {
        median = vector[vec_size / 2];
    }

    free(vector);

    return median;
}

int min_operations(int** grid, int grid_row_size, int *grid_col_size, int x)
{
    int median = median_int_matrix(grid, grid_row_size, grid_col_size);
    int nearest_int = nearest_int_matrix(grid, grid_row_size, grid_col_size, median);
    int **matrix_diff = alloc_matrix_int(grid_row_size, grid_col_size);

    // calculate matrix diff
    for(int i = 0; i < grid_row_size; i++)
    {
        for(int j = 0; j < grid_col_size[i]; j++)
        {
            matrix_diff[i][j] = grid[i][j] - nearest_int;
        }
    }

    // check if is possible uni value
    // and calculate the number of operations
    int number_operations = 0;

    for(int i = 0; i < grid_row_size; i++)
    {
        for(int j = 0; j < grid_col_size[i]; j++)
        {
            if((matrix_diff[i][j] % x) != 0)
                return -1;
            
            number_operations += abs(matrix_diff[i][j] / x);
        }
    }

    matrix_diff = free_matrix_int(matrix_diff, grid_row_size);

    return number_operations;
}

int main(void)
{
    int row = 1;
    int col[] = {1};
    int matrix_aux[4][4] = {{146}};
    int **matrix = alloc_matrix_int(row, col);

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col[i]; j++)
        {
            matrix[i][j] = matrix_aux[i][j];
        }
    }
    // print_int_matrix(matrix, row, col);

    int result = min_operations(matrix, row, col, 84);

    matrix = free_matrix_int(matrix, 2);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}