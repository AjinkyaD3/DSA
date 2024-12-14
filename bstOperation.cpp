#include <iostream>
using namespace std;

// Define a simple structure for a node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {  // Constructor to create a new node
        data = value;
        left = right = nullptr;
    }
};

// Insert a new value into the BST
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);  // If tree is empty, create a new node
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);  // Insert in the left subtree
    } else {
        root->right = insert(root->right, value);  // Insert in the right subtree
    }

    return root;  // Return the root node
}

// Search for a value in the tree
bool search(Node* root, int value) {
    if (root == nullptr) return false;  // Not found if root is null
    if (root->data == value) return true;  // Value found
    
    if (value < root->data) return search(root->left, value);  // Search in left
    return search(root->right, value);  // Search in right
}

// In-order traversal (left, root, right)
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);  // Visit left subtree
        cout << root->data << " ";  // Print node value
        inorder(root->right);  // Visit right subtree
    }
}

int main() {
    Node* root = nullptr;  // Start with an empty tree

    // Insert values into the tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    // Display the tree in sorted order (in-order traversal)
    cout << "In-order traversal: ";
    inorder(root);
    cout << endl;

    // Search for a value
    int valueToSearch = 40;
    cout << "Searching for " << valueToSearch << ": ";
    cout << (search(root, valueToSearch) ? "Found" : "Not Found") << endl;

    return 0;
}
