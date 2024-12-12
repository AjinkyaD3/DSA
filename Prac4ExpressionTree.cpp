#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Node structure for Expression Tree
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

class ExpressionTree {
public:
    Node* constructFromPostfix(const string& postfix) {
        stack<Node*> s;

        for (char ch : postfix) {
            if (isalnum(ch)) { // Operand
                s.push(new Node(ch));
            } else { // Operator
                Node* opNode = new Node(ch);
                opNode->right = s.top(); s.pop();
                opNode->left = s.top(); s.pop();
                s.push(opNode);
            }
        }
        return s.top();
    }

    Node* constructFromPrefix(const string& prefix) {
        stack<Node*> s;

        for (int i = prefix.size() - 1; i >= 0; i--) {
            char ch = prefix[i];
            if (isalnum(ch)) { // Operand
                s.push(new Node(ch));
            } else { // Operator
                Node* opNode = new Node(ch);
                opNode->left = s.top(); s.pop();
                opNode->right = s.top(); s.pop();
                s.push(opNode);
            }
        }
        return s.top();
    }

    // Recursive Traversals
    void inOrderRecursive(Node* root) {
        if (root) {
            inOrderRecursive(root->left);
            cout << root->data << " ";
            inOrderRecursive(root->right);
        }
    }

    void preOrderRecursive(Node* root) {
        if (root) {
            cout << root->data << " ";
            preOrderRecursive(root->left);
            preOrderRecursive(root->right);
        }
    }

    void postOrderRecursive(Node* root) {
        if (root) {
            postOrderRecursive(root->left);
            postOrderRecursive(root->right);
            cout << root->data << " ";
        }
    }

    // Non-Recursive Traversals
    void inOrderNonRecursive(Node* root) {
        stack<Node*> s;
        Node* current = root;

        while (current || !s.empty()) {
            while (current) {
                s.push(current);
                current = current->left;
            }
            current = s.top(); s.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }

    void preOrderNonRecursive(Node* root) {
        if (!root) return;

        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node* current = s.top(); s.pop();
            cout << current->data << " ";

            if (current->right) s.push(current->right);
            if (current->left) s.push(current->left);
        }
    }

    void postOrderNonRecursive(Node* root) {
        if (!root) return;

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* current = s1.top(); s1.pop();
            s2.push(current);

            if (current->left) s1.push(current->left);
            if (current->right) s1.push(current->right);
        }

        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
    }
};

int main() {
    ExpressionTree tree;
    string postfix, prefix;

    cout << "Enter a postfix expression: ";
    cin >> postfix;
    Node* postfixTree = tree.constructFromPostfix(postfix);

    cout << "Recursive In-order Traversal: ";
    tree.inOrderRecursive(postfixTree);
    cout << endl;

    cout << "Non-Recursive In-order Traversal: ";
    tree.inOrderNonRecursive(postfixTree);
    cout << endl;

    cout << "Recursive Pre-order Traversal: ";
    tree.preOrderRecursive(postfixTree);
    cout << endl;

    cout << "Non-Recursive Pre-order Traversal: ";
    tree.preOrderNonRecursive(postfixTree);
    cout << endl;

    cout << "Recursive Post-order Traversal: ";
    tree.postOrderRecursive(postfixTree);
    cout << endl;

    cout << "Non-Recursive Post-order Traversal: ";
    tree.postOrderNonRecursive(postfixTree);
    cout << endl;

    cout << "\nEnter a prefix expression: ";
    cin >> prefix;
    Node* prefixTree = tree.constructFromPrefix(prefix);

    cout << "Recursive In-order Traversal: ";
    tree.inOrderRecursive(prefixTree);
    cout << endl;

    cout << "Non-Recursive In-order Traversal: ";
    tree.inOrderNonRecursive(prefixTree);
    cout << endl;

    cout << "Recursive Pre-order Traversal: ";
    tree.preOrderRecursive(prefixTree);
    cout << endl;

    cout << "Non-Recursive Pre-order Traversal: ";
    tree.preOrderNonRecursive(prefixTree);
    cout << endl;

    cout << "Recursive Post-order Traversal: ";
    tree.postOrderRecursive(prefixTree);
    cout << endl;

    cout << "Non-Recursive Post-order Traversal: ";
    tree.postOrderNonRecursive(prefixTree);
    cout << endl;

    return 0;
}
