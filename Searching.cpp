#include <iostream>
using namespace std;

int linearSearch(int ar[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (ar[i] == key) {
            cout << "Value Found at index: " << i + 1 << " value: " << key << endl;
            return i;
        }
    }
    return -1;
}

int binarySearch(int ar[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2; 
        if (ar[mid] == key) {
            cout << "Value Found at index: " << mid << " value: " << key << endl;
            return mid;
        }
        if (ar[mid] < key) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }
    return -1; 
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]); 
    binarySearch(arr, 0, size - 1, 50); 
    // linearSearch(arr, size, 300);
    return 0;
}
