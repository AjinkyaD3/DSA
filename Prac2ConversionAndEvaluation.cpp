// #include <iostream>
// #include <cctype>
// using namespace std;

// // Node structure for stack using singly linked list
// struct Node {
//     char data;
//     Node* next;
//     Node(char value) : data(value), next(nullptr) {}
// };


// class Stack {
// private:
//     Node* top;

// public:
//     Stack(){ 
//         top=nullptr;
//     }

//     bool isEmpty() {
//         return top == nullptr;
//     }

//     void push(char value) {
//         Node* newNode = new Node(value);
//         newNode->next = top;
//         top = newNode;
//     }

//     char pop() {
//         if (isEmpty()) return '\0';
//         char value = top->data;
//         top = top->next;
//         return value;
//     }

//     char peek() {
//         return isEmpty() ? '\0' : top->data;
//     }
// };

// // Helper function to check if a character is an operator
// bool isOperator(char ch) {
//     return (ch == '+' || ch == '-' || ch == '*' || ch == '/'|| ch == '^');
// }

// // Helper function to get precedence of operators
// int precedence(char op) {
//     if (op == '+' || op == '-') return 1;
//     if (op == '*' || op == '/') return 2;
//     if (op == '^' ) return 3;
//     return 0;
// }

// // Function to convert infix to postfix
// string infixToPostfix(const string& infix) {
//     Stack s;
//     string postfix = "";

//     for (char ch : infix) {
//         if (isalnum(ch)) {  // Operand
//             postfix += ch;
//         }
//         else if (ch == '(') {  // Left Parenthesis
//             s.push(ch);
//         }
//         else if (ch == ')') {  // Right Parenthesis
//             while (!s.isEmpty() && s.peek() != '(') {
//                 postfix += s.pop();
//             }
//             s.pop();  // Pop '('
//         }
//         else if (isOperator(ch)) {  // Operator
//             while (!s.isEmpty() && precedence(ch) <= precedence(s.peek())) {
//                 postfix += s.pop();
//             }
//             s.push(ch);
//         }
//     }

//     // Pop remaining operators from stack
//     while (!s.isEmpty()) {
//         postfix += s.pop();
//     }

//     return postfix;
// }

// // Function to evaluate postfix expression
// int evaluatePostfix(const string& postfix) {
//     Stack s;

//     for (char ch : postfix) {
//         if (isdigit(ch)) {  // Operand
//             s.push(ch - '0');
//         }
//         else if (isOperator(ch)) {  // Operator
//             int b = s.pop();
//             int a = s.pop();
//             switch (ch) {
//                 case '+': s.push(a + b); break;
//                 case '-': s.push(a - b); break;
//                 case '*': s.push(a * b); break;
//                 case '/': s.push(a / b); break;
//             }
//         }
//     }

//     return s.pop();  // Result is the last value in the stack
// }

// int main() {
//     string infix;

//     // Input infix expression
//     cout << "Enter infix expression: ";
//     cin >> infix;

//     // Convert infix to postfix
//     string postfix = infixToPostfix(infix);
//     cout << "Postfix expression: " << postfix << endl;

//     // Evaluate postfix expression
//     int result = evaluatePostfix(postfix);
//     cout << "Postfix evaluation result: " << result << endl;

//     return 0;
// }
#include <iostream>
#include <cctype> // for isdigit and isalnum
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stack {
    Node* top;
public:
    Stack() : top(nullptr) {}

    void push(int val) {
        Node* newNode = new Node{val, top};
        top = newNode;
    }

    int pop() {
        if (top == nullptr) return -1; // Return -1 for empty stack
        Node* temp = top;
        int val = top->data;
        top = top->next;
        delete temp;
        return val;
    }

    int peek() {
        return top ? top->data : -1;
    }

    bool empty() {
        return top == nullptr;
    }
};

int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

string infixToPostfix(const string& infix) {
    Stack s;
    string postfix;
    
    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;  // Append operand to postfix
        } else if (ch == '(') {
            s.push(ch);  // Push '(' onto stack
        } else if (ch == ')') {
            while (!s.empty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop(); // Pop '('
        } else {  // Operator
            while (!s.empty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop(); // Pop operators of higher precedence
            }
            s.push(ch);  // Push current operator
        }
    }

    while (!s.empty()) {
        postfix += s.pop();  // Pop remaining operators
    }

    return postfix;
}

string reverse(const string& str) {
    Stack s;
    for (char ch : str) {
        s.push(ch);
    }

    string reversed;
    while (!s.empty()) {
        reversed += s.pop();
    }

    return reversed;
}

string infixToPrefix(const string& infix) {
    string reversed = reverse(infix);
    string postfix = infixToPostfix(reversed);
    return reverse(postfix);
}

int evaluateExpression(const string& exp, bool isPrefix = false) {
    Stack s;
    int start = isPrefix ? exp.length() - 1 : 0;
    int end = isPrefix ? -1 : exp.length();
    int step = isPrefix ? -1 : 1;

    for (int i = start; i != end; i += step) {
        char ch = exp[i];
        
        if (isdigit(ch)) {
            s.push(ch - '0');  // Convert char to integer
        } else {
            int val2 = s.pop();
            int val1 = s.pop();

            switch (ch) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
                default: break;
            }
        }
    }

    return s.peek();
}

int main() {
    string infix = "a+b*c-(d/e+f)*g";
    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    // Evaluate expressions
    string prefixExpr = "*+98-97";
    string postfixExpr = "23+4*";

    int prefixVal = evaluateExpression(prefixExpr, true);
    int postfixVal = evaluateExpression(postfixExpr);

    cout << "Prefix evaluation: " << prefixVal << endl;
    cout << "Postfix evaluation: " << postfixVal << endl;

    return 0;
}
