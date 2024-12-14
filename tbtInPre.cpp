#include <iostream>
using namespace std;

// Define a simple node structure for Threaded Binary Tree
struct Node {
    int data;
    Node* left;
    Node* right;
    bool leftThread;  // True if left pointer is a thread
    bool rightThread; // True if right pointer is a thread

    // Constructor to create a node
    Node(int val) {
        data = val;
        left = right = nullptr;
        leftThread = rightThread = false;
    }
};

// Function to insert a new node in the tree (in-order threading)
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);  // If tree is empty, create a new node
    }

    Node* curr = root;
    Node* prev = nullptr;

    // Find the position to insert the new node
    while (curr != nullptr) {
        prev = curr;
        if (value < curr->data) {
            if (!curr->leftThread) {
                curr = curr->left;  // Move left
            } else {
                break;
            }
        } else {
            if (!curr->rightThread) {
                curr = curr->right;  // Move right
            } else {
                break;
            }
        }
    }

    Node* newNode = new Node(value);

    // Insert in the left or right of the parent
    if (value < prev->data) {
        newNode->left = prev->left;
        newNode->right = prev;
        prev->left = newNode;
        prev->leftThread = true;  // Thread the left pointer
    } else {
        newNode->right = prev->right;
        newNode->left = prev;
        prev->right = newNode;
        prev->rightThread = true;  // Thread the right pointer
    }

    return root;
}

// In-order traversal (using threads)
void inorder(Node* root) {
    if (root == nullptr) return;

    Node* temp = root;
    // Move to the leftmost node
    while (temp != nullptr && !temp->leftThread) {
        temp = temp->left;
    }

    // Traverse the tree using threads
    while (temp != nullptr) {
        cout << temp->data << " ";  // Visit the node
        if (temp->rightThread) {
            temp = temp->right;  // Move to the in-order successor using thread
        } else {
            temp = temp->right;
            // Move to the leftmost node in the right subtree
            while (temp != nullptr && !temp->leftThread) {
                temp = temp->left;
            }
        }
    }
}

// Pre-order traversal (using threads)
void preorder(Node* root) {
    if (root == nullptr) return;

    Node* temp = root;
    cout << temp->data << " ";  // Visit root

    while (temp != nullptr) {
        if (!temp->leftThread) {
            temp = temp->left;  // Visit left child if no thread
        } else if (!temp->rightThread) {
            temp = temp->right;  // Visit right child if no thread
        } else {
            break;  // End of traversal
        }
        cout << temp->data << " ";  // Visit node
    }
}

int main() {
    Node* root = nullptr;

    // Insert nodes into the threaded binary tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // In-order traversal
    cout << "In-order traversal: ";
    inorder(root);
    cout << endl;

    // Pre-order traversal
    cout << "Pre-order traversal: ";
    preorder(root);
    cout << endl;

    return 0;
}
