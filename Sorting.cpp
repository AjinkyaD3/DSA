#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n  - 1; j++) {
            if (arr[j] > arr[j + 1]) { 
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

   for (int i = 0; i < n - 1; i++){
    cout<<arr[i] <<", ";
   }
}

int main() {
    int arr[] = {90,231,12312,1312,2312,323,322,111};
    int len = sizeof (arr) / sizeof(arr[0]);
    // bubbleSort(arr, len);
    
    return 0;
}
