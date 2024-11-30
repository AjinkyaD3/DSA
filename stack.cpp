#include <iostream>
using namespace std;

int top = -1;  // Initialize stack pointer
#define n 5  // Define the size of the stack

int s[n];  // Declare the stack array with size n

// Push function to add an element to the stack
void push(int i) {
    if(top == n-1) {  // Check if the stack is full (top = n-1 for array size n)
        cout << "Overflow: Stack is full!" << endl;
        return;
    } else {
        top++;  // Move the top index up
        s[top] = i;  // Add value to stack
        cout << i << " pushed to stack" << endl;
    }
}

// Peek function to return the top element of the stack
int peek() {
    if(top == -1) {
        cout << "Stack is empty!" << endl;
        return -1;  // Return -1 if the stack is empty
    } else {
        cout << "Top element is: " << s[top] << endl;
        return s[top];  // Return the top element
    }
}

// Display function to show all elements in the stack
void display() {
    if(top == -1) {
        cout << "Stack is empty!" << endl;
    } else {
        cout << "Stack elements: ";
        for(int i = 0; i <= top; i++) {
            cout << s[i] << " ";
        }
        cout << endl;
    }
}

// Pop function to remove the top element from the stack
void pop() {
    if(top == -1) {  // Check if the stack is empty
        cout << "Underflow: Stack is empty!" << endl;
    } else {
        cout << s[top] << " popped from stack" << endl;
        top--;  // Move the top index down
    }
}

int main() {
    // Push elements to the stack
    push(5);
    push(4);
    push(2);
    push(3);
    push(1);
    push(6);  // This should trigger an overflow

    // Display the current elements in the stack
    display();

    // Peek at the top element
    peek();

    // Pop an element from the stack
    pop();
    
    // Display the stack again after popping
    display();

    return 0;
}
