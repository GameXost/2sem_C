#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode {
    int value;
    struct treenode *child;
    struct treenode *brother;
} treenode;

treenode *createnode(int value) {
    treenode* result = malloc(sizeof(treenode));
    if (result == NULL) {
        return NULL;
    }
    result->value = value;
    result->child = NULL;
    result->brother = NULL;
    return result;
}

void addchild(treenode *parent, treenode *new_child) {
    if (parent->child == NULL) {
        parent->child = new_child;
    } else {
        treenode *sibling = parent->child;
        while (sibling->brother) {
            sibling = sibling->brother;
        }
        sibling->brother = new_child;
    }
}

treenode *search(treenode *root, int value) {
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    treenode *found = search(root->child, value);
    if (found) return found;

    return search(root->brother, value);
}

treenode *findParent(treenode *root, treenode *target) {
    if (root == NULL || target == NULL) return NULL;
    
    if (root->child == target) return root;
    
    treenode *sibling = root->child;
    while (sibling) {
        if (sibling->brother == target) return root;
        sibling = sibling->brother;
    }
    
    treenode *parent = findParent(root->child, target);
    if (parent) return parent;
    
    return findParent(root->brother, target);
}

void freeSubtree(treenode *node) {
    if (node == NULL) return;
    freeSubtree(node->child);
    freeSubtree(node->brother);
    free(node);
}

void deletetree(treenode **root, int value) {
    if (*root == NULL) return;
    
    if ((*root)->value == value) {
        freeSubtree(*root);
        *root = NULL;
        return;
    }
    
    treenode *found = search(*root, value);
    if (found == NULL) return;

    treenode *parent = findParent(*root, found);
    if (parent != NULL) {
        if (parent->child == found) {
            parent->child = found->brother;
        } else {
            treenode *sibling = parent->child;
            while (sibling && sibling->brother != found) {
                sibling = sibling->brother;
            }
            if (sibling) {
                sibling->brother = found->brother;
            }
        }
    }

    freeSubtree(found);
}

void printtree(treenode *root, int level) {
    if (root == NULL) return;
    
    printf("%*s%d\n", level * 4, "", root->value);
    printtree(root->child, level + 1);
    printtree(root->brother, level);
}

int degree(treenode *root) {
    if (root == NULL) return 0;
    int max_degree = 0;
    treenode *child = root->child;
    while (child) {
        max_degree++;
        int child_degree = degree(child);
        if (child_degree > max_degree) max_degree = child_degree;
        child = child->brother;
    }
    return max_degree;
}


int main() {
    treenode *root = NULL;
    int choice, parent_val, child_val;

    while (1) {
        printf("\n--- Tree Operations Menu ---\n");
        printf("1. Add child to parent node\n");
        printf("2. Print tree\n");
        printf("3. Delete branch\n");
        printf("4. Tree degree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter parent value: ");
                scanf("%d", &parent_val);
                printf("Enter child value: ");
                scanf("%d", &child_val);
            
                if (root == NULL) {
                    root = createnode(parent_val);
                    printf("Tree was empty. Created root node with value %d.\n", parent_val);
                    break;
                }
            
                treenode *parent_node = search(root, parent_val);
                if (parent_node) {
                    treenode *new_child = createnode(child_val);
                    addchild(parent_node, new_child);
                    printf("Child %d added to parent %d\n", child_val, parent_val);
                } else {
                    printf("Parent node not found!\n");
                }
                break;
            
            case 2:
                printf("\nCurrent Tree Structure:\n");
                printtree(root, 0);
                break;
            case 3:
                printf("Enter value to delete: ");
                int del_val;
                scanf("%d", &del_val);
                if (root && del_val == root->value) {
                    printf("Cannot delete root node!\n");
                    break;
                }
                if (search(root, del_val)) {
                    deletetree(&root, del_val);
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