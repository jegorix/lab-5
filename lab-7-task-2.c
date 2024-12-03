//2. Даны строки S и S0. Найти количество вхождений строки S0 в строку S.

// abc --- abcabcabc

#include <stdio.h>
#include <stdlib.h>


int str_len(char* str_len, int i); // функция для поиска длины строки
int counter_in_string(char* array_1, char* array_2, int len_1, int len_2); // функция для поиска количества вхождений

int main(void)
{
    int MAX_TEXT_LENGHTH = 50;

    // printf("Введите ограничение по длине строк: ");
    // scanf("%d", &MAX_TEXT_LENGHTH);

char* str_first = (char*) calloc(MAX_TEXT_LENGHTH, sizeof(char) );
char* str_second = (char*) calloc(MAX_TEXT_LENGHTH, sizeof(char) );

printf("Введите строку, в которой будут элементы, которые мы будем искать:\n");
fgets(str_first, MAX_TEXT_LENGHTH, stdin);

printf("Введите строку, в которой мы будем искать количество вхождений:\n");
fgets(str_second, MAX_TEXT_LENGHTH, stdin);

// определим длины строк

int length_first = str_len(str_first, 0);
int length_second = str_len(str_second, 0);

// определим количество вхождений

printf("Количество вхождений первой строки во вторую = %d\n", counter_in_string(str_first, str_second, length_first, length_second) );





    return 0;
}



int str_len(char* str, int i)
{
    if(str[i] == '\0' || str[i] == '\n'){return 0;}

    return 1 + str_len(str, i + 1);


}




int counter_in_string(char* array_1, char* array_2, int len_1, int len_2)

{
int flag = 0;

    if(len_1 > len_2){return 0;}



    for(int i = 0; i < len_1; i++)

    {
        if(array_1[i] == array_2[i]) {flag = 1;}

        else{flag = 0; break;}
    }   
    

    if(flag)
    {
        return 1 + counter_in_string(array_1, array_2 + 1, len_1, len_2 - 1); // сдвиг указателя на 1, чтобы проверять следущий элемент
    }


    if(!flag)
    {
        return counter_in_string(array_1, array_2 + 1, len_1, len_2 - 1); // len_2 - 1, чтобы двигаться рекурсивно
    }














// for(int j = 0; j < len_2; j++)
// {

//     for(int i = 0; i < len_1; i++)

//     {
//         if(array_1[i] == array_2[i + j]) {flag = 1;}

//         else{flag = 0;}
//     }   


// if(flag == 1){counter++;}

// }

//return counter;


}





