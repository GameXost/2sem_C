#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { node_number, node_operator, node_variable } NodeType;

typedef struct TreeNode {
    NodeType type;
    union {
        double number;
        char op;
        char variable;
    } data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode **data;
    int top;
    int capacity;
} Stack;

Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = (TreeNode **) malloc(capacity * sizeof(TreeNode *));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int isEmpty(Stack *stack) { return stack->top == -1; }

void push(Stack *stack, TreeNode *node) {
    if (stack->top == stack->capacity - 1) {
        printf("Переполнение стека\n");
        exit(1);
    }
    stack->data[++stack->top] = node;
}

TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Переполнение стека\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

TreeNode *peek(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->data[stack->top];
}

TreeNode *createNumberNode(double value) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    node->type = node_number;
    node->data.number = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *createOperatorNode(char op) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->type = node_operator;
    node->data.op = op;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *createVariableNode(char var) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->type = node_variable;
    node->data.variable = var;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

TreeNode *buildExpressionTree(const char *expression) {
    Stack *values = createStack(strlen(expression));
    Stack *operators = createStack(strlen(expression));

    for (int i = 0; expression[i]; i++) {
        if (expression[i] == ' ') {
            continue;
        }

        if (expression[i] == '(') {
            push(operators, createOperatorNode(expression[i]));
        } else if (expression[i] == ')') {
            while (!isEmpty(operators) && peek(operators)->data.op != '(') {
                TreeNode *opNode = pop(operators);
                opNode->right = pop(values);
                opNode->left = pop(values);
                push(values, opNode);
            }
            pop(operators);
        } else if (isdigit(expression[i]) || expression[i] == '.') {
            double num = 0;
            int dot = 0;
            double fraction = 1.0;

            while (expression[i] && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    dot = 1;
                } else {
                    if (dot) {
                        fraction *= 0.1;
                        num += (expression[i] - '0') * fraction;
                    } else {
                        num = num * 10 + (expression[i] - '0');
                    }
                }
                i++;
            }
            i--;

            push(values, createNumberNode(num));
        } else if (isalpha(expression[i])) {
            push(values, createVariableNode(expression[i]));
        } else {
            TreeNode *opNode = createOperatorNode(expression[i]);

            while (!isEmpty(operators) && getPriority(peek(operators)->data.op) >= getPriority(expression[i])) {
                TreeNode *topOp = pop(operators);
                topOp->right = pop(values);
                topOp->left = pop(values);
                push(values, topOp);
            }

            push(operators, opNode);
        }
    }

    while (!isEmpty(operators)) {
        TreeNode *opNode = pop(operators);
        opNode->right = pop(values);
        opNode->left = pop(values);
        push(values, opNode);
    }

    TreeNode *result = pop(values);
    free(values->data);
    free(values);
    free(operators->data);
    free(operators);

    return result;
}


bool needParenthesesLeft(TreeNode *parent, TreeNode *child) {
    if (child == NULL || parent == NULL)
        return false;

    if (child->type != node_operator)
        return false;

    if (getPriority(parent->data.op) > getPriority(child->data.op)) {
        return true;
    }

    return false;
}

bool needParenthesesRight(TreeNode *parent, TreeNode *child) {
    if (child == NULL || parent == NULL)
        return false;

    if (child->type != node_operator)
        return false;

    if (getPriority(parent->data.op) > getPriority(child->data.op)) {
        return true;
    }

    if (getPriority(parent->data.op) == getPriority(child->data.op)) {
        if (parent->data.op == '-' || parent->data.op == '/') {
            return true;
        }
    }

    return false;
}

void printInfix(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    if (root->left) {
        if (needParenthesesLeft(root, root->left)) {
            printf("(");
            printInfix(root->left);
            printf(")");
        } else {
            printInfix(root->left);
        }
    }

    switch (root->type) {
        case node_number:
            if (root->data.number == (int) root->data.number) {
                printf("%d", (int) root->data.number);
            } else {
                printf("%g", root->data.number);
            }
            break;
        case node_operator:
            printf("%c", root->data.op);
            break;
        case node_variable:
            printf("%c", root->data.variable);
            break;
    }

    if (root->right) {
        if (needParenthesesRight(root, root->right)) {
            printf("(");
            printInfix(root->right);
            printf(")");
        } else {
            printInfix(root->right);
        }
    }
}

void printTree(TreeNode *root, int level) {
    if (root == NULL) {
        return;
    }

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    switch (root->type) {
        case node_number:
            if (root->data.number == (int) root->data.number) {
                printf("%d\n", (int) root->data.number);
            } else {
                printf("%g\n", root->data.number);
            }
            break;
        case node_operator:
            printf("%c\n", root->data.op);
            break;
        case node_variable:
            printf("%c\n", root->data.variable);
            break;
    }

    printTree(root->left, level + 1);
}

