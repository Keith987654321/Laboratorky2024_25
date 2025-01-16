/* Ввести натуральные числа A, B и C. Если A кратно B и B больше C, то вывести A/B+C, если A кратно B и B меньше C, то вывести A/B-C, в остальных случаях вывести (A+B)*C.
Ввести натуральное число N, обозначающее номер месяца в году. Используя оператор switch вывести названия всех месяцев года. Предусмотреть обработку ошибочного ввода N.
Переменная x может принимать 2 значения: -1 и 1. Если -1, то вывести в консоль “Negative number”, если положительное - “Positive number”. Предложить вариант программы и объяснить свой выбор.*/

#include <iostream>
using namespace std;


void first()
{
    int a, b, c;
    cout << "Enter three natural numbers\n";
    cin >> a >> b >> c;

    if (a % b == 0 && b > c)
    {
        cout << (a / (b+c));
    }
    else if ( a % b == 0 && b < c)
    {
        cout << (a / (a - b));
    }
    else
    {
        cout << (a + b)*c;
    }
    cout << endl;
}


void second()
{
    int n;
    cout << "Enter month number\n";
    cin >> n;

    switch (n) 
    {
        case 1:
        cout << "January";
        break;

        case 2:
        cout << "February";
        break;

        case 3:
        cout << "March";
        break;

        case 4:
        cout << "April";
        break;

        case 5:
        cout << "May";
        break;

        case 6:
        cout << "June";
        break;

        case 7:
        cout << "July";
        break;

        case 8:
        cout << "August";
        break;

        case 9:
        cout << "September";
        break;

        case 10:
        cout << "October";
        break;

        case 11:
        cout << "November";
        break;

        case 12:
        cout << "December";
        break;

        default:
        cout << " You have entered an incorrect value";
        break;
    }
    cout << endl;
}


void third() // Пользователь вводит любое число, но значение x всё равно остаётся равным 1 или -1 в зависимости от того, что он ввёл. Даже если пользователь ввёл 0.
{
    int x = 0;
    cout << "Enter a digit, except zero\n";

    while (x == 0)
    {
        cin >> x;

        if (x == 0)
        {
            cout << "Enter a digit, EXCEPT ZERO!!!\n";
        }
    }

    if (x / abs(x) == 1)
    {
        cout << "Positive number";
    }
    else
    {
        cout << "Negative number";
    }
    cout << endl;
}


int main()
{
    first();
    cout << endl;
    second();
    cout << endl;
    third();
    cout << endl;
    
    system("pause");
    return 0;
}
