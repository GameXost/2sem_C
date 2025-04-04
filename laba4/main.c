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
    printf("9. Отсортировать список\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    ArrayList list;
    list_create(&list, 4);  // Начальная вместимость

    int choice, key, value;
    size_t index;  // index типа size_t для обеспечения корректности индекса

    while (1) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите ключ и значение: ");
                scanf("%d %d", &key, &value);
                list_push_front(&list, key, value);
                break;
            case 2:
                printf("Введите ключ и значение: ");
                scanf("%d %d", &key, &value);
                list_push_back(&list, key);
            case 3:
                list_pop_front(&list);
                break;
            case 4:
                list_pop_back(&list);
                break;
            case 5:
                printf("Введите индекс, ключ и значение: ");
                scanf("%zu %d %d", &index, &key, &value);  // %zu для size_t
                if (index > list_size(&list)) {  // index не должен превышать текущий размер списка
                    printf("Ошибка: некорректный индекс!\n");
                } else {
                    list_insert(&list, index, key, value);
                }
                break;
            case 6:
                printf("Введите индекс: ");
                scanf("%zu", &index);  // %zu для size_t
                if (index >= list_size(&list)) {
                    printf("Ошибка: некорректный индекс!\n");
                } else {
                    list_erase(&list, index);
                }
                break;
            case 7:
                list_print(&list);
                break;
            case 8:
                printf("Размер списка: %zu\n", list_size(&list));
                break;
            case 9:

            case 0:
                list_destroy(&list);
                return 0;
            default:
                printf("Некорректный ввод, попробуйте снова.\n");
        }
    }
}
