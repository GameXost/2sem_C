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

int main() {
    treenode *root = createnode(1);
    treenode *child1 = createnode(2);
    treenode *child2 = createnode(3);
    treenode *child3 = createnode(4);
    treenode *child4 = createnode(5);
    treenode *child5 = createnode(6);
    treenode *child6 = createnode(7);
    treenode *child7 = createnode(8);
    treenode *child8 = createnode(9);
    treenode *child9 = createnode(10);
    treenode *child10 = createnode(11);
    treenode *child11 = createnode(12);
    treenode *child12 = createnode(13);
    treenode *child13 = createnode(14);
    treenode *child14 = createnode(15);

    addchild(root, child1);
    addchild(root, child2);
    addchild(root, child3);
    addchild(child1, child4);
    addchild(child1, child5);
    addchild(child1, child6);
    addchild(child2, child7);
    addchild(child2, child8);
    addchild(child2, child9);
    addchild(child3, child10);
    addchild(child3, child11);
    addchild(child4, child12);
    addchild(child4, child13);
    addchild(child13, child14);

    printf("Original tree:\n");
    printtree(root, 0);

    deletetree(root, 4);

    printf("\nTree after deleting node 4:\n");
    printtree(root, 0);

    return 0;
}