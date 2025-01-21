// Дан двумерный массив ненулевых целых чисел. Определить максимально длинную последовательности положительных чисел.
//Массив просматривается построчно сверху вниз, а в каждой строке - слева направо.
//Сохранение знака при переходе на новую строку также учитывать.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int execute_verification(int min, int max);
void create_random_array(int **array, int length);
void create_array(int **array, int *length);
void print_array(int **array, int *length);
int find_sequence(int **array, int *length);


int main(void) {
    printf("Введите количество строк двумерного массива: ");
    int row_count = execute_verification(1, 2147483647);

    int **array = (int**) calloc(row_count, sizeof(int*));

    printf("Выберите тип заполнения массива: (1 - случайные значения, 0 - ручной ввод)\n");
    int flag = execute_verification(0, 1);

    if (flag == 1) {
        create_random_array(array, row_count);
    } else {
        create_array(array, &row_count);
    }

    print_array(array, &row_count);

    printf("Максимальная длина последовательности положительных элементов = %d\n", find_sequence(array, &row_count));

    for (int i = 0; i < row_count; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}



int execute_verification(int min, int max) {
    int num;
    char symbol;

    while (1) {
        char input[100];

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Ошибка ввода! Повторите ввод: \n");
            continue;
        }

        if (sscanf(input, "%d %c", &num, &symbol) != 1) {
            printf("Ошибка ввода! Введите целое число: \n");
            continue;
        }

        if (num < min || num > max) {
            printf("Ошибка ввода! Введите число из диапазона от %d до %d: ", min, max);
            continue;
        }

        return num;
    }
}



void create_array(int **array, int *length) {
    for (int i = 0; i < *length; i++) {
        printf("Введите длину %d-й строки: ", i + 1);
        int row_len = execute_verification(1, 2147483647); // проверка длины строки

        array[i] = (int*) calloc(row_len + 1, sizeof(int));  // плюс один для нулевого элемента в конце строки

        printf("Введите элементы %d-й строки: ", i + 1);
        for (int j = 0; j < row_len; j++) {
            array[i][j] = execute_verification(-2147483648, 2147483647);
        }
    }
}



void create_random_array(int **array, int length) {
    srand((unsigned int)time(NULL));  // инициализация генератора случайных чисел
    for (int i = 0; i < length; i++) {
        int row_len;

        // случайная длина строки
        row_len = (rand() % 10) + 1;  // длина от 1 до 10
        array[i] = (int*) calloc(row_len + 1, sizeof(int));  // плюс один для нулевого элемента в конце строки

        // заполняем строку случайными значениями
        printf("Заполнение %d-й строки случайными значениями (ее длина = %d):\n", i + 1, row_len);
        for (int j = 0; j < row_len; j++) {
            array[i][j] = (rand() % 199) - 99;  // заполняем случайными значениями от -99 до 99
        }
    }
}



int find_sequence(int **array, int *length) {
    int max_length = 0;
    int current_length = 0;
    int flag = 0;

    for (int i = 0; i < *length; i++) {
        int j = 0;

        while (array[i][j] != 0) {
            if (array[i][j] > 0) {
                current_length++;
                flag = 1; // надежда, что последний элемент положительный (условное сохранение)
            } else {
                if (current_length > max_length) {
                    max_length = current_length;
                }
                current_length = 0;
                flag = 0; // надежда, что последний элемент отрицательный, чтобы проверить в будущем след строку
            }
            j++;
        }

        if (!flag) { // флаг нужен ради того, чтобы проверить начало следующей строки
            current_length = 0;
        }
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}




void print_array(int **array, int *length) {
    printf("Исходный массив:\n");
    for (int i = 0; i < *length; i++) {
        int j = 0;
        while (array[i][j] != 0) {
            printf("%d ", array[i][j]);
            j++;
        }
        printf("\n");
    }
}