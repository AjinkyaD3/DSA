#include <iostream>
#include <stack>
#include <cctype>
#include <string>
using namespace std;

// Node structure for Expression Tree
struct Node {
    char data;  // Store operator or operand
    Node* left;
    Node* right;
    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

// Check if the character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Build Expression Tree from Postfix
Node* buildTreeFromPostfix(const string& postfix) {
    stack<Node*> stk;
    
    for (char ch : postfix) {
        if (isalnum(ch)) {
            stk.push(new Node(ch));  // Operand node
        } else if (isOperator(ch)) {
            Node* right = stk.top(); stk.pop();
            Node* left = stk.top(); stk.pop();
            Node* operatorNode = new Node(ch);  // Operator node
            operatorNode->left = left;
            operatorNode->right = right;
            stk.push(operatorNode);  // Push new operator node to stack
        }
    }
    return stk.top();  // Root of the tree
}

// Build Expression Tree from Prefix
Node* buildTreeFromPrefix(const string& prefix) {
    stack<Node*> stk;
    
    // Traverse prefix from right to left
    for (int i = prefix.length() - 1; i >= 0; --i) {
        char ch = prefix[i];
        
        if (isalnum(ch)) {
            stk.push(new Node(ch));  // Operand node
        } else if (isOperator(ch)) {
            Node* left = stk.top(); stk.pop();
            Node* right = stk.top(); stk.pop();
            Node* operatorNode = new Node(ch);  // Operator node
            operatorNode->left = left;
            operatorNode->right = right;
            stk.push(operatorNode);  // Push new operator node to stack
        }
    }
    return stk.top();  // Root of the tree
}

// Recursive Traversals
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Non-recursive Traversals
void inorderNonRecursive(Node* root) {
    stack<Node*> stk;
    Node* current = root;
    
    while (current != nullptr || !stk.empty()) {
        while (current != nullptr) {
            stk.push(current);
            current = current->left;
        }
        current = stk.top(); stk.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preorderNonRecursive(Node* root) {
    if (root == nullptr) return;
    
    stack<Node*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        Node* current = stk.top();
        stk.pop();
        cout << current->data << " ";
        
        if (current->right) stk.push(current->right);
        if (current->left) stk.push(current->left);
    }
}

void postorderNonRecursive(Node* root) {
    if (root == nullptr) return;
    
    stack<Node*> stk1, stk2;
    stk1.push(root);
    
    while (!stk1.empty()) {
        Node* current = stk1.top();
        stk1.pop();
        stk2.push(current);
        
        if (current->left) stk1.push(current->left);
        if (current->right) stk1.push(current->right);
    }
    
    while (!stk2.empty()) {
        cout << stk2.top()->data << " ";
        stk2.pop();
    }
}

int main() {
    string postfix = "ab+c*";   // Example postfix expression
    string prefix = "*+abc";    // Example prefix expression
    
    // Build Expression Trees from postfix and prefix
    Node* postfixTree = buildTreeFromPostfix(postfix);
    Node* prefixTree = buildTreeFromPrefix(prefix);
    
    cout << "Postfix Expression Tree Traversals:" << endl;
    cout << "In-order (Recursive): ";
    inorder(postfixTree);
    cout << endl;
    
    cout << "Pre-order (Recursive): ";
    preorder(postfixTree);
    cout << endl;
    
    cout << "Post-order (Recursive): ";
    postorder(postfixTree);
    cout << endl;
    
    cout << "In-order (Non-recursive): ";
    inorderNonRecursive(postfixTree);
    cout << endl;
    
    cout << "Pre-order (Non-recursive): ";
    preorderNonRecursive(postfixTree);
    cout << endl;
    
    cout << "Post-order (Non-recursive): ";
    postorderNonRecursive(postfixTree);
    cout << endl;

    cout << "\nPrefix Expression Tree Traversals:" << endl;
    cout << "In-order (Recursive): ";
    inorder(prefixTree);
    cout << endl;
    
    cout << "Pre-order (Recursive): ";
    preorder(prefixTree);
    cout << endl;
    
    cout << "Post-order (Recursive): ";
    postorder(prefixTree);
    cout << endl;
    
    cout << "In-order (Non-recursive): ";
    inorderNonRecursive(prefixTree);
    cout << endl;
    
    cout << "Pre-order (Non-recursive): ";
    preorderNonRecursive(prefixTree);
    cout << endl;
    
    cout << "Post-order (Non-recursive): ";
    postorderNonRecursive(prefixTree);
    cout << endl;
    
    return 0;
}
