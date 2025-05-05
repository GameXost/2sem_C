#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int64_t number;
    char letter;
    int index; // Индекс для связи с данными
} Key;

// Сравнение двух ключей (без учета индекса)
int compareKey(const Key a, const Key b) {
    if (a.number < b.number)      return -1;
    if (a.number > b.number)      return  1;
    if (a.letter < b.letter)      return -1;
    if (a.letter > b.letter)      return  1;
    return 0;
}

// Обмен двух ключей
void swap(Key *keys, int i, int j) {
    Key tmpKey = keys[i];
    keys[i] = keys[j];
    keys[j] = tmpKey;
}

// Слияние для merge sort (только ключи)
void merge(Key *keys, Key *tempKeys, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (compareKey(keys[i], keys[j]) <= 0) {
            tempKeys[k++] = keys[i++];
        } else {
            tempKeys[k++] = keys[j++];
        }
    }
    while (i <= mid) tempKeys[k++] = keys[i++];
    while (j <= right) tempKeys[k++] = keys[j++];
    for (i = left; i <= right; i++) keys[i] = tempKeys[i];
}

// Рекурсивная сортировка слиянием (только ключи)
void mergeSort(Key *keys, Key *tempKeys, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(keys, tempKeys, left, mid);
        mergeSort(keys, tempKeys, mid+1, right);
        merge(keys, tempKeys, left, mid, right);
    }
}

// Бинарный поиск по массиву ключей
int binarySearch(Key *keys, int size, Key key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compareKey(key, keys[mid]);
        if (cmp == 0)      return mid;
        else if (cmp < 0)  right = mid - 1;
        else               left  = mid + 1;
    }
    return -1;
}

// Чтение таблицы: ключи и данные сохраняются раздельно
int readTable(const char *filename, Key **pkeys, char (**pdata)[100]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия %s\n", filename);
        return -1;
    }

    // Считаем строки
    int size = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) size++;
    rewind(file);

    if (size < 17) {
        printf("Требуется минимум 17 элементов, найдено %d\n", size);
        fclose(file);
        return -1;
    }

    // Выделяем память
    *pkeys = malloc(size * sizeof(Key));
    *pdata = malloc(size * sizeof((*pdata)[0]));

    for (int i = 0; i < size; i++) {
        if (!fgets(buffer, sizeof(buffer), file)) {
            printf("Ошибка чтения строки %d\n", i + 1);
            free(*pkeys); free(*pdata);
            fclose(file);
            return -1;
        }
        char *space = strchr(buffer, ' ');
        if (!space) {
            printf("Неверный формат в строке %d\n", i + 1);
            free(*pkeys); free(*pdata);
            fclose(file);
            return -1;
        }
        *space = '\0';
        char letter = buffer[strlen(buffer) - 1];
        buffer[strlen(buffer) - 1] = '\0';
        int64_t number = strtoll(buffer, NULL, 10);

        // Сохраняем ключ и индекс данных
        (*pkeys)[i].number = number;
        (*pkeys)[i].letter = letter;
        (*pkeys)[i].index = i; // Индекс соответствует исходной позиции данных

        // Копируем данные
        strncpy((*pdata)[i], space + 1, 99);
        (*pdata)[i][99] = '\0';
        char *nl = strchr((*pdata)[i], '\n');
        if (nl) *nl = '\0';
    }

    fclose(file);
    return size;
}

// Печать таблицы через индексы в ключах
void printTable(Key *keys, char data[][100], int size) {
    printf("+-----------+-------------------------------------------------------+\n");
    printf("|   Ключ    | Данные                                               |\n");
    printf("+-----------+-------------------------------------------------------+\n");
    for (int i = 0; i < size; i++) {
        printf("| %lld%c | %s\n",
               (long long)keys[i].number,
               keys[i].letter,
               data[keys[i].index]); // Доступ к данным через индекс в ключе
    }
    printf("+-----------+-------------------------------------------------------+\n");
}

