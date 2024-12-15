#include <iostream>
using namespace std;

// Function to maintain max-heap property
void MaxHeapify(int a[], int i, int n) {
    int largest = i, left = 2 * i, right = 2 * i + 1;
    if (left <= n && a[left] > a[largest]) largest = left;
    if (right <= n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(a[i], a[largest]);
        MaxHeapify(a, largest, n);  // Recursively heapify
    }
}

// Heap sort function
void HeapSort(int a[], int n) {
    for (int i = n / 2; i >= 1; i--) MaxHeapify(a, i, n);  // Build max-heap
    for (int i = n; i >= 2; i--) {
        swap(a[1], a[i]);  // Move root to end
        MaxHeapify(a, 1, i - 1);  // Heapify the reduced heap
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n + 1];  // 1-based index
    for (int i = 1; i <= n; i++) cin >> arr[i];  // Input elements

    HeapSort(arr, n);  // Sort the array

    for (int i = 1; i <= n; i++) cout << arr[i] << " ";  // Output sorted array

    return 0;
}
