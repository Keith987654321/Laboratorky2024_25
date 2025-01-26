#include <iostream>


int PartOfSortHoara(int left, int right, int* arr) {
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


void QuickSortHoara(int start, int end, int* arr) {
    if (start >= end) return;
    int rightStart = PartOfSortHoara(start, end, arr);
    QuickSortHoara(start, rightStart-1, arr);
    QuickSortHoara(rightStart, end, arr);
}


void QuickSortHoara(int* arr, int length) {
    QuickSortHoara(0, length - 1, arr);
}



int main() {

    const int length = 7;
    int mass[length] = {4, 3, 5, 9, 1, 2, 1};
    QuickSortHoara(mass, length);

    for (int i = 0; i <length; i++)
    {
        std::cout << mass[i] << std::endl;
    }
    return 0;
}