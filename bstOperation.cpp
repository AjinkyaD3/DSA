#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) {
        value = val;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->value) {
        root->left = insert(root->left, val);
    }
    if (val > root->value) {
        root->right = insert(root->right, val);
    }
    return root;
}

bool search(Node* root, int val) {
    if (root == nullptr) return false;
    if (root->value == val) return true;
    if (val < root->value) {
        return search(root->left, val);
    }
    return search(root->right, val);
}

Node* deleteNode(Node* root, int val) {
    if (root == nullptr) {
        return root;
    }
    if (val < root->value) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->value) {
        root->right = deleteNode(root->right, val);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);  
        root->value = temp->value;  
        root->right = deleteNode(root->right, temp->value);  
    }
    return root;  
}

Node* findMin(Node* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->value << " ";
    }
}

void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int choice, val;

    do {
        cout << "\nMenu: \n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display In-Order\n";
        cout << "5. Display Pre-Order\n";
        cout << "6. Display Post-Order\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                root = deleteNode(root, val);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> val;
                if (search(root, val)) {
                    cout << "Value " << val << " found in the tree.\n";
                } else {
                    cout << "Value " << val << " not found in the tree.\n";
                }
                break;
            case 4:
                cout << "In-Order: ";
                inOrder(root);
                cout << endl;
                break;
            case 5:
                cout << "Pre-Order: ";
                preOrder(root);
                cout << endl;
                break;
            case 6:
                cout << "Post-Order: ";
                postOrder(root);
                cout << endl;
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
