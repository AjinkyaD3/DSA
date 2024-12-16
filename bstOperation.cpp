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
    } else if (value > root->data) {
        root->right = insert(root->right, value);  // Insert in the right subtree
    }
    // If value == root->data, it's a duplicate, so we do nothing
    
    return root;  // Return the root node
}

// Search for a value in the tree
bool search(Node* root, int value) {
    if (root == nullptr) return false;  // Not found if root is null
    if (root->data == value) return true;  // Value found
    
    if (value < root->data) return search(root->left, value);  // Search in left
    return search(root->right, value);  // Search in right
}

// Find the node with the minimum value (for deletion)
Node* findMin(Node* root) {
    while (root && root->left) {
        root = root->left;  // Traverse to the leftmost node
    }
    return root;
}

// Delete a value from the tree
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;  // Tree is empty or value not found

    if (value < root->data) {
        root->left = deleteNode(root->left, value);  // Recur on left subtree
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);  // Recur on right subtree
    } else {
        // Node to be deleted is found
        
        // Case 1: Node has no children (leaf node)
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        
        // Case 2: Node has one child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        // Case 3: Node has two children
        Node* temp = findMin(root->right);  // Get the inorder successor (smallest in right subtree)
        root->data = temp->data;  // Copy the inorder successor's value to this node
        root->right = deleteNode(root->right, temp->data);  // Delete the inorder successor
    }

    return root;
}

// In-order traversal (left, root, right)
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);  // Visit left subtree
        cout << root->data << " ";  // Print node value
        inorder(root->right);  // Visit right subtree
    }
}

// Pre-order traversal (root, left, right)
void preorder(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";  // Print node value
        preorder(root->left);  // Visit left subtree
        preorder(root->right);  // Visit right subtree
    }
}

// Post-order traversal (left, right, root)
void postorder(Node* root) {
    if (root != nullptr) {
        postorder(root->left);  // Visit left subtree
        postorder(root->right);  // Visit right subtree
        cout << root->data << " ";  // Print node value
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
    root = insert(root, 50);  // Duplicate value (won't be inserted)

    // Display the tree in sorted order (in-order traversal)
    cout << "In-order traversal: ";
    inorder(root);
    cout << endl;

    // Search for a value
    int valueToSearch = 40;
    cout << "Searching for " << valueToSearch << ": ";
    cout << (search(root, valueToSearch) ? "Found" : "Not Found") << endl;

    // Delete a value
    int valueToDelete = 40;
    cout << "Deleting " << valueToDelete << endl;
    root = deleteNode(root, valueToDelete);

    // Display the tree again after deletion
    cout << "In-order traversal after deletion: ";
    inorder(root);
    cout << endl;

    // Display the tree in pre-order
    cout << "Pre-order traversal: ";
    preorder(root);
    cout << endl;

    // Display the tree in post-order
    cout << "Post-order traversal: ";
    postorder(root);
    cout << endl;

    return 0;
}