void freeTree(TreeNode *root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void printMenu() {
    printf("\nМеню:\n");
    printf("1. Ввести выражение\n");
    printf("2. Вывести выражение\n");
    printf("3. Упростить выражение\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");
}

TreeNode *copyTree(TreeNode *root) {
    if (root == NULL)
        return NULL;

    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (!newNode) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    newNode->type = root->type;
    switch (root->type) {
        case node_number:
            newNode->data.number = root->data.number;
            break;
        case node_operator:
            newNode->data.op = root->data.op;
            break;
        case node_variable:
            newNode->data.variable = root->data.variable;
            break;
    }

    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}

TreeNode *applyDistributiveInternal(TreeNode *node) {
    if (node == NULL) {
        return NULL;
    }

    node->left = applyDistributiveInternal(node->left);
    node->right = applyDistributiveInternal(node->right);

    if (node->type == node_operator && node->data.op == '*') {
        TreeNode *left = node->left;
        TreeNode *right = node->right;

        // Случай: (число/переменная) * (A - B)
        if (left != NULL && (left->type == node_variable || left->type == node_number) && right != NULL &&
            right->type == node_operator && right->data.op == '-') {

            TreeNode *copyLeft1 = copyTree(left);
            TreeNode *copyLeft2 = copyTree(left);
            TreeNode *a = copyTree(right->left);
            TreeNode *b = copyTree(right->right);

            // Собираем новую структуру: (copyLeft1 * a) - (copyLeft2 * b)
            TreeNode *leftA = createOperatorNode('*');
            leftA->left = copyLeft1;
            leftA->right = a;

            TreeNode *leftB = createOperatorNode('*');
            leftB->left = copyLeft2;
            leftB->right = b;

            TreeNode *newNode = createOperatorNode('-');
            newNode->left = leftA;
            newNode->right = leftB;

            // Освобождаем текущий узел (*), который уже не используется
            free(node);
            return newNode;
        } else if (right != NULL && (right->type == node_variable || right->type == node_number) && left != NULL &&
                 left->type == node_operator && left->data.op == '-') {

            // Создаем две копии правого поддерева для использования в обеих частях выражения
            TreeNode *copyRight1 = copyTree(right);
            TreeNode *copyRight2 = copyTree(right);
            TreeNode *a = copyTree(left->left);
            TreeNode *b = copyTree(left->right);

            TreeNode *aRight = createOperatorNode('*');
            aRight->left = a;
            aRight->right = copyRight1;

            TreeNode *bRight = createOperatorNode('*');
            bRight->left = b;
            bRight->right = copyRight2;

            TreeNode *newNode = createOperatorNode('-');
            newNode->left = aRight;
            newNode->right = bRight;

            free(node);
            return newNode;
        }
    }

    return node;
}


TreeNode *applyDistributive(TreeNode *node) {
    if (node == NULL) {
        return NULL;
    }
    TreeNode *treeCopy = copyTree(node);
    return applyDistributiveInternal(treeCopy);
}


int main() {
    char expression[256] = "";
    TreeNode *root = NULL;
    TreeNode *simplifiedRoot = NULL;
    int choice;
    bool hasExpression = false;

    do {
        printMenu();
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;

        switch (choice) {
            case 1:
                printf("Введите арифметическое выражение: ");
                fgets(expression, sizeof(expression), stdin);
                expression[strcspn(expression, "\n")] = '\0';

                if (simplifiedRoot) {
                    freeTree(simplifiedRoot);
                    simplifiedRoot = NULL;
                }
                if (root) {
                    freeTree(root);
                    root = NULL;
                }

                root = buildExpressionTree(expression);
                hasExpression = true;
                printf("Выражение сохранено.\n");
                break;

            case 2:
                if (!hasExpression) {
                    printf("Сначала введите выражение (пункт 1).\n");
                    break;
                }

                printf("\nТекстовое представление: ");
                printInfix(root);
                printf("\n");

                printf("\nДерево выражения:\n");
                printTree(root, 0);
                break;

            case 3:
                if (!hasExpression) {
                    printf("Сначала введите выражение (пункт 1).\n");
                    break;
                }

                if (simplifiedRoot != NULL) {
                    freeTree(simplifiedRoot);
                }
                simplifiedRoot = copyTree(root);

                simplifiedRoot = applyDistributive(simplifiedRoot);

                printf("\nУпрощенное выражение (текст): ");
                printInfix(simplifiedRoot);
                printf("\n");

                printf("\nУпрощенное дерево выражения:\n");
                printTree(simplifiedRoot, 0);
                break;

            case 4:
                printf("Выход из программы.\n");
                break;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);

    if (root != NULL) {
        freeTree(root);
        root = NULL;
    }
    if (simplifiedRoot != NULL) {
        freeTree(simplifiedRoot);
        simplifiedRoot = NULL;
    }
    
    return 0;
}