#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MaxStudent = 15;

struct student {
    int roll_no;
    string name;
    float sgpa;
};

// 1. Input Function
void input(student s[]) {
    for (int i = 0; i < MaxStudent; i++) {
        cout << "\nEnter the Roll number of the student: ";
        cin >> s[i].roll_no;

        cout << "Enter the Name of Roll No. " << s[i].roll_no << ": ";
        cin >> s[i].name;

        cout << "Enter the SGPA of Roll No. " << s[i].roll_no << ": ";
        cin >> s[i].sgpa;
    }
}

// 2. Display Function
void display(student list[]) {
    cout << "\n---------------------------------------------------\n";
    cout << left << setw(10) << "Sr.No."
         << left << setw(10) << "Roll No."
         << left << setw(25) << "Student Name"
         << left << setw(15) << "SGPA" << endl;
    cout << "---------------------------------------------------\n";

    for (int i = 0; i < MaxStudent; i++) {
        cout << left << setw(10) << i + 1
             << left << setw(10) << list[i].roll_no
             << left << setw(25) << list[i].name
             << left << setw(15) << list[i].sgpa << endl;
    }
}

// 3. Bubble Sort
void bubble_sort(student s[]) {
    for (int k = 0; k < MaxStudent; k++) {
        for (int j = 0; j < MaxStudent - 1; j++) {
            if (s[j].roll_no > s[j + 1].roll_no) {
                swap(s[j], s[j + 1]);
            }
        }
    }
    cout << "\n\t\t* Bubble Sort: Roll No. *" << endl;
    display(s);
}

// 4. Insertion Sort
void insertion_sort(student s[]) {
    for (int i = 1; i < MaxStudent; i++) {
        student key = s[i];
        int j = i - 1;

        while (j >= 0 && s[j].name > key.name) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
    cout << "\n\t\t* Insertion Sort: Name *" << endl;
    display(s);
}

// 5. Quick Sort
void quick_sort(student s[], int first, int last) {
    if (first < last) {
        int p = first, i = first, j = last;
        student temp;

        while (i < j) {
            while (s[i].sgpa >= s[p].sgpa && i < last) i++;
            while (s[j].sgpa < s[p].sgpa) j--;

            if (i < j) {
                swap(s[i], s[j]);
            }
        }
        swap(s[j], s[p]);

        quick_sort(s, first, j - 1);
        quick_sort(s, j + 1, last);
    }
}

// 6. Linear Search
void search_sgpa(student list[]) {
    float sgpa;
    cout << "\nEnter SGPA: ";
    cin >> sgpa;

    cout << "\n--------------------------------------------------------\n";
    cout << left << setw(10) << "Sr.No."
         << left << setw(10) << "Roll No."
         << left << setw(25) << "Student Name"
         << left << setw(15) << "SGPA" << endl;
    cout << "--------------------------------------------------------\n";

    for (int i = 0; i < MaxStudent; i++) {
        if (list[i].sgpa == sgpa) {
            cout << left << setw(10) << i + 1
                 << left << setw(10) << list[i].roll_no
                 << left << setw(25) << list[i].name
                 << left << setw(15) << list[i].sgpa << endl;
        }
    }
}

// 7. Binary Search
int binary_search(student s[]) {
    insertion_sort(s);

    string key;
    cout << "\nEnter the Name you want to search: ";
    cin >> key;

    int low = 0, high = MaxStudent - 1;
    while (low <= high) {
        int mid = (low + high) / 2;

        if (key == s[mid].name) {
            return mid;
        } else if (key < s[mid].name) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

// 8. View Top Students
void view(student list[], int count) {
    cout << "\n--------------------------------------------------------\n";
    cout << left << setw(10) << "Sr.No."
         << left << setw(10) << "Roll No."
         << left << setw(25) << "Student Name"
         << left << setw(15) << "SGPA" << endl;
    cout << "--------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << i + 1
             << left << setw(10) << list[i].roll_no
             << left << setw(25) << list[i].name
             << left << setw(15) << list[i].sgpa << endl;
    }
}

int main() {
    student s[MaxStudent];
    input(s);
    display(s);

    int choice, cont = 0;
    do {
        cout << "\n##### MENU #####\n";
        cout << "1. Bubble Sort (Sort by Roll Number)\n";
        cout << "2. Insertion Sort (Sort by Name)\n";
        cout << "3. Quick Sort (Sort by SGPA)\n";
        cout << "4. Linear Search (Find students with same SGPA)\n";
        cout << "5. Binary Search (Find Student by Name)\n";

        cout << "\nSelect the Operation: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bubble_sort(s);
                break;
            case 2:
                insertion_sort(s);
                break;
            case 3:
                cout << "\n\t\t* Quick Sort: SGPA *" << endl;
                quick_sort(s, 0, MaxStudent - 1);
                view(s, MaxStudent);
                break;
            case 4:
                search_sgpa(s);
                break;
            case 5: {
                int result = binary_search(s);
                if (result == -1) {
                    cout << "Data not found!\n";
                } else {
                    cout << "Name found at Sr. No.: " << result + 1 << endl;
                }
                break;
            }
            default:
                cout << "Invalid Input!\n";
        }

        cout << "\nEnter 0 to EXIT or Enter 1 to RETURN MENU: ";
        cin >> cont;

    } while (cont == 1);

    cout << "Thank you!";
    return 0;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // Find the index of the smallest element
            }
        }
        // Swap the found minimum element with the first element
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

