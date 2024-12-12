#include <iostream>
#include <string>
using namespace std;

// Node structure for the stack
struct Node {
    char data;
    Node* next;
};

// Stack ADT using a singly linked list
class Stack {
private:
    Node* top;

public:
    Stack() { top = nullptr; }

    bool isEmpty() { return top == nullptr; }

    void push(char value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            cerr << "Stack Underflow!" << endl;
            return '\0';
        }
        char value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    char peek() {
        if (isEmpty()) {
            cerr << "Stack is empty!" << endl;
            return '\0';
        }
        return top->data;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Helper function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

// Helper function to check if a character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to check if a character is a digit
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Function to check if a character is an alphanumeric character
bool isAlnum(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Function to calculate power manually
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// Function to convert infix to postfix
string infixToPostfix(const string& infix) {
    Stack stack;
    string postfix = "";

    for (char ch : infix) {
        if (isAlnum(ch)) { // Operand
            postfix += ch;
        } else if (ch == '(') { // Left parenthesis
            stack.push(ch);
        } else if (ch == ')') { // Right parenthesis
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop(); // Remove '(' from stack
        } else if (isOperator(ch)) { // Operator
            while (!stack.isEmpty() && precedence(ch) <= precedence(stack.peek())) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) { // Pop remaining operators
        postfix += stack.pop();
    }

    return postfix;
}

// Function to convert infix to prefix
string infixToPrefix(const string& infix) {
    Stack stack;
    string prefix = "";
    string reversedInfix = "";

    // Reverse the infix expression and handle parentheses
    for (int i = infix.length() - 1; i >= 0; i--) {
        char ch = infix[i];
        if (ch == '(') {
            reversedInfix += ')';
        } else if (ch == ')') {
            reversedInfix += '(';
        } else {
            reversedInfix += ch;
        }
    }

    string reversedPostfix = infixToPostfix(reversedInfix);

    // Reverse the postfix expression to get prefix
    for (int i = reversedPostfix.length() - 1; i >= 0; i--) {
        prefix += reversedPostfix[i];
    }

    return prefix;
}

// Function to evaluate a postfix expression
int evaluatePostfix(const string& postfix) {
    Stack stack;

    for (char ch : postfix) {
        if (isDigit(ch)) { // Operand
            stack.push(ch - '0'); // Convert char to int
        } else if (isOperator(ch)) { // Operator
            int b = stack.pop();
            int a = stack.pop();

            switch (ch) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
                case '^': stack.push(power(a, b)); break;
            }
        }
    }

    return stack.pop();
}

// Function to evaluate a prefix expression
int evaluatePrefix(const string& prefix) {
    Stack stack;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isDigit(ch)) { // Operand
            stack.push(ch - '0'); // Convert char to int
        } else if (isOperator(ch)) { // Operator
            int a = stack.pop();
            int b = stack.pop();

            switch (ch) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
                case '^': stack.push(power(a, b)); break;
            }
        }
    }

    return stack.pop();
}

int main() {
    string infix;

    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    string prefix = infixToPrefix(infix);
    cout << "Prefix: " << prefix << endl;

    cout << "Evaluating Postfix: " << evaluatePostfix(postfix) << endl;
    cout << "Evaluating Prefix: " << evaluatePrefix(prefix) << endl;

    return 0;
}
