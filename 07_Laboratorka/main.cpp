#include <iostream>
#include "func.hpp"
using namespace std;

//Дана целочисленная матрица {Aij}i=1...n;j=1..n , n<=100. Если в матрице есть два одинаковых столбца и есть хотя бы один элемент, 
//абсолютная величина которого - простое число, упорядочить строки матрицы по неубыванию суммы модулей элементов. 


int main()
{
    int n;
    cout << "Enter matrix scale: ";
    cin >> n;

    int** myMatrix = createSquareMatrix(n);
    fillSquareMatrix(myMatrix, n);
    

    if (SquareMatrixHasIdenticalColumns(myMatrix, n) && SquareMatrixHasPrimeNumber(myMatrix, n, true))
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (findSumOfArrayElem(myMatrix[i], n, true) > findSumOfArrayElem(myMatrix[j], n, true))
                {
                    swap(myMatrix[i], myMatrix[j]);
                }
            }
        }
        
    }

    printSquareMatrix(myMatrix, n);
    deleteSquareMatrix(myMatrix, n);

    return 0;
}