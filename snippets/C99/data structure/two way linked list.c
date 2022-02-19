struct num {
    int data;
    struct num* left;
    struct num* right;
};

struct num* construct_node(int val) {
    struct num* constructed = (struct num*)malloc(sizeof(struct num));
    constructed->data = val;
    constructed->left = NULL;
    constructed->right = NULL;
    return constructed;
}

struct num* insert_node(struct num* reference, int val, char direction) {
    // direction) 0: left / 1: right

    struct num* inserted = (struct num*)malloc(sizeof(struct num));
    struct num* temp;
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

int scan_nodes(struct num* start) {
    printf("All nodes: ");
    while (start->left != NULL) start = start->left;
    while (start != NULL) {
        printf("%d ", start->data);
        start = start->right;
    }
    printf("\n");
    return 0;
}