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

void printtree(treenode* root, int level){
    if (root == NULL) return;
    int middle = root->childcount/2;
    for (int i = root->childcount - 1; i >= middle; i--) {
        printtree(root->children[i], level + 1);
    }
    printf("%*s%d\n\n", level * 4, "", root->value);
    

    for (int i = middle-1; i >= 0; i--){
        printtree(root->children[i], level + 1);
    }
}

void freetree(treenode* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->childcount; i++) {
        freetree(root->children[i]);
    }
    free(root);
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

    addchild(root, child1);
    addchild(root, child2);
    addchild(root, child3);
    addchild(root, child4);

    addchild(child1, child5);
    addchild(child1, child6);
    addchild(child2, child7);
    addchild(child2, child8);


    // Выводим дерево повернутым на 90 градусов
    printtree(root, 0);
    freetree(root);


    return 0;
}
