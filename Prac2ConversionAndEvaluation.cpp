#include <iostream>
#include <cctype>
using namespace std;

// Node structure for stack using singly linked list
struct Node {
    char data;
    Node* next;
    Node(char value) : data(value), next(nullptr) {}
};


class Stack {
private:
    Node* top;

public:
    Stack(){ 
        top=nullptr;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(char value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        char value = top->data;
        top = top->next;
        return value;
    }

    char peek() {
        return isEmpty() ? '\0' : top->data;
    }
};

// Helper function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/'|| ch == '^');
}

// Helper function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^' ) return 3;
    return 0;
}

// Function to convert infix to postfix
string infixToPostfix(const string& infix) {
    Stack s;
    string postfix = "";

    for (char ch : infix) {
        if (isalnum(ch)) {  // Operand
            postfix += ch;
        }
        else if (ch == '(') {  // Left Parenthesis
            s.push(ch);
        }
        else if (ch == ')') {  // Right Parenthesis
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();  // Pop '('
        }
        else if (isOperator(ch)) {  // Operator
            while (!s.isEmpty() && precedence(ch) <= precedence(s.peek())) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }

    // Pop remaining operators from stack
    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

// Function to evaluate postfix expression
int evaluatePostfix(const string& postfix) {
    Stack s;

    for (char ch : postfix) {
        if (isdigit(ch)) {  // Operand
            s.push(ch - '0');
        }
        else if (isOperator(ch)) {  // Operator
            int b = s.pop();
            int a = s.pop();
            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.pop();  // Result is the last value in the stack
}

int main() {
    string infix;

    // Input infix expression
    cout << "Enter infix expression: ";
    cin >> infix;

    // Convert infix to postfix
    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    // Evaluate postfix expression
    int result = evaluatePostfix(postfix);
    cout << "Postfix evaluation result: " << result << endl;

    return 0;
}
