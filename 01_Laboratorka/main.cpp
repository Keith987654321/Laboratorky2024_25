#include <iostream>
#include <cmath>
using namespace std;


void VariableInfo(string VarName, unsigned __int64 VarSize, bool IsUnsigned  = false)
{
    long long temp;
    temp = pow(2, (8 * VarSize))/2;

    if (!IsUnsigned)
    {
        cout << "Тип " << VarName << " занимает в памяти " << VarSize << " байт" << endl;
        cout << "Минимальное значение: " << (-1)*temp << endl;
        cout << "Максимальное значение: " << --temp << "\n\n";
    }
    else
    {
        cout << "Тип " << VarName << " занимает в памяти " << VarSize << " байт" << endl;
        cout << "Минимальное значение: " << 0 << endl;
        cout << "Максимальное значение: " << temp*2 - 1 << "\n\n";
    }
}


void VarTypesInfo()
{
    cout << "Тип " << "bool" << " занимает в памяти 1 байт\n";
    cout << "Может принимать значения true или false\n\n";

    cout << "Тип " << "char" << " занимает в памяти 1 байт\n";
    cout << "Может принимать 256 символьных значений\n\n";

    VariableInfo("short int", (sizeof(short int)));

    VariableInfo("unsigned short int", (sizeof(unsigned short int)), true);

    VariableInfo("long int", (sizeof(long int)));

    VariableInfo("unsigned long int", (sizeof(unsigned long int)), true);
    
    VariableInfo("long long", (sizeof(long long)));
    
    cout << "Тип " << "unsigned long long" << " занимает в памяти 8 байт\n";
    cout << "Минимальное значение: " << 0 << endl;
    cout << "Максимальное значение: 18446744073709551615" << "\n\n";
    
    VariableInfo("int", (sizeof(int)));

    VariableInfo("unsigned int", (sizeof(long int)), true);

    cout << "Тип " << "float" << " занимает в памяти 4 байт\n";
    cout << "Минимальное значение: 1.2е-38" << endl;
    cout << "Максимальное значение: 3.4е38" << "\n\n";

    cout << "Тип " << "double" << " занимает в памяти 8 байт\n";
    cout << "Минимальное значение: 2.2е-308" << endl;
    cout << "Максимальное значение: 1.8е308" << "\n\n";
}


int main()
{
    cout.setf(ios_base::fixed);
    
    VarTypesInfo();

    int a, b;
    a = 6;
    b = 5;
    cout << a - b << endl; //пример операции вычитания с целочисленным типом данных

    float x, y;
    x = 11,5;
    y = 5,7;
    cout << x + y << endl; //пример операции сложения с вещественным типом данных
    
    unsigned int u_a, u_b;
    u_a = 555;
    u_b = 445;
    int c = u_a + u_b;  // пример операции сложения с беззнаковым типом данных
    cout << c << endl;

    short s_x, s_y;
    s_x = 55;
    s_y = 11;
    cout << s_x / s_y << endl; //пример операции деления с целочисленным типом данных

    double da, db;
    da = 1.23456;
    db = 5.5;
    cout << da * db << endl; //пример операции умножения с вещественным типом данных

    return 0;
}