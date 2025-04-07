#include "linked_list.h"
#include <stdio.h>

void insertion_sort(StaticList *list);

void showMenu() {
    printf("\nМеню:\n");
    printf("1. Добавить элемент по индексу\n");
    printf("2. Удалить элемент по индексу\n");
    printf("3. Вывести список\n");
    printf("4. Отсортировать список\n");
    printf("5. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    StaticList myList;
    init_list(&myList);

    int option, key, index;
    char value[STRING_LENGTH];

    while (1) {
        showMenu();
        if (scanf("%d", &option) != 1) break;
        switch (option) {
            case 1:
                printf("Введите ключ, значение и индекс: ");
                scanf("%d %s %d", &key, value, &index);
                insert(&myList, key, value, index);
                print_list(&myList);
                break;
            case 2:
                printf("Введите индекс для удаления: ");
                scanf("%d", &index);
                erase(&myList, index);
                print_list(&myList);
                break;
            case 3:
                print_list(&myList);
                break;
            case 4:

                insertion_sort(&myList);
                print_list(&myList);
                break;
            case 5:
                clear_list(&myList);
                return 0;
                break;
            default:
                printf("Неверный выбор!\n");
        }
    }
    clear_list(&myList);
    return 0;
}
