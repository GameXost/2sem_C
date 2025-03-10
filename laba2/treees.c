#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode {
    int value;
    int childcount;
    struct treenode* children[10];
} treenode;

treenode *createnode(int value) {
    treenode* result = malloc(sizeof(treenode));
    if (result == NULL) {
        return NULL;
    }
    result->value = value;
    result->childcount = 0;
    return result;
}

void addchild(treenode *parent, treenode *child) {
    if (parent->childcount < 10) {
        parent->children[parent->childcount++] = child;
    }
}

treenode *search(treenode *root, int value) {
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    for (int i = 0; i < root->childcount; i++) {
        treenode* found = search(root->children[i], value);
        if (found != NULL) return found;
    }
    return NULL;
}

treenode* findParent(treenode *root, treenode *target) {
    if (root == NULL) return NULL;
    for (int i = 0; i < root->childcount; i++) {
        if (root->children[i] == target) {
            return root;
        }
        treenode *parent = findParent(root->children[i], target);
        if (parent != NULL) {
            return parent;
        }
    }
    return NULL;
}

void freeSubtree(treenode *node) {
    if (node == NULL) return;
    for (int i = 0; i < node->childcount; i++) {
        freeSubtree(node->children[i]);
    }
    free(node);
}

void deletetree(treenode *root, int value) {
    treenode *found = search(root, value);
    if (found == NULL) return;

    treenode *parent = findParent(root, found);

    if (parent != NULL) {
        int index = -1;
        for (int i = 0; i < parent->childcount; i++) {
            if (parent->children[i] == found) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int j = index; j < parent->childcount - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->childcount--;
        }
    }

    freeSubtree(found);
}

void printtree(treenode* root, int level) {
    if (root == NULL) return;
    int middle = root->childcount / 2;
    for (int i = root->childcount - 1; i >= middle; i--) {
        if (i == root->childcount - 1) {
            printf("\n");
        }
        printtree(root->children[i], level + 1);
    }
    printf("%*s%d\n", level * 4, "", root->value);

    for (int i = middle - 1; i >= 0; i--) {
        printtree(root->children[i], level + 1);
        if (i == 0) {
            printf("\n");
        }
    }
}
int degree(treenode *root) {
    int max_degree = root->childcount;
    if (root == NULL) return 0;
    for (int i = 0; i < root->childcount; i++){
        int child_degree = degree(root->children[i]);
        if (child_degree > max_degree) max_degree = child_degree;
    }
    return max_degree;
}


int main() {
    treenode *root = createnode(1);
    treenode *child1 = createnode(2);
    treenode *child2 = createnode(3);
    treenode *child4 = createnode(5);
    treenode *child5 = createnode(6);
    treenode *child6 = createnode(7);
    treenode *child7 = createnode(8);
    treenode *child8 = createnode(9);

    addchild(root, child1);
    addchild(root, child2);
    addchild(child1, child4);
    addchild(child1, child5);
    addchild(child1, child6);
    addchild(child2, child7);
    addchild(child2, child8);
 

    int choice, parent_val, child_val, del_val;

    while(1) {
        printf("\n--- Tree Operations Menu ---\n");
        printf("1. Add child to parent node\n");
        printf("2. Print tree\n");
        printf("3. Delete branch\n");
        printf("4. tree degree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter parent value: ");
                scanf("%d", &parent_val);
                printf("Enter child value: ");
                scanf("%d", &child_val);
                
                treenode* parent = search(root, parent_val);
                if(parent) {
                    if(parent->childcount < 10) {
                        treenode* new_child = createnode(child_val);
                        addchild(parent, new_child);
                        printf("Child %d added to parent %d\n", child_val, parent_val);
                    } else {
                        printf("Parent already has maximum children!\n");
                    }
                } else {
                    printf("Parent not found!\n");
                }
                break;

            case 2:
                printf("\nCurrent Tree Structure:");
                printtree(root, 0);
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &del_val);
                if(del_val == root->value) {
                    printf("Cannot delete root node!\n");
                    break;
                }
                if(search(root, del_val)) {
                    deletetree(root, del_val);
                    printf("Branch %d deleted successfully\n", del_val);
                } else {
                    printf("Node not found!\n");
                }
                break;
            case 4:
                printf("Maximum degree of the tree: %d\n", degree(root));
                break;
            case 5:
                freeSubtree(root);
                printf("Tree deleted. Exiting...\n");
                exit(0);


            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}