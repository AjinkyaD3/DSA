#include <iostream>
using namespace std;

// Node structure representing each node in the tree
struct Node {
    int data;
    Node *left, *right;
    bool leftThread, rightThread;  // These indicate if the left or right pointer is a thread

    // Constructor to initialize a node with data and no threads
    Node(int val) {
        data = val;
        left = right = nullptr;
        leftThread = rightThread = false;
    }
};

// Function to insert a new node in the tree
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);  // If the tree is empty, create a new node
    }

    Node* curr = root;
    Node* prev = nullptr;

    // Traverse the tree to find the correct position for the new node
    while (curr != nullptr) {
        prev = curr;
        if (value < curr->data) {
            if (!curr->leftThread) {
                curr = curr->left;  // Move left if no thread
            } else {
                break;
            }
        } else {
            if (!curr->rightThread) {
                curr = curr->right;  // Move right if no thread
            } else {
                break;
            }
        }
    }

    // Create the new node
    Node* newNode = new Node(value);

    // Insert the new node as the left or right child, and set threads
    if (value < prev->data) {
        newNode->left = prev->left;
        newNode->right = prev;
        prev->left = newNode;
        prev->leftThread = true;  // Set thread for the left pointer
    } else {
        newNode->right = prev->right;
        newNode->left = prev;
        prev->right = newNode;
        prev->rightThread = true;  // Set thread for the right pointer
    }

    return root;
}

// In-order traversal of the tree (left, root, right) using threads
void inorder(Node* root) {
    if (root == nullptr) return;

    // Move to the leftmost node
    Node* temp = root;
    while (temp != nullptr && !temp->leftThread) {
        temp = temp->left;
    }

    // Traverse the tree using threads
    while (temp != nullptr) {
        cout << temp->data << " ";  // Print the node's data
        if (temp->rightThread) {
            temp = temp->right;  // Follow the thread to the next node
        } else {
            temp = temp->right;
            while (temp != nullptr && !temp->leftThread) {
                temp = temp->left;  // Move to the leftmost node in the right subtree
            }
        }
    }
}

// Pre-order traversal of the tree (root, left, right) using threads
void preorder(Node* root) {
    if (root == nullptr) return;

    Node* temp = root;
    cout << temp->data << " ";  // Visit the root node

    while (temp != nullptr) {
        if (!temp->leftThread) {
            temp = temp->left;  // Move left if no thread
        } else if (!temp->rightThread) {
            temp = temp->right;  // Move right if no thread
        } else {
            break;  // End of traversal
        }
        cout << temp->data << " ";  // Visit the node
    }
}

int main() {
    Node* root = nullptr;

    // Insert nodes into the tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // Perform in-order traversal
    cout << "In-order traversal: ";
    inorder(root);
    cout << endl;

    // Perform pre-order traversal
    cout << "Pre-order traversal: ";
    preorder(root);
    cout << endl;

    return 0;
}
