#include <stdio.h>
#include <stdlib.h>
#define N_MAX 10001
typedef struct TreeNode {
    int data;
    struct TreeNode* p;
    struct TreeNode* l;
    struct TreeNode* r;
} TreeNode;
int n, numbers[N_MAX], cursor;
TreeNode* root;

TreeNode* TreeNode__init__(TreeNode* parent, int data);
int preorder_traverse(TreeNode* s);
int postorder_traverse(TreeNode* s);

int main() {
    int a;
    while (scanf("%d", &a) != EOF) numbers[n++] = a;
    root = TreeNode__init__(NULL, 0);
    preorder_traverse(root);
    postorder_traverse(root);
    return 0;
}

TreeNode* TreeNode__init__(TreeNode* parent, int data) {
    TreeNode* new = malloc(sizeof(TreeNode));
    new->data = data;
    new->p = parent;
    new->l = NULL;
    new->r = NULL;
    return new;
}

int can_put(TreeNode* s, int number) {
    int can_put = 1;
    while (1) {
        TreeNode* parent = s->p;
        if (parent == NULL) break;
        if (parent->l == s) {  // left
            if (number >= parent->data) {
                can_put = 0;
                break;
            }
        } else {  // right
            if (number <= parent->data) {
                can_put = 0;
                break;
            }
        }
        s = parent;
    }
    return can_put;
}

int preorder_traverse(TreeNode* s) {
    if (cursor == n) return 0;
    if (can_put(s, numbers[cursor])) {
        s->data = numbers[cursor];
        s->l = TreeNode__init__(s, 0);
        s->r = TreeNode__init__(s, 0);
        cursor++;
        preorder_traverse(s->l);
        preorder_traverse(s->r);
    }
    return 0;
}

int postorder_traverse(TreeNode* s) {
    if (s->data == 0) return 0;
    postorder_traverse(s->l);
    postorder_traverse(s->r);
    printf("%d\n", s->data);
    return 0;
}