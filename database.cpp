#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    char division[10];
    char address[100];
};

// Function to add a student record to the file
void addStudent() {
    Student s;
    fstream file("students.dat", ios::app | ios::binary);

    cout << "Enter roll number: ";
    cin >> s.rollNo;
    cin.ignore();  // To ignore the newline character after entering roll number
    
    cout << "Enter name: ";
    cin.getline(s.name, 50);

    cout << "Enter division: ";
    cin.getline(s.division, 10);

    cout << "Enter address: ";
    cin.getline(s.address, 100);

    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();

    cout << "Student record added successfully!" << endl;
}

// Function to delete a student record from the file
void deleteStudent() {
    int rollNo;
    cout << "Enter roll number of student to delete: ";
    cin >> rollNo;

    fstream file("students.dat", ios::in | ios::binary);
    fstream tempFile("temp.dat", ios::out | ios::binary);

    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == rollNo) {
            found = true;
        } else {
            tempFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        }
    }

    file.close();
    tempFile.close();

    // Remove the original file and rename the temp file
    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "Student record not found!" << endl;
    }
}

// Function to display a student's record by roll number
void displayStudent() {
    int rollNo;
    cout << "Enter roll number to search: ";
    cin >> rollNo;

    fstream file("students.dat", ios::in | ios::binary);
    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == rollNo) {
            found = true;
            cout << "\nStudent Details:\n";
            cout << "Roll No: " << s.rollNo << endl;
            cout << "Name: " << s.name << endl;
            cout << "Division: " << s.division << endl;
            cout << "Address: " << s.address << endl;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Student record not found!" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nStudent Database Menu:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
