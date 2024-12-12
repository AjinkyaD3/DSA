#include <iostream>
#include <string>
using namespace std;

const int MaxStudent = 10;

struct Student {
    int roll_no;
    string name; // Keeping string
    float sgpa;
};

// 1. Input Function
void input(Student s[]) {
    for (int i = 0; i < MaxStudent; i++) {
        cout << "\nEnter the Roll number of the student: ";
        cin >> s[i].roll_no;

        cout << "Enter the Name of Roll No. " << s[i].roll_no << ": ";
        cin.ignore(); // To avoid newline issues after cin
        getline(cin, s[i].name); // Use getline for reading full name

        cout << "Enter the SGPA of Roll No. " << s[i].roll_no << ": ";
        cin >> s[i].sgpa;
    }
}

// 2. Display Function
void display(Student list[]) {
    cout << "\n---------------------------------------------------\n";
    cout << "Sr.No.  Roll No.   Student Name             SGPA\n";
    cout << "---------------------------------------------------\n";

    for (int i = 0; i < MaxStudent; i++) {
        // Manually format and align the output
        cout << i + 1 << "       " 
             << list[i].roll_no << "         " 
             << list[i].name; 
        
        // Add spaces for alignment based on name length
        int name_length = list[i].name.length();
        for (int j = 0; j < 20 - name_length; j++) cout << " ";
        
        cout << list[i].sgpa << "\n";
    }
}

// 3. Bubble Sort
void bubble_sort(Student s[]) {
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
void insertion_sort(Student s[]) {
    for (int i = 1; i < MaxStudent; i++) {
        Student key = s[i];
        int j = i - 1;

        while (j >= 0 && s[j].name > key.name) { // String comparison
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
    cout << "\n\t\t* Insertion Sort: Name *" << endl;
    display(s);
}

// 5. Quick Sort
void quick_sort(Student s[], int first, int last) {
    if (first < last) {
        int p = first, i = first, j = last;

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
void search_sgpa(Student list[]) {
    float sgpa;
    cout << "\nEnter SGPA: ";
    cin >> sgpa;

    cout << "\n--------------------------------------------------------\n";
    cout << "Sr.No.  Roll No.   Student Name             SGPA\n";
    cout << "--------------------------------------------------------\n";

    for (int i = 0; i < MaxStudent; i++) {
        if (list[i].sgpa == sgpa) {
            cout << i + 1 << "       " 
                 << list[i].roll_no << "         " 
                 << list[i].name;

            int name_length = list[i].name.length();
            for (int j = 0; j < 20 - name_length; j++) cout << " ";
            
            cout << list[i].sgpa << "\n";
        }
    }
}

// 7. Binary Search
int binary_search(Student s[]) {
    insertion_sort(s);

    string key;
    cout << "\nEnter the Name you want to search: ";
    cin.ignore();
    getline(cin, key);

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
void view(Student list[], int count) {
    cout << "\n--------------------------------------------------------\n";
    cout << "Sr.No.  Roll No.   Student Name             SGPA\n";
    cout << "--------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << i + 1 << "       " 
             << list[i].roll_no << "         " 
             << list[i].name;

        int name_length = list[i].name.length();
        for (int j = 0; j < 20 - name_length; j++) cout << " ";
        
        cout << list[i].sgpa << "\n";
    }
}

int main() {
    Student s[MaxStudent];
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
