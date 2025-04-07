#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void init_list(list *cur_list) {
    cur_list->header = NULL;
    cur_list->size = 0;
}

int empty(list *cur_list) {
    return cur_list->size == 0;
}

node *find_by_index(node *cur, int need_ind) {
    for (int i = 0; cur != NULL && i < need_ind; i++) {
        cur = cur->next;
    }
    return cur;
}

void push(list *cur_list, int val, int ind) {
    if (ind < 0 || ind > cur_list->size) {
        printf("Неверный индекс\n");
        return;
    }

    node *new_node = malloc(sizeof(node));
    new_node->value = val;
    new_node->next = NULL;

    if (ind == 0) {
        new_node->next = cur_list->header;
        cur_list->header = new_node;
    } else {
        node *prev = find_by_index(cur_list->header, ind - 1);
        if (prev == NULL) {
            free(new_node);
            return;
        }
        new_node->next = prev->next;
        prev->next = new_node;
    }
    cur_list->size++;
}
int size(list *cur_list) {
    return cur_list->size;
}

void pop_front(list *cur_list) {
    if (empty(cur_list)) return;

    node *temp = cur_list->header;
    cur_list->header = temp->next;
    free(temp);
    cur_list->size--;
}

void pop_back(list *cur_list) {
    if (empty(cur_list)) return;

    if (cur_list->size == 1) {
        pop_front(cur_list);
        return;
    }

    node *prev = find_by_index(cur_list->header, cur_list->size - 2);
    free(prev->next);
    prev->next = NULL;
    cur_list->size--;
}

void pop_by_ind(list *cur_list, int ind) {
    if (ind < 0 || ind >= cur_list->size) return;
    if (ind == 0) {
        pop_front(cur_list);
        return;
    }
    node *prev = find_by_index(cur_list->header, ind - 1);
    node *temp = prev->next;
    prev->next = temp->next;
    free(temp);
    cur_list->size--;
}

void clear(list *cur_list) {
    while (!empty(cur_list)) {
        pop_front(cur_list);
    }
}

void print_list(list *cur_list) {
    node *current = cur_list->header;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
}
    printf("\n");
}

void el_by_ind(list *cur_list, int ind) {
    if (ind < 0 || ind >= cur_list->size) {
        printf("Неверный индекс\n");
        return;
    }
    node *n = find_by_index(cur_list->header, ind);
    printf("Значение %d на индексе %d\n", n->value, ind);
}

void insertion_sort(list *cur_list) {
    if (cur_list->size < 2) return;

    node *sorted = NULL; // начало нового отсортированного списка
    node *current = cur_list->header;

    while (current != NULL) {
        node *next = current->next;

        // вставляем current в нужное место в отсортированном списке
        if (sorted == NULL || current->value < sorted->value) {
            current->next = sorted;
            sorted = current;
        } else {
            node *temp = sorted;
            while (temp->next != NULL && temp->next->value < current->value) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    cur_list->header = sorted;
}
