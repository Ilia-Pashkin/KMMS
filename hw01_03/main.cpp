using namespace std;
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <algorithm>
#include <iterator>

void array_generator(int *arr, unsigned int Size) {
    for (int i=0; i < Size; i++) {
        arr[i] = rand() % 100;
    }
};

void sequencedEvenOddSort (int *arr, unsigned int Size) {
    bool sorted = false;
    int init = 0;
    while (!sorted or init != 0) {
        sorted = true;
        for (int j = init; j < Size - 1; j += 2)
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                sorted = false;
            }
        if (init == 0)
            init = 1;
        else init = 0;
    }

};

void paralleledEvenOddSort (int *arr, unsigned int Size) {
    bool sorted = false;
    int init = 0;
    while (!sorted or init != 0) {
        sorted = true;
        omp_set_num_threads(4);
        #pragma omp parallel shared(sorted)
        for (int j = init; j < Size - 1; j += 2)
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                sorted = false;
            }
        if (init == 0)
            init = 1;
        else init = 0;
    }
};

int main() {
    unsigned int number_of_arrays = 20;
    double total_time_sequenced = 0;
    double total_time_paralleled = 0;
    unsigned int n = 10000;

    for (int i=0; i<number_of_arrays; i++) {
        int *a1 = new int[n];
        array_generator(a1, n);
        int *a2 = new int[n];
        for (int j = 0; j < n; j++)
            a2[j] = a1[j];

        cout << "Iteration number: " << i+1 << endl;
        double startTime, finishTime;
        startTime = omp_get_wtime();
        sequencedEvenOddSort(a1, n);
        finishTime = omp_get_wtime();
        cout << "sequenced" << endl;
        cout << (finishTime - startTime) << endl << endl;
        total_time_sequenced += finishTime - startTime;

        startTime = omp_get_wtime();
        paralleledEvenOddSort(a2, n);
        finishTime = omp_get_wtime();
        cout << "parallelled" << endl;
        cout << (finishTime - startTime) << endl << endl;
        total_time_paralleled += finishTime - startTime;
    }
    cout << "Total time on sequenced sort: " << total_time_sequenced << endl;
    cout << "Total time on paralleled sort: " << total_time_paralleled << endl;
}