// Реверс ключей
void reverseTable(Key *keys, int size) {
    for (int i = 0; i < size/2; i++)
        swap(keys, i, size-1-i);
}

// Перемешивание ключей
void shuffleTable(Key *keys, int size) {
    srand(time(NULL));
    for (int i = size-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(keys, i, j);
    }
}

// Проверка сортировки ключей
bool isSorted(Key *keys, int size) {
    for (int i = 0; i < size-1; i++)
        if (compareKey(keys[i], keys[i+1]) > 0) return false;
    return true;
}

// Проверка обратной сортировки ключей
bool isReverseSorted(Key *keys, int size) {
    for (int i = 0; i < size-1; i++)
        if (compareKey(keys[i], keys[i+1]) < 0) return false;
    return true;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    Key   *keys    = NULL;
    char (*data)[100] = NULL;
    int    size    = 0;
    char   filename[100];
    int    choice;
    Key    searchKey;
    char   keyInput[50];

    do {
        printf("\nМеню:\n");
        printf("1) Загрузить таблицу\n");
        printf("2) Сортировка слиянием\n");
        printf("3) Бинарный поиск по ключу\n");
        printf("4) Печать таблицы\n");
        printf("5) Реверс таблицы\n");
        printf("6) Перемешать таблицу\n");
        printf("0) Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                if (keys) { free(keys); free(data); }
                printf("Введите имя файла: ");
                if (fgets(filename, sizeof(filename), stdin)) {
                    filename[strcspn(filename, "\n")] = '\0';
                    size = readTable(filename, &keys, &data);
                    if (size > 0) printf("Загружено %d строк\n", size);
                }
                break;

            case 2:
                if (!keys) {
                    printf("Таблица не загружена!\n"); break;
                }
                printf("\nПроверка перед сортировкой:\n");
                if      (isSorted(keys, size))        printf("Таблица уже отсортирована\n");
                else if (isReverseSorted(keys, size)) printf("Таблица в обратном порядке\n");
                else                                   printf("Таблица не отсортирована\n");

                Key *tempKeys = malloc(size * sizeof(Key));
                mergeSort(keys, tempKeys, 0, size-1);
                free(tempKeys);
                printf("Сортировка завершена\n");
                break;

            case 3:
                if (!keys) {
                    printf("Таблица не загружена!\n"); break;
                }
                printf("Введите ключ (например 123A): ");
                if (fgets(keyInput, sizeof(keyInput), stdin)) {
                    keyInput[strcspn(keyInput, "\n")] = '\0';
                    int len = strlen(keyInput);
                    if (len < 2) {
                        printf("Неверный формат ключа!\n"); break;
                    }
                    searchKey.letter = keyInput[--len];
                    keyInput[len] = '\0';
                    searchKey.number = strtoll(keyInput, NULL, 10);
                    int idx = binarySearch(keys, size, searchKey);
                    if (idx != -1)
                        printf("Найдено: %lld%c %s\n",
                               (long long)keys[idx].number,
                               keys[idx].letter,
                               data[keys[idx].index]); // Доступ через индекс
                    else
                        printf("Ключ %lld%c не найден\n",
                               (long long)searchKey.number,
                               searchKey.letter);
                }
                break;

            case 4:
                if (!keys) {
                    printf("Таблица не загружена!\n"); break;
                }
                printTable(keys, data, size);
                break;

            case 5:
                if (!keys) {
                    printf("Таблица не загружена!\n"); break;
                }
                reverseTable(keys, size);
                printf("Таблица перевернута\n");
                break;

            case 6:
                if (!keys) {
                    printf("Таблица не загружена!\n"); break;
                }
                shuffleTable(keys, size);
                printf("Таблица перемешана\n");
                break;

            case 0:
                printf("Выход...\n");
                break;

            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 0);

    if (keys) free(keys);
    if (data) free(data);
    return 0;
}