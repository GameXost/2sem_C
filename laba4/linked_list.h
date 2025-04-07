#ifndef __STATIC_LIST_H__
#define __STATIC_LIST_H__

#define MAX_SIZE 100
#define STRING_LENGTH 50

typedef int key_type;
typedef char value_type[STRING_LENGTH];

typedef struct {
    key_type key;
    value_type value;
} data_type;

typedef struct {
    data_type data[MAX_SIZE];
    int size;
} StaticList;

void init_list(StaticList *list);
int empty(const StaticList *list);
void insert(StaticList *list, key_type key, const char *value, int index);
void erase(StaticList *list, int index);
void print_list(const StaticList *list);
void clear_list(StaticList *list);
int find_first_unsorted(const StaticList *list, int start);
void move_element(StaticList *list, int from_index);

#endif
