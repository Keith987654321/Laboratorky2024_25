#pragma once
int** createSquareMatrix(int n);
int findSumOfArrayElem(int* array, int length, bool sumByAbs = false);
void printSquareMatrix(int** matrix, int n);
void fillSquareMatrix(int** matrix, int n);
void deleteSquareMatrix(int** matrix, int length);
bool SquareMatrixHasIdenticalColumns(int** matrix, int n);
bool SquareMatrixHasPrimeNumber(int** matrix, int n, bool useAbs = false);
bool isPrime(int n);