#ifndef __UDT_H__
#define __UDT_H__

#include <stdbool.h>
#include <stddef.h>

#define MAX_CAPACITY 100 // Фиксированный размер массива

// Структура данных элемента
typedef struct {
    int key;
    int value;
} data_type;

// Узел списка (хранится в массиве)
typedef struct {
    data_type data;
    int next; // Индекс следующего элемента
} list_node;

// Основная структура списка
typedef struct {
    list_node nodes[MAX_CAPACITY]; // Статический массив узлов
    int head;                     // Индекс первого элемента основного списка
    int free_head;                // Индекс первого свободного элемента
    size_t size;                  // Текущий размер основного списка
} udt;

// Инициализация списка
void udt_create(udt *list);

// Проверка на пустоту
bool udt_is_empty(const udt *list);

// Добавление в начало
void udt_push_front(udt *list, data_type data);

// Удаление по ключу (рекурсивная реализация)
void udt_erase(udt *list, const int key);

// Вывод списка
void udt_print(const udt *list);

// Получение размера
size_t udt_size(const udt *list);

// Другие функции (реализация в .c файле)
void udt_push_back(udt *list, data_type data);
void udt_pop_front(udt *list);
void udt_pop_back(udt *list);
void udt_insert(udt *list, const data_type data);

#endif