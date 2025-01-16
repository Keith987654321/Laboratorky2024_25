#include "func.hpp"
#include <iostream>

int** createSquareMatrix(int n)
{
    int** matrix = new int*[n];

    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
    }

    return matrix;
}


void fillSquareMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << "Enter a number: ";
            std::cin >> matrix[i][j];
        }
    }
}


void printSquareMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


bool SquareMatrixHasIdenticalColumns(int** matrix, int n)
{
    for (int i = 0; i < n - 1; i++) // берёт столбец для сравнения
    {
        for (int j = i + 1; j < n; j++) // берёт другие столбцы
        {
            int counter = 0; 
            for (int k = 0; k < n; k++) //пробегает по всем элементам столбцов
            {
                if (matrix[k][i] == matrix[k][j]) counter++;
            }
            if (counter == n) return true;
        }
    }

    return false;
}


bool SquareMatrixHasPrimeNumber(int** matrix, int n, bool useAbs)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (useAbs) 
            {
                if (isPrime(abs(matrix[i][j]))) return true;
            }
            else
            {
                if (isPrime(matrix[i][j])) return true;
            } 
        }
    }

    return false;
}


bool isPrime(int n) 
{   
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) 
    {
        if (n % i == 0) return false; 
    }
    return true;
}


int findSumOfArrayElem(int* array, int length, bool sumByAbs)
{
    int counter = 0;
    if (sumByAbs)
    {
        for (int i = 0; i < length; i++)
        {
            counter += abs(array[i]);
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            counter += array[i];
        }
    }

    return counter;
}


void deleteSquareMatrix(int** matrix, int length)
{
    for (int i = 0; i < length; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}