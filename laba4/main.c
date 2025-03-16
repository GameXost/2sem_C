#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("\nМеню:\n");
    printf("1. Добавить элемент в начало\n");
    printf("2. Добавить элемент в конец\n");
    printf("3. Удалить первый элемент\n");
    printf("4. Удалить последний элемент\n");
    printf("5. Вставить элемент по индексу\n");
    printf("6. Удалить элемент по индексу\n");
    printf("7. Вывести список\n");
    printf("8. Вывести размер списка\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    SinglyLinkedList list;
    list_create(&list);
    int choice, value, index;

    while (1) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение: ");
                scanf("%d", &value);
                list_push_front(&list, value);
                break;
            case 2:
                printf("Введите значение: ");
                scanf("%d", &value);
                list_push_back(&list, value);
                break;
            case 3:
                list_pop_front(&list);
                break;
            case 4:
                list_pop_back(&list);
                break;
            case 5:
                printf("Введите индекс и значение: ");
                scanf("%d %d", &index, &value);
                list_insert(&list, index, value);
                break;
            case 6:
                printf("Введите индекс: ");
                scanf("%d", &index);
                list_erase(&list, index);
                break;
            case 7:
                list_print(&list);
                break;
            case 8:
                printf("Размер списка: %zu\n", list_size(&list));
                break;
            case 9:
            printf("9. Отсортировать список по возрастанию:\n");
                list_insertion_sort(&list);
                break;
            case 0:
                return 0;
            default:
                printf("Некорректный ввод, попробуйте снова.\n");
        }
    }
}