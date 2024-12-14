#include <iostream>   // Include the input/output stream library for console input/output
#include <fstream>    // Include the file stream library to handle file operations
#include <string>     // Include the string library for handling strings
using namespace std;  // Use the standard namespace to avoid prefixing standard functions with 'std::'

// Function to add a student record
void addStudent() {
    int rollNo;  // Variable to store the student's roll number
    string name, division, address;  // Variables to store the student's name, division, and address
    
    cout << "Enter roll number: ";  // Ask the user for the roll number
    cin >> rollNo;  // Read the roll number input from the user
    cin.ignore();  // Ignore the newline left by the previous 'cin' operation to avoid issues with 'getline'
    
    cout << "Enter name: ";  // Ask the user for the student's name
    getline(cin, name);  // Read the entire name (including spaces) into the 'name' string
    
    cout << "Enter division: ";  // Ask the user for the student's division
    getline(cin, division);  // Read the entire division (including spaces) into the 'division' string
    
    cout << "Enter address: ";  // Ask the user for the student's address
    getline(cin, address);  // Read the entire address (including spaces) into the 'address' string
    
    // Open the file in append mode (this will add new data to the end of the file)
    ofstream file("students.txt", ios::app);  
    // Write the student's details to the file, separated by spaces, with each record on a new line
    file << rollNo << " " << name << " " << division << " " << address << endl;  
    file.close();  // Close the file after writing

    cout << "Student record added!" << endl;  // Inform the user that the record has been added
}

// Function to delete a student record by roll number
void deleteStudent() {
    int rollNo;  // Variable to store the roll number of the student to be deleted
    cout << "Enter roll number to delete: ";  // Ask the user for the roll number to delete
    cin >> rollNo;  // Read the roll number input
    
    // Open the original file for reading and a temporary file for writing
    ifstream file("students.txt");
    ofstream tempFile("temp.txt");
    
    int r;  // Variable to temporarily store the roll number from the file
    string n, d, addr;  // Variables to temporarily store the name, division, and address
    bool found = false;  // Flag to check if the student record was found and deleted
    
    // Read all records from the file and write them to the temporary file, skipping the matching rollNo
    while (file >> r) {
        file.ignore();  // Ignore the space between roll number and name
        getline(file, n, ' ');  // Read the name up to the space
        getline(file, d, ' ');  // Read the division up to the space
        getline(file, addr);  // Read the entire address
        
        if (r == rollNo) {  // If the roll number matches the one to delete
            found = true;  // Set the 'found' flag to true (record will not be written to temp file)
        } else {
            // Write the record to the temporary file if it's not the one to delete
            tempFile << r << " " << n << " " << d << " " << addr << endl;
        }
    }
    
    file.close();  // Close the original file
    tempFile.close();  // Close the temporary file
    
    if (found) {  // If the record was found and deleted
        remove("students.txt");  // Delete the original file
        rename("temp.txt", "students.txt");  // Rename the temporary file to replace the original file
        cout << "Student record deleted!" << endl;  // Inform the user that the record was deleted
    } else {
        cout << "Student not found!" << endl;  // If the record wasn't found, display a message
    }
}

// Function to display a student's record by roll number
void displayStudent() {
    int rollNo;  // Variable to store the roll number of the student to display
    cout << "Enter roll number to display: ";  // Ask the user for the roll number to display
    cin >> rollNo;  // Read the roll number input
    
    // Open the file for reading
    ifstream file("students.txt");
    
    int r;  // Variable to temporarily store the roll number from the file
    string n, d, addr;  // Variables to temporarily store the name, division, and address
    bool found = false;  // Flag to check if the student record was found
    
    // Read all records from the file and display the matching one
    while (file >> r) {
        file.ignore();  // Ignore the space between roll number and name
        getline(file, n, ' ');  // Read the name up to the space
        getline(file, d, ' ');  // Read the division up to the space
        getline(file, addr);  // Read the entire address
        
        if (r == rollNo) {  // If the roll number matches the one to display
            // Display the student's details
            cout << "\nStudent Details:\n";
            cout << "Roll No: " << r << endl;
            cout << "Name: " << n << endl;
            cout << "Division: " << d << endl;
            cout << "Address: " << addr << endl;
            found = true;  // Set the 'found' flag to true
            break;  // Exit the loop since the record has been found
        }
    }
    
    file.close();  // Close the file
    
    if (!found) {  // If no matching record was found
        cout << "Student not found!" << endl;  // Display an error message
    }
}

int main() {
    int choice;  // Variable to store the user's menu choice
    
    // Infinite loop to keep displaying the menu until the user chooses to exit
    while (true) {
        // Display the menu options
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";  // Ask the user for their choice
        cin >> choice;  // Read the user's choice
        
        // Switch statement to call the appropriate function based on the user's choice
        switch (choice) {
            case 1: addStudent(); break;  // Call the 'addStudent' function
            case 2: deleteStudent(); break;  // Call the 'deleteStudent' function
            case 3: displayStudent(); break;  // Call the 'displayStudent' function
            case 4: return 0;  // Exit the program
            default: cout << "Invalid choice!" << endl;  // If the choice is invalid, display an error message
        }
    }
    
    return 0;  // This line is never reached due to the infinite loop
}
