#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <chrono>

using namespace std;

// Partition function for QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing last element as pivot
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Parallel QuickSort using OpenMP tasks
void quickSortParallel(int arr[], int low, int high, int depth) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Set a threshold for when to use parallel execution
        if (depth > 0) {
            #pragma omp task
            quickSortParallel(arr, low, pi - 1, depth - 1);

            #pragma omp task
            quickSortParallel(arr, pi + 1, high, depth - 1);
        }
    }
}

int main() {
    int n, numThreads;
    cout << "Enter the size of the array: ";
    cin >> n;
    cout << "Enter the number of threads to use: ";
    cin >> numThreads;

    int* arrPar = new int[n];

    // Generate random array
    for (int i = 0; i < n; i++) {
        arrPar[i] = rand() % 100000;
    }

    // Measure Parallel QuickSort time
    auto startPar = chrono::high_resolution_clock::now();
    #pragma omp parallel num_threads(numThreads)
    {
        #pragma omp single
        quickSortParallel(arrPar, 0, n - 1, numThreads);
    }
    auto endPar = chrono::high_resolution_clock::now();
    auto durationPar = chrono::duration_cast<chrono::milliseconds>(endPar - startPar).count();
    cout << "Multi-threaded QuickSort Time with " << numThreads << " threads: " << durationPar << " ms\n";

    delete[] arrPar;
    return 0;
}
