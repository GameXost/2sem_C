#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Функция для вставки элемента в отсортированную часть списка
Node* sortedInsert(Node* head, Node* newNode) {
    if (head == NULL || newNode->data <= head->data) {
        newNode->next = head;
        return newNode;
    }
    
    Node* current = head;
    while (current->next != NULL && current->next->data < newNode->data) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    
    return head;
}

// Функция сортировки вставкой
Node* insertionSort(Node* head) {
    Node* sorted = NULL; // Отсортированная часть списка
    Node* current = head;
    
    while (current != NULL) {
        Node* next = current->next;
        sorted = sortedInsert(sorted, current);
        current = next;
    }
    
    return sorted;
}

// Функция для добавления элемента в начало списка
void push(Node** headRef, int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = *headRef;
    *headRef = newNode;
}

// Функция для вывода списка
void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Освобождение памяти
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    
    push(&head, 5);
    push(&head, 3);
    push(&head, 8);
    push(&head, 1);
    push(&head, 2);
    
    printf("Исходный список:\n");
    printList(head);
    
    head = insertionSort(head);
    
    printf("Отсортированный список:\n");
    printList(head);
    
    freeList(head);
    return 0;
}
