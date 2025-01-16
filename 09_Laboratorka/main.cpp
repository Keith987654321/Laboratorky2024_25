// Дано целое число типа int, выведите на экран содержимое каждого из его байтов, используя знания по указателям. Дайте обоснование полученному результату.


#include <iostream>
#include <iomanip>
using namespace std;


int main() 
{
    unsigned int x;
    cout << "Enter a number: " << endl;
    cin >> x;

    //unsigned int* p = &x;
    unsigned char* n = (unsigned char*) &x;
    for (int i = 0; i < 4; i++)
    {
        cout << hex << (int) *(n + i) << " ";
    }

    return 0;
}