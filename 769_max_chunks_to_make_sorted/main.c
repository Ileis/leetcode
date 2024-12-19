#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct tuple
{
    int size;
    int min;
    int max;
}
tuple;

int max(int number1, int number2){ return number1 >= number2 ? number1 : number2; }

int min(int number1, int number2){ return number1 < number2 ? number1 : number2; }

void print_tuple(tuple t){ printf("(size: %d, min: %d, max: %d)", t.size, t.min, t.max); }

int max_chunks_to_sorted(int *arr, int arr_size)
{
    tuple *data_arr = malloc(sizeof(tuple) * arr_size);

    for(int i = 0; i < arr_size; i++)
    {
        data_arr[i].size = 1;
        data_arr[i].min = data_arr[i].max = arr[i];
    }

    int occur_merge = TRUE;

    while(occur_merge)
    {
        occur_merge = FALSE;
        int index = 0;

        while(data_arr[index].size + index < arr_size)
        {
            if(data_arr[index].max > data_arr[data_arr[index].size + index].min)
            {
                occur_merge = TRUE;
                data_arr[index].max = max(data_arr[index].max, data_arr[data_arr[index].size + index].max);
                data_arr[index].min = min(data_arr[index].min, data_arr[data_arr[index].size + index].min);
                data_arr[index].size++;
            }
            else
                index += data_arr[index].size;
        }
    }
    
    int count = 0;

    for(int i = 0; i < arr_size; i += data_arr[i].size)
        count++;

    free(data_arr);

    return count;
}

int main(void)
{
    printf("max_partitions: %d\n", max_chunks_to_sorted((int[]){1, 2, 0 ,3}, 4));

    return EXIT_SUCCESS;
}