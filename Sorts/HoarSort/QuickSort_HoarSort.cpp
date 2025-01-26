#include <iostream>


int PartOfHoaraSort(int* arr, int left, int right) {
    int pivot = arr[(left + right) / 2];
    while (left <= right) {
        while(arr[left] < pivot) left++;
        while(arr[right] > pivot) right--;
        if (left <= right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    return left;
}


void HoaraSort(int* arr, int start, int end) {
    if (start >= end) return;
    int rightStart = PartOfHoaraSort(arr, start, end);
    HoaraSort(arr, 0, rightStart - 1);
    HoaraSort(arr, rightStart, end);
}


void QuickSort(int* arr, int arrayLength) {
    HoaraSort(arr, 0, arrayLength - 1);
}


int main() {
    const int LENGTH = 7;
    int mass[LENGTH] = {4, 3, 5, 9, 1, 2, 1};
    QuickSort(mass, LENGTH);

    for (int i = 0; i < LENGTH; i++) {
        std::cout << mass[i] << std::endl;
    }
    
    return 0;
}