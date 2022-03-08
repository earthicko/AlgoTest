#include <stdio.h>
#define TREE_SIZE 27
int preorder_travel(int s);
int inorder_travel(int s);
int postorder_travel(int s);
int tree[TREE_SIZE][2];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char parent, child0, child1;
        scanf(" %c %c %c", &parent, &child0, &child1);
        tree[parent - 'A'][0] = child0 - 'A';
        tree[parent - 'A'][1] = child1 - 'A';
    }
    preorder_travel(0);
    printf("\n");
    inorder_travel(0);
    printf("\n");
    postorder_travel(0);
    printf("\n");
    return 0;
}
int preorder_travel(int s) {
    if (s + 'A' == '.') return 0;
    printf("%c", s + 'A');
    preorder_travel(tree[s][0]);
    preorder_travel(tree[s][1]);
    return 0;
}
int inorder_travel(int s) {
    if (s + 'A' == '.') return 0;
    inorder_travel(tree[s][0]);
    printf("%c", s + 'A');
    inorder_travel(tree[s][1]);
    return 0;
}
int postorder_travel(int s) {
    if (s + 'A' == '.') return 0;
    postorder_travel(tree[s][0]);
    postorder_travel(tree[s][1]);
    printf("%c", s + 'A');
    return 0;
}