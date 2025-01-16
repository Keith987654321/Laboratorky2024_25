/* 
Дана последовательность натуральных чисел {Aj}. Найти произведение чисел, оканчивающихся цифрой 2 или 4, наименьшее из таких чисел и номер этого числа в последовательности.
Дано натуральное число N (N<10^9). Найти наибольшую цифру числа N.
*/

#include <iostream>
using namespace std;


void fillArray(int* array, int length)
{
    cout << "Enter " << length << " numbers\n";
    for (int i = 0; i < length; i++)
    {
        int x;
        cin >> x;
        array[i] = x;
    }
}


void printArray(int* array, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << "\t";
    }
}


void printProduct(int* array, int length)
{
    int productOfNumbers = 1;
    for (int i = 0; i < length; i++)
    {
        if ((array[i] % 10 == 2) || (array[i] % 10 == 4))
        {
            productOfNumbers *= array[i];
        }
    }
    cout << "Product of numbers is " << productOfNumbers;
}


void printMinOfNumbers(int* array, int length)
{
    int minNumber = array[0],
    minNumberIndex = -1;
    
    for (int i = 0; i < length; i++)
    {
        if (minNumber >= array[i])
        {
            minNumber = array[i];
            minNumberIndex = i;
        }
    }

    cout << "Min number from array is: " << minNumber << endl;
    cout << "Min number index in array is: " << minNumberIndex;
}


void printMaxDigitOfNumber(int number)
{
    int maxDigit = 0;

    while (number != 0)
    {
        if (number % 10 > maxDigit)
        {
            maxDigit = number % 10;
        }

        number /= 10;
    }

    cout << "Max digit in number is " << maxDigit;
}


int main()
{
    //First task
    int arrayLength = 0;
    cout << "Enter array length\n";
    cin >> arrayLength;

    int* myArray = new int[arrayLength];

    
    fillArray(myArray, arrayLength);
    cout << endl;
    printProduct(myArray, arrayLength);
    cout << endl;
    printMinOfNumbers(myArray, arrayLength);
    cout << endl;
    
    delete[] myArray;

    //Second task
    int n = 0;
    cout << endl << "Enter a number ";
    cin >> n;

    printMaxDigitOfNumber(n);
    cout << endl;

    system("pause");
    return 0;
}