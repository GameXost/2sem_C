#include <stdio.h>
#include <string.h>
#include "linked_list.h"

void init_list(StaticList *list) {
    list->size = 0;
}

int empty(const StaticList *list) {
    return (list->size == 0);
}

void insert(StaticList *list, key_type key, const char *value, int index) {
    if (index < 0 || index > list->size) {
        printf("Invalid index!\n");
        return;
    }
    if (list->size >= MAX_SIZE) {
        printf("List is full!\n");
        return;
    }

    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }

    list->data[index].key = key;
    strncpy(list->data[index].value, value, STRING_LENGTH - 1);
    list->data[index].value[STRING_LENGTH - 1] = '\0';

    list->size++;
}

void erase(StaticList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index!\n");
        return;
    }

    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

int find_first_unsorted(const StaticList *list, int start) {
    for (int i = start; i < list->size; i++) {
        if (i > 0 && list->data[i].key < list->data[i - 1].key) {
            return i;
        }
    }
    return -1;
}

void move_element(StaticList *list, int from_index) {
    data_type temp = list->data[from_index];
    int j = from_index - 1;
    while (j >= 0 && list->data[j].key > temp.key) {
        list->data[j + 1] = list->data[j];
        j--;
    }
    list->data[j + 1] = temp;
}

void insertion_sort(StaticList *list) {
    for (int i = 1; i < list->size; i++) {
        int wrong_index = find_first_unsorted(list, i);
        if (wrong_index != -1) {
            move_element(list, wrong_index);
        }
    }
}

void print_list(const StaticList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("(%d: %s) ", list->data[i].key, list->data[i].value);
    }
    printf("\n");
}

void clear_list(StaticList *list) {
    list->size = 0;
}
