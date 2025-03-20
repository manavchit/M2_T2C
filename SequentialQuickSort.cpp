#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

// Partition function for QuickSort
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive QuickSort function
void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;  // Generate random numbers
    }

    auto start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    cout << "Sequential QuickSort Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;

    return 0;
}
