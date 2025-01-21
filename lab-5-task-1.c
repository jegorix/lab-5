// 1.Заполнить массив случайными числами. Удалить из массива все элементы с чётным значением.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// ф-я для проверки ввода целого числа в заданном диапазоне
int execute_verification(int min, int max);

// ф-я для создания двумерного массива случайных чисел
void create_random_array(int **array, int rows);

// ф-я для ручного ввода двумерного массива
void create_array(int **array, int rows);

// ф-я для удаления строки с минимальной суммой элементов
void delete_min_row(int **array, int *rows);

// ф-я для вывода двумерного массива
void array_output(int **array, int rows);



int main(void)
{
    printf("Введите количество строк двумерного массива: ");
    int rows = execute_verification(1, 2147483647);

    int **array = (int**) calloc(rows, sizeof(int*));

    printf("Выберите тип заполнения массива (1 - случайные значения, 0 - ручной ввод): ");
    int flag = execute_verification(0, 1);

    if (flag == 1)
    {
        create_random_array(array, rows);
    }
    else
    {
        create_array(array, rows);
    }

    printf("\nИсходный массив:\n");
    array_output(array, rows);

    delete_min_row(array, &rows);

    printf("\nМассив после удаления строки с минимальной суммой элементов:\n");
    array_output(array, rows);

    for (int i = 0; i < rows; i++)
    {
        free(array[i]);
    }
    free(array);

    return 0;
}


int execute_verification(int min, int max)
{
    int num;
    char symbol;

    while (1)
    {
        char input[100];

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Ошибка ввода! Повторите ввод: \n");
            continue;
        }

        if (sscanf(input, "%d %c", &num, &symbol) != 1)
        {
            printf("Ошибка ввода! Введите целое число: \n");
            continue;
        }

        if (num < min || num > max)
        {
            printf("Ошибка ввода! Введите число из диапазона от %d до %d: ", min, max);
            continue;
        }

        return num;
    }
}


void create_random_array(int **array, int rows)
{
    srand(time(NULL)); // инициализация генератора случайных чисел

    for (int i = 0; i < rows; i++)
    {
        int row_len = (rand() % 10) + 1; // длина строки от 1 до 10
        array[i] = (int*) calloc(row_len + 1, sizeof(int)); // +1 для завершающего нуля

        for (int j = 0; j < row_len; j++)
        {
            array[i][j] = (rand() % 98) + 1; // случайные числа от 1 до 99
        }
    }
}

void create_array(int **array, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        printf("Введите длину %d-й строки: ", i + 1);
        int row_len = execute_verification(1, 2147483647);

        array[i] = (int*) calloc(row_len + 1, sizeof(int)); // +1 для завершающего нуля

        printf("Введите элементы %d-й строки: ", i + 1);
        for (int j = 0; j < row_len; j++)
        {
            array[i][j] = execute_verification(1, 99); // ввод элементов от 1 до 99
        }
    }
}


void delete_min_row(int **array, int *rows)
{
    int min_sum = 2147483647;
    int min_row = 0;

    for (int i = 0; i < *rows; i++)
    {
        int sum = 0;
        int j = 0;

        while (array[i][j] != 0) // считаем сумму строки
        {
            sum += array[i][j];
            j++;
        }

        if (sum < min_sum)
        {
            min_sum = sum;
            min_row = i;
        }
    }

    // вывод информации о минимальной строке
    printf("\nСтрока с минимальной суммой элементов: %d, ее сумма = %d\n", min_row + 1, min_sum);

    free(array[min_row]); // освобождаем строку с минимальной суммой

    for (int i = min_row; i < *rows - 1; i++)
    {
        array[i] = array[i + 1]; // сдвигаем оставшиеся строки
    }

    (*rows)--; // уменьшаем количество строк
}


void array_output(int **array, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int j = 0;
        while (array[i][j] != 0)
        {
            printf("%d ", array[i][j]);
            j++;
        }
        printf("0\n");
    }
}