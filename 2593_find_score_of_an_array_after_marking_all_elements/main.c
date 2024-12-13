#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int key_index;
    int value_element;
}
Tuple;

void print_tuple_vec(Tuple *vec, int size)
{
    printf("[");
    for(int i = 0; i < size; i++)
    {
        printf("(key: %d, value: %d)", vec[i].key_index, vec[i].value_element);

        if(i < (size - 1)) printf(", ");
    }
    printf("]\n");
}

int compare_tuple(const void *p_t1, const void * p_t2)
{
    int num_t1 = (*(Tuple*) p_t1).value_element;
    int num_t2 = (*(Tuple*) p_t2).value_element;

    return num_t1 - num_t2;
}

long long find_score(int *nums, int num_size)
{
    Tuple *table_t = malloc(sizeof(Tuple) * num_size);

    for(int i = 0; i < num_size; i++)
    {
        table_t[i].key_index = i;
        table_t[i].value_element = nums[i];
    }

    qsort(table_t, num_size, sizeof(Tuple), compare_tuple);

    int table_it = 0;
    int acc = 0;
    for(int i = 0; i < num_size; i++)
    {
        int index_number = table_t[table_it].key_index;
        int number = nums[index_number];

        if(number > -1)
        {
            acc += number;

            if((index_number - 1) >= 0)
                nums[index_number - 1] = -1;
            if((index_number + 1) < num_size)
                nums[index_number + 1] = -1;
        }
        table_it++;
    }

    return acc;
}

int main()
{
    printf("score: %lld\n", find_score((int[]){2, 1, 3, 4, 5, 2}, 6));

    return EXIT_SUCCESS;
}