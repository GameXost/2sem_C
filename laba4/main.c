#include "linked_list.h"
#include <stdio.h>

void display_menu() {
    printf("\nМеню:\n");
    printf("1. Добавить элемент в начало\n");
    printf("2. Добавить элемент в конец\n");
    printf("3. Добавить элемент по индексу\n");
    printf("4. Удалить первый элемент\n");
    printf("5. Удалить последний элемент\n");
    printf("6. Удалить элемент по индексу\n");
    printf("7. Вывести список\n");
    printf("8. Отсортировать список\n");
    printf("9. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    list our_list;
    init_list(&our_list);

    int choice, val, ind;

    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Введите значение: ");
                scanf("%d", &val);
                push(&our_list, val, 0);
                print_list(&our_list);
                break;
            case 2:
                printf("Введите значение: ");
                scanf("%d", &val);
                push(&our_list, val, size(&our_list)); // Корректно, так как индексы от 0 до size
                print_list(&our_list);
                break;
            case 3: // Добавить по индексу
                printf("Введите значение и индекс: ");
                scanf("%d %d", &val, &ind);
                push(&our_list, val, ind);
                print_list(&our_list);
                break;
            case 4:
                pop_front(&our_list);
                print_list(&our_list);
                break;
            case 5:
                pop_back(&our_list);
                print_list(&our_list);
                break;
            case 6:
                printf("Введите индекс: ");
                scanf("%d", &ind);
                pop_by_ind(&our_list, ind);
                print_list(&our_list);
                break;
            case 7:
                print_list(&our_list);
                break;
            case 8:
                insertion_sort(&our_list);
                break;
            case 9:
                clear(&our_list);
                return 0;
                break;
            default:
                printf("Неверный выбор!\n");
        }
    }

    clear(&our_list);
    return 0;
}