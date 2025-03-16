#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdbool.h>  // Для типа bool
#include <stddef.h>   // Для типа size_t

// Определение структуры узла списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Определение структуры списка
typedef struct {
    Node* head;
} SinglyLinkedList;

// Операции над списком
void list_create(SinglyLinkedList *);
bool list_is_empty(const SinglyLinkedList *);
void list_push_front(SinglyLinkedList *, int);
void list_push_back(SinglyLinkedList *, int);
void list_pop_front(SinglyLinkedList *);
void list_pop_back(SinglyLinkedList *);
void list_print(const SinglyLinkedList *);
size_t list_size(const SinglyLinkedList *);
void list_insert(SinglyLinkedList *, size_t, int);
void list_erase(SinglyLinkedList *, size_t);
void list_insertion_sort(SinglyLinkedList *list);

#endif // SINGLY_LINKED_LIST_H
