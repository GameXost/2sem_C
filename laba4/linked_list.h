#ifndef __list_H__
#define __list_H__

struct node {
    int value;
    struct node *next;
};
typedef struct node node;

struct list {
    node *header;
    int size;
};
typedef struct list list;

void init_list(list *cur_list);
int empty(list *cur_list);
node *find_by_index(node *cur, int need_ind);
void push(list *cur_list, int val, int ind);
void pop_front(list *cur_list);
void pop_back(list *cur_list);
void pop_by_ind(list *cur_list, int ind);
int size(list *cur_list);
void el_by_ind(list *cur_list, int ind);
void clear(list *cur_list);
void print_list(list *cur_list);
int size(list *cur_list);
void insertion_sort(list *cur_list);

#endif