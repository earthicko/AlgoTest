struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* construct_node(int val) {
    struct node* constructed = (struct node*)malloc(sizeof(struct node));
    constructed->data = val;
    constructed->left = NULL;
    constructed->right = NULL;
    return constructed;
}

struct node* insert_node(struct node* reference, int val, char direction) {
    // direction) 0: left / 1: right

    struct node* inserted = (struct node*)malloc(sizeof(struct node));
    struct node* temp;
    inserted->data = val;

    if (direction) {
        // right
        temp = reference->right;
        reference->right = inserted;
        inserted->left = reference;
        inserted->right = temp;
        if (temp != NULL) temp->left = inserted;
    } else {
        // left
        temp = reference->left;
        reference->left = inserted;
        inserted->right = reference;
        inserted->left = temp;
        if (temp != NULL) temp->right = inserted;
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