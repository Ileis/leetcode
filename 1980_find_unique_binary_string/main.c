#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// meu algoritmo funciona mas nao eh tao engenhoso quando a solucao proposta pelo leetcode
// solucao proposta: Argumento diagonal de Cantor
//  -> A ideia principal eh garantir que a string resultante difira de todas as strings
//     em nums em pelo menos um bit.
// -> output vai ser o "inverso" da diagonal principal da matriz nums.

int string_to_bin(char *str, int str_size)
{
    int value = 0;
    for(int i = (str_size - 1); i >= 0; i--)
        value += (pow(2, str_size - i - 1) * (str[i] - '0'));

    return value;
}

char* int_to_string_bin(int num, int str_size)
{
    char *str_bin = malloc(sizeof(char) * str_size + 1);
    str_bin[str_size] = '\0';

    for(int i = (str_size - 1); i >= 0; i--)
    {
        str_bin[i] = '0' + num % 2;
        num /= 2;
    }

    return str_bin;
}

char* find_different_binary_string(char **nums, int num_size)
{
    int total_size = pow(2, num_size);
    int *table_presence = malloc(sizeof(int) * total_size);

    for(int i = 0; i < total_size; i++)
        table_presence[i] = 0;

    for(int i = 0; i < num_size; i++)
    {
        int index = string_to_bin(nums[i], num_size);
        table_presence[index] = 1;
    }

    int index_element = 0;
    for(int i = 0; i < total_size; i++)
    {
        if(table_presence[i] == 0)
            index_element = i; 
    }

    free(table_presence);

    return int_to_string_bin(index_element, num_size);
}

int main(void)
{
    char *str = "101";
    char strs_aux[3][3] = {{"111"}, {"011"}, {"001"}};
    char **strs = malloc(sizeof(char*) * 3);

    for(int i = 0; i < 3; i++)
        strs[i] = malloc(sizeof(char) * 3);    

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            strs[i][j] = strs_aux[i][j];

    char *str_output = find_different_binary_string(strs, 3);

    printf("%s\n", str_output); // free

    free(str_output);

    for(int i = 0; i < 3; i++)
        free(strs[i]);
    free(strs);

    return EXIT_SUCCESS;
}