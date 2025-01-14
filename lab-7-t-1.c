#include <stdio.h>
#include <stdlib.h>

void execute_verification(int* num, int min, int max)
{
    do
    {
        char input[100];

        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Ошибка ввода! Повторите ввод: \n");
            continue;
        }

        if(sscanf(input,"%d", num) != 1)
        {
            printf("Ошибка ввода! Введите целое число: \n");
            continue;
        }

        if(*num < min || *num > max)
        {
            printf("Ошибка ввода! Введите число из диапазона от %d до %d: ", min, max);
        }
        

    } while ( *num < min || *num > max);
    
}



char* user_text_input()
{
    char* str = NULL;
    char ch;

    size_t length = 0;
    size_t capacity = 10;

    str = malloc(capacity * sizeof(char));

    while( (ch = getchar()) != '\n' && ch != EOF )
    {
        if(length + 1 >= capacity)
        {
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
        }

        str[length++] = ch;
    }
    str[length] = '\0';

    return str;
}



int words_count(char* str)
{
    int in_word = 0;
    int count = 0;

    while(*str)
    {
        if(*str != ' ')
        {
            if(!in_word)
            {
                in_word = 1;
                count++;
            }
        }

        else{in_word = 0;}

        str++;

    }

    return count;

}



char** sep_words(char* str, int count)
{

    char** words = (char**) malloc (count * sizeof(char*));
    int index = 0;

    while(*str)
    {
        while(*str == ' ')
        {
            str++;
        }


        if(*str)
        {
            char* start = str;

            while(*str && *str != ' ')
            {
                str++;
            }

            int length = str - start;
            words[index] = malloc((length + 1) * sizeof(char));

            for(int i = 0; i < length; i++)
            {
                words[index][i] = start[i];
            }

            words[index][length] = '\0';
            index++;

        }
    }
    return words;

}

void words_output(char** words, int count, int k, int m)
{
    for(int i = 0; i < count; i++)
    {
        if(i == k)
        {
            printf("%s ", words[m]);
        }

        else if(i == m)
        {
            printf("%s ", words[k]);
        }

        else
        {
            printf("%s ", words[i]);
        }
    }
    printf("\n");
}






int main(void)
{
    int k = 0;
    int m = 0;
    
    printf("Введите строку:\n");

    char* text = user_text_input();

    // printf("%s\n", text);
    
    int (*count_of_words) (char*); 
    count_of_words = words_count;

    //int count = words_count(text);
    // printf("%d\n", count);

    char** words = sep_words(text, count_of_words(text));

    

    printf("Введите какое по счету слово мы будем менять (от 1 до %d):\n", count_of_words(text));
    execute_verification(&k, 1, count_of_words(text));

    printf("Введите на какое по счету слово мы будем менять (от 1 до %d):\n", count_of_words(text));
    execute_verification(&m, 1, count_of_words(text));

    words_output(words, count_of_words(text), k-1, m-1);


    for(int i = 0; i < count_of_words(text); i++)
    {
        free(words[i]);
    }
    free(words);



    return 0;
}