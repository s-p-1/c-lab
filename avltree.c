#include "helper.h"


// Function to get the height of the tree
int height(AVLNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to create a new AVL tree node
AVLNode* newNode(int value) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    node->count = 1; // initialize count to 1
    return node;
}

// Right rotate subtree rooted with y
AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor of node N
int getBalance(AVLNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a value in the subtree rooted
// with node and returns the new root of the subtree.
AVLNode* insert(AVLNode* root, int value) {
    // 1. Perform the normal BST insertion
    if (root == NULL)
        return newNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    else { // Equal values are found
        root->count++;
        return root;
    }

    // 2. Update height of this ancestor node
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && value < root->left->value)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && value > root->right->value)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && value > root->left->value) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && value < root->right->value) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // return the (unchanged) node pointer
    return root;
}

// Recursive function to delete a node with given value
// from subtree with given root. It returns root of the
// modified subtree.
AVLNode* deleteNode(AVLNode* root, int value) {
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the value to be deleted is smaller than the root's
    // value, then it lies in left subtree
    if (value < root->value)
        root->left = deleteNode(root->left, value);

    // If the value to be deleted is greater than the root's
    // value, then it lies in right subtree
    else if (value > root->value)
        root->right = deleteNode(root->right, value);

    // if value is same as root's value
    else {
        // If the count is greater than 1, simply decrement the count and return
        if (root->count > 1) {
            root->count--;
            return root;
        }
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *temp = root->left ? root->left : root->right;
            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        }
        else {
            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            AVLNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->value = temp->value;
            root->count = temp->count;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->value);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    // this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// function to print inorder traversal of the tree when given the int converted values of the cells
void inorderTraversal(AVLNode *root , int size) {
    int* list = (int*)malloc(size*sizeof(int));
    int i = 0;
    if (root != NULL) {
        inorderTraversal(root->left, size);
        list[i] = root->value;
        i++;
        inorderTraversal(root->right, size);
    }
    return list;
}

// Function to build an AVL tree from a list of values
AVLNode* buildAVLTree(int values[], int size) {
    AVLNode *root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, values[i]);
    }
    return root;
}

// Utility function to find the node with minimum value
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    // loop down to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;
    return current;
}
AVLNode* maxValueNode(AVLNode* node) {
    AVLNode* current = node;
    // loop down to find the rightmost leaf
    while (current->right != NULL)
        current = current->right;
    return current;
}

// Driver program to test above functions

// int main() {
//     // List of values to insert into the AVL tree
//     int values[] = {10, 20, 30, 40, 50, 25};
//     int size = sizeof(values) / sizeof(values[0]);

//     // Build the AVL tree from the list of values
//     AVLNode *root = buildAVLTree(values, size);

//     // Print inorder traversal of the AVL tree
//     printf("Inorder traversal of the constructed AVL tree is:\n");
//     inorderTraversal(root);
//     printf("\n");

//     // Insert duplicate values to test count increment
//     root = insert(root, 20);
//     root = insert(root, 30);

//     // Print inorder traversal after inserting duplicates
//     printf("Inorder traversal after inserting duplicates:\n");
//     inorderTraversal(root);
//     printf("\n");

//     // Delete a value and print the tree
//     root = deleteNode(root, 20);
//     printf("Inorder traversal after deleting 20:\n");
//     inorderTraversal(root);
//     printf("\n");

//     // Delete a value with count > 1 and print the tree
//     root = deleteNode(root, 30);
//     printf("Inorder traversal after deleting 30 (count > 1):\n");
//     inorderTraversal(root);
//     printf("\n");

//     root = deleteNode(root, 30);
//     printf("Inorder traversal after deleting 30 (count > 1):\n");
//     inorderTraversal(root);
//     printf("\n");
//     return 0;
// }