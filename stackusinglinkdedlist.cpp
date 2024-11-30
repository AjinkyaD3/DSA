#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* top = NULL;

// Push operation
void push(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;  
    top = newNode; 
    cout << value << " pushed onto stack." << endl;
}

// Pop operation
void pop() {
    if (top == NULL) {
        cout << "Stack is empty, cannot pop." << endl;
        return;
    }
    // Remove the top node
    Node* temp = top;
    top = top->next;  // Move the top pointer to the next node
    cout << temp->data << " popped from stack." << endl;
    delete temp;  // Free the memory of the popped node
}

// Peek operation (view the top element)
void peek() {
    if (top == NULL) {
        cout << "Stack is empty." << endl;
        return;
    }
    cout << "Top element is " << top->data << endl;
}

// Check if stack is empty
bool isEmpty() {
    return top == NULL;
}

// Display the stack contents (optional)
void display() {
    if (top == NULL) {
        cout << "Stack is empty." << endl;
        return;
    }
    Node* temp = top;
    cout << "Stack contents: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Perform stack operations
    push(10);
    push(20);
    push(30);
    display();  // Display stack contents

    peek();  // View the top element

    pop();
    display();  // Display stack contents after pop

    pop();
    pop();
    pop();  // Trying to pop from an empty stack

    return 0;
}
