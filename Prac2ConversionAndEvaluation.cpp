#include <iostream>
#include <cctype>
using namespace std;

// Node structure for stack using singly linked list
struct Node {
    char data;   // To store character (operand/operator)
    Node* next;  // Pointer to the next node in the stack
    Node(char value) : data(value), next(nullptr) {}  // Constructor to initialize node
};

// Stack class implementation using linked list
class Stack {
private:
    Node* top;  // Pointer to the top of the stack

public:
    Stack(){ top = nullptr;}  // Initialize stack as empty

    // Check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Push a value onto the stack
    void push(char value) {
        Node* newNode = new Node(value);  // Create a new node
        newNode->next = top;              // Point new node to the current top
        top = newNode;                    // Update top to the new node
    }

    // Pop a value from the stack
    char pop() {
        if (isEmpty()) return '\0';  // Return null character if stack is empty
        char value = top->data;
        Node* temp = top;
        top = top->next;  // Update top to the next node
        delete temp;      // Free the memory of popped node
        return value;     // Return popped value
    }

    // Peek at the top value of the stack
    char peek() {
        return isEmpty() ? '\0' : top->data;  // Return top value or null character if empty
    }
};

// Check if the character is an operator (+, -, *, /, ^)
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Get the precedence of the operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;  // For non-operators, return 0
}

// Convert infix expression to postfix
string infixToPostfix(const string& infix) {
    Stack s;
    string postfix = "";  // String to hold the result

    for (char ch : infix) {
        if (isalnum(ch)) {  // If the character is an operand (number/letter)
            postfix += ch;  // Add it directly to the postfix result
        }
        else if (ch == '(') {  // If the character is '('
            s.push(ch);  // Push '(' onto the stack
        }
        else if (ch == ')') {  // If the character is ')'
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();  // Pop operators from stack until '(' is found
            }
            s.pop();  // Pop the '(' from stack
        }
        else if (isOperator(ch)) {  // If the character is an operator
            while (!s.isEmpty() && precedence(ch) <= precedence(s.peek())) {
                postfix += s.pop();  // Pop operators with higher or equal precedence
            }
            s.push(ch);  // Push the current operator onto the stack
        }
    }

    // Pop any remaining operators from the stack
    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

// Manually reverse a string (instead of using algorithm library)
string reverseString(const string& str) {
    string reversed = "";
    for (int i = str.length() - 1; i >= 0; --i) {
        reversed += str[i];  // Add characters from end to beginning
    }
    return reversed;
}

// Convert infix expression to prefix
string infixToPrefix(const string& infix) {
    // Reverse the infix expression
    string reversedInfix = reverseString(infix);

    // Replace '(' with ')' and vice versa in the reversed expression
    for (int i = 0; i < reversedInfix.length(); i++) {
        if (reversedInfix[i] == '(') reversedInfix[i] = ')';
        else if (reversedInfix[i] == ')') reversedInfix[i] = '(';
    }

    // Convert the reversed infix expression to postfix
    string reversedPostfix = infixToPostfix(reversedInfix);

    // Reverse the postfix expression to get the prefix expression
    return reverseString(reversedPostfix);
}

// Evaluate a postfix expression
int evaluatePostfix(const string& postfix) {
    Stack s;

    for (char ch : postfix) {
        if (isdigit(ch)) {  // If the character is a digit
            s.push(ch - '0');  // Convert char to int and push onto stack
        }
        else if (isOperator(ch)) {  // If the character is an operator
            int b = s.pop();  // Pop the second operand
            int a = s.pop();  // Pop the first operand
            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.pop();  // The result is the last value in the stack
}

// Evaluate a prefix expression
int evaluatePrefix(const string& prefix) {
    Stack s;

    // Traverse prefix expression from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];

        if (isdigit(ch)) {  // If the character is a digit
            s.push(ch - '0');  // Convert char to int and push onto stack
        }
        else if (isOperator(ch)) {  // If the character is an operator
            int a = s.pop();  // Pop the first operand
            int b = s.pop();  // Pop the second operand
            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.pop();  // The result is the last value in the stack
}

int main() {
    string infix;
    
    // Input the infix expression
    cout << "Enter infix expression: ";
    cin >> infix;

    // Convert infix to postfix
    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;
    
    // Evaluate postfix expression
    int postfixResult = evaluatePostfix(postfix);
    cout << "Postfix evaluation result: " << postfixResult << endl;

    // Convert infix to prefix
    string prefix = infixToPrefix(infix);
    cout << "Prefix expression: " << prefix << endl;
    
    // Evaluate prefix expression
    int prefixResult = evaluatePrefix(prefix);
    cout << "Prefix evaluation result: " << prefixResult << endl;

    return 0;
}
