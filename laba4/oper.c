#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// Инициализация списка
void list_create(SinglyLinkedList *list) {
    list->head = NULL;
}

// Проверка, пуст ли список
bool list_is_empty(const SinglyLinkedList *list) {
    return list->head == NULL;
}

// Добавление элемента в начало
void list_push_front(SinglyLinkedList *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
}

// Добавление элемента в конец
void list_push_back(SinglyLinkedList *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = value;
    new_node->next = NULL;
    
    if (list_is_empty(list)) {
        list->head = new_node;
        return;
    }
    
    Node *temp = list->head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Удаление первого элемента
void list_pop_front(SinglyLinkedList *list) {
    if (list_is_empty(list)) return;
    Node *temp = list->head;
    list->head = temp->next;
    free(temp);
}

// Удаление последнего элемента
void list_pop_back(SinglyLinkedList *list) {
    if (list_is_empty(list)) return;
    
    if (!list->head->next) {
        free(list->head);
        list->head = NULL;
        return;
    }
    
    Node *temp = list->head;
    while (temp->next->next) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Вывод списка
void list_print(const SinglyLinkedList *list) {
    Node *temp = list->head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Получение размера списка
size_t list_size(const SinglyLinkedList *list) {
    size_t count = 0;
    Node *temp = list->head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Вставка элемента по индексу
void list_insert(SinglyLinkedList *list, size_t index, int value) {
    if (index == 0) {
        list_push_front(list, value);
        return;
    }
    
    Node *temp = list->head;
    for (size_t i = 0; temp && i < index - 1; i++) {
        temp = temp->next;
    }
    
    if (!temp) return;
    
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = value;
    new_node->next = temp->next;
    temp->next = new_node;
}

// Удаление элемента по индексу
void list_erase(SinglyLinkedList *list, size_t index) {
    if (list_is_empty(list)) return;
    
    if (index == 0) {
        list_pop_front(list);
        return;
    }
    
    Node *temp = list->head;
    for (size_t i = 0; temp->next && i < index - 1; i++) {
        temp = temp->next;
    }
    
    if (!temp->next) return;
    
    Node *to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);
}

// Сортировка списка вставками
void list_insertion_sort(SinglyLinkedList *list) {
    if (!list->head || !list->head->next) return;
    
    Node *sorted = NULL;
    Node *current = list->head;
    
    while (current) {
        Node *next = current->next;
        
        if (!sorted || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        
        current = next;
    }
    
    list->head = sorted;
}