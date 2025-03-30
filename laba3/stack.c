
#include <stdio.h>
#include <stdlib.h>

enum Type {
    NONE,
    OPERATOR,
    NUMBER
};
typedef enum Type Type;

enum Sost {
    IN_NUMBER,
    NOT_IN_NUMBER,
};

typedef enum Sost Sost;

struct stack {
    Type type;
    int val;
    char oper;
    struct stack* prev;
};
typedef struct stack stack;


stack* push_num(stack* header, int val){
    stack* new_stack = malloc(sizeof(stack));
    new_stack->type = NUMBER;
    new_stack->val = val;
    new_stack->prev = header;
    return new_stack;
}
stack* push_oper(stack* header, char oper){
    stack* new_stack = malloc(sizeof(stack));
    new_stack->type = OPERATOR;
    new_stack->oper = oper;
    new_stack->prev = header;
    return new_stack;
}

stack* pop(stack* header){
    if (header == NULL) {
        return 0;
    }
    stack* new_header = header->prev;
    free(header);
    return new_header;
}


Type front_type(stack* header) {
    if (header == NULL) {
        return NONE;
    }
    return header -> type;
}
int front_val(stack* header) {
    if (header == NULL) {
        return NONE;
    }
    return header -> val;
}

char front_oper(stack* header) {
    if (header == NULL) {
        return NONE;
    }
    return header -> oper;
}

int is_number(char c) {
    return ('0' <= c && c <= '9');
}

int main(){
    stack* postfix = NULL;
    stack* operators = NULL;
    char c;
    Sost cur_sost = NOT_IN_NUMBER;
    int cur_num = 0;
    int zn = 1;
    while((scanf("%c", &c) != EOF)){
        if (c == '\n') {
            break;
        }
        if (is_number(c)) {
            if (cur_sost == NOT_IN_NUMBER) {
                cur_sost = IN_NUMBER;
                cur_num = c - '0';
                cur_num *= zn;
                zn = 1;
            } else {
                cur_num = cur_num * 10 + c - '0';
            }
        } else {
            if (cur_sost == NOT_IN_NUMBER) {
                if (c == '-') {
                    zn = -1;
                } else if (c == '(') {
                    push_oper(operators, c);
                } else {
                    return 1;
                }
            } else {
                push_num(postfix, cur_num);
                cur_num = 0;

                if (front_oper(operators) == NONE) {
                    push_oper(operators, c);
                } else {
                    if (c == '+' || c == '-') {
                        while (front_oper(operators) != NONE && front_oper(operators) != '-' && front_oper(operators) != '(' && front_oper(operators) != '+') {
                            push_oper(operators, front_oper(operators));
                            pop(operators);
                        }
                        push_oper(operators, c);
                    } else if (c == '*') {
                        push_oper(operators, c);
                    } else if (c == ':') {
                        while (front_oper(operators) != NONE && front_oper(operators) != '(' && front_oper(operators) != '+') {}

                    }
            }
            }
        }
    }
}
