#include <stdio.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    struct list* parent;
} node;

typedef struct list {
    int num_nodes;
    node* head;
    node* tail;
} list;

list* construct_list() {
    list* constructed = (list*)malloc(sizeof(list));
    constructed->num_nodes = 0;
    constructed->head = NULL;
    constructed->tail = NULL;
    return constructed;
}

node* construct_node(int val, list* p) {
    node* constructed = (node*)malloc(sizeof(node));
    constructed->data = val;
    constructed->left = NULL;
    constructed->right = NULL;
    constructed->parent = p;
    return constructed;
}

node* append_node(list* target, int val) {
    node* new_node = construct_node(val, target);
    if (target->num_nodes == 0) {
        target->head = new_node;
        target->tail = new_node;
    } else {
        target->tail->right = new_node;
        new_node->left = target->tail;
        target->tail = new_node;
    }
    target->num_nodes++;
    return new_node;
}

node* insert_node(node* reference, int val, char direction) {
    // direction) 0: left / 1: right

    node* inserted = construct_node(val, reference->parent);
    node* temp;
    inserted->parent->num_nodes++;

    if (direction) {
        // right
        temp = reference->right;
        reference->right = inserted;
        inserted->left = reference;
        inserted->right = temp;
        if (temp != NULL)
            temp->left = inserted;
        else
            inserted->parent->tail = inserted;
    } else {
        // left
        temp = reference->left;
        reference->left = inserted;
        inserted->right = reference;
        inserted->left = temp;
        if (temp != NULL)
            temp->right = inserted;
        else
            inserted->parent->head = inserted;
    }

    return inserted;
}

int scan_nodes(struct node* start) {
    printf("All nodes: ");
    while (start->left != NULL) start = start->left;
    while (start != NULL) {
        printf("%d ", start->data);
        start = start->right;
    }
    printf("\n");
    return 0;
}