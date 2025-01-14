// //3.Отсортировать методом Хоара массив строк по количеству слов состоящим из четного количества символов.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quick_sort(int* array, int* indexies, int start, int finish);




int execute_verification(int min, int max)
{
    int num;
    do
    {
        char input[100];

        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Ошибка ввода! Повторите ввод: \n");
            continue;
        }

        if(sscanf(input,"%d", &num) != 1)
        {
            printf("Ошибка ввода! Введите целое число: \n");
            continue;
        }

        if(num < min || num > max)
        {
            printf("Ошибка ввода! Введите число из диапазона от %d до %d: ", min, max);
        }
        

    } while ( num < min || num > max);
    
    return num;
}






char* string_create()
{
    char* str = NULL;
    char ch;
    size_t capacity = 10;
    size_t length = 0;
    str = malloc(capacity * sizeof(char));

    while( (ch = getchar()) != '\n' && ch != EOF)
    {
        if(length + 1 > capacity)
        {
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
        }

        str[length++] = ch;
    }

    str[length] = '\0';

    return str;
}







int even_words_identify(char* str)
{
    int even_count = 0;

    while(*str)
    {
        while(*str == ' ')
        {
            str++;
        }
    
        if(*str && *str != ' ')
        {
            char* start = str;

            
            while(*str && *str != ' ')
            {
                str++;
            }

            int length = str - start;

            if(length % 2 == 0)
            {
                even_count++;
            }
        }

    }

    return even_count;


}







int main(void)
{

printf("Введите количество строк текста: ");
int string_count = execute_verification(1,50);


char** text = malloc(string_count * sizeof(char*));



for(int i = 0; i < string_count; i++)
{
    printf("Введите %d-ю строку:\n", i+1);
    text[i] = string_create();
}

int* even_count = malloc(string_count * sizeof(int*));



for(int i = 0; i < string_count; i++)
{
    even_count[i] = even_words_identify(text[i]);

}

int* indexies = malloc(string_count * sizeof(int));
for(int i = 0; i < string_count; i++)
{
    indexies[i] = i;
}


quick_sort(even_count, indexies, 0, string_count-1);

printf("Сортировка по количеству четных слов в каждой строке:\n");
for(int i = 0; i < string_count; i++)
{
   printf("%s (%d)\n", text[indexies[i]], even_count[indexies[i]]);
}


for(int i = 0; i < string_count; i++)
{
    free(text[i]);
}
free(text);
free(indexies);
free(even_count);



return 0;

}





// void hoar_sort(int* array, int left, int right)
// {
//     if(left >= right) return;

//     int i = left;
//     int j = right;

//     int pointer = (left + right) / 2;


//     while(i <= j)
//     {
//         while(array[i] < array[pointer]) i++;
//         while(array[j] > array[pointer]) j--;

//         if(i <= j)
//         {
//             int temp = array[i];
//             array[i] = array[j];
//             array[j] = temp;

//             i++;
//             j--;
//         }

//     }

//     hoar_sort(array, i, right);
//     hoar_sort(array, left, j);
// }





void quick_sort(int* array, int* indexies, int start, int finish)
{
    if( start > finish)
    {
        return;
    }

    int i = start;
    int j = finish;
    int point = indexies[(start + finish) / 2];

    while(array[indexies[i]] < array[point])
    {
        i++;
    }

    while(array[indexies[j]] > array[point])
    {
        j--;
    }

    if( i <= j )
    {
        int temp = indexies[i];
        indexies[i] = indexies[j];
        indexies[j] = temp;
        i++;
        j--;
    }


    quick_sort(array, indexies, start, j);
    quick_sort(array, indexies, i, finish);


}