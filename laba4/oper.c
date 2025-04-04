#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"



void udt_create(udt *list){
    list->head = -1;
    list->free_head = 0;
    list->size = 0;

    for (int i = 0; i < MAX_CAPACITY - 1; i++){
        list->nodes[i].next = i + 1;
    }
    list->nodes[MAX_CAPACITY - 1].next = -1;
}


bool is_empty(udt *list){
    return list->size == 0;
}

void udt_push_front(udt *list, data_type data){
    if (list->size == MAX_CAPACITY){
        return;
    }

    int index = list->free_head;
    list->free_head = list->nodes[index].next;  // сдвигаем индекс на следующий

    list->nodes[index].data = data;
    list->nodes[index].next = list->head;
    list->head = index;
    list->size++;
}

// Удаление из начала
void udt_pop_front(udt *list) {
    if (udt_is_empty(list)) return;

    int old_head = list->head;
    list->head = list->nodes[old_head].next;

    // Возврат элемента в список свободных
    list->nodes[old_head].next = list->free_head;
    list->free_head = old_head;
    list->size--;
}

// Добавление в конец
void udt_push_back(udt *list, data_type data) {
    if (list->free_head == -1) return;

    int new_index = list->free_head;
    list->free_head = list->nodes[new_index].next;

    list->nodes[new_index].data = data;
    list->nodes[new_index].next = -1;

    if (udt_is_empty(list)) {
        list->head = new_index;
    } else {
        // Поиск последнего элемента
        int current = list->head;
        while (list->nodes[current].next != -1) {
            current = list->nodes[current].next;
        }
        list->nodes[current].next = new_index;
    }
    list->size++;
}


// Рекурсивное удаление по ключу
static void erase_recursive(udt *list, int current, int prev, int key) {
    if (current == -1) return;

    if (list->nodes[current].data.key == key) {
        if (prev == -1) {
            list->head = list->nodes[current].next;
        } else {
            list->nodes[prev].next = list->nodes[current].next;
        }

        // Возвращаем узел в список свободных
        list->nodes[current].next = list->free_head;
        list->free_head = current;
        list->size--;
        return;
    }

    erase_recursive(list, list->nodes[current].next, current, key);
}

void udt_erase(udt *list, const int key) {
    erase_recursive(list, list->head, -1, key);
}

void udt_print(const udt *list){
    if (is_empty(list)){
        printf("Empty list\n");
        return;
    }
    int current = list->head;
    while (current != -1) {
        printf("Ключ: %d, Значение: %d\n",
               list->nodes[current].data.key,
               list->nodes[current].data.value);
        current = list->nodes[current].next;
    }
}

size_t udt_size(const udt *list) {
    return list->size;
}

