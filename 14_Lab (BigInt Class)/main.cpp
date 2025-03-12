#include <iostream>
using namespace std;

class BigInt {
private:
    char* _data = nullptr;
    size_t _capacity;
    size_t _length;
    bool _isNegative = false;

    void ExtendCapacity(size_t x = 8) {
        char* tmp = _data;
        _capacity += x;
        _data = new char[_capacity];
        for (int i = 0; i <= _length; i++) _data[i] = tmp[i];
        delete[] tmp;
    }

    bool CheckCapacity(size_t n) {
        if (n >= _capacity) {
            ExtendCapacity(n + 8);
            return false;
        }
        return true;
    }

    void MakeNulls(size_t n) {
        for (int i = _length; i < n; i++) {
            _data[i] = '0';
        }
        _data[n] = 0;
        _length = n;
    }

    BigInt& Sum(const BigInt& other) {
        CheckCapacity(other._length + 1);
        bool flag = true;
        short carry = 0;
        if (other._length > _length) { MakeNulls(other._length); }
        else { flag = false; }
        _data[_length] = '0';

        if (flag) {
            for (int i = 0; i < other._length; i++) {
                short tmp = static_cast<short>((_data[i] - '0') + (other._data[i] - '0')) + carry;
                carry = 0;
                if (9 < tmp && tmp < 100) { carry = tmp / 10; }
                _data[i] = static_cast<char>((tmp % 10) + '0');
            }
            if (carry != 0) { _data[_length] = static_cast<char>(carry + '0'); }
        }

        else {
            for (int i = 0; i < other._length; i++) {
                short tmp = static_cast<short>((_data[i] - '0') + (other._data[i] - '0')) + carry;
                carry = 0;
                if (9 < tmp && tmp < 100) { carry = tmp / 10; }
                _data[i] = static_cast<char>((tmp % 10) + '0');
            }
            for (int i = other._length; i < _length; i++) {
                if (carry == 0) { break; }
                short tmp = static_cast<short>(_data[i] - '0') + carry;
                carry = 0;
                if (9 < tmp && tmp < 100) { carry = tmp / 10; }
                _data[i] = static_cast<char>((tmp % 10) + '0');
            }
            if (carry != 0) { _data[_length] = static_cast<char>(carry + '0'); }
        }

        if (_data[_length] != '0') { _length++; }
        _data[_length] = 0;

        return *this;
    }

    BigInt& Subtraction(const BigInt& other) {
        short minus_next = 0;
        for (int i = 0; i < other._length; i++) {
            short tmp = static_cast<short>((_data[i] - '0') - (other._data[i] - '0')) - minus_next;
            minus_next = 0;
            if (tmp < 0) {
                minus_next = 1;
                tmp += 10;
            }
            _data[i] = static_cast<char>(tmp + '0');
        }

        for (int i = other._length; i < _length; i++) {
            if (minus_next == 0) { break; }
            short tmp = static_cast<short>(_data[i] - '0') - minus_next;
            minus_next = 0;
            if (tmp < 0) {
                minus_next = 1;
                tmp += 10;
            }
            _data[i] = static_cast<char>(tmp + '0');
        }

        for (int i = _length - 1; i >= 0; i--) {
            if (_data[i] != '0') {
                _length = i + 1;
                break;
            }
            else { _length--; }
        }

        if (_length == 0) { _data[0] = '0'; _length++; }
        _data[_length] = 0;

        return *this;
    }

    BigInt& Multiplication(const BigInt& other) {
        short new_arr_len = _length + other._length;
        CheckCapacity(new_arr_len + 1);
        char* new_arr = new char[_capacity];

        for (int i = 0; i < new_arr_len + 1; i++) { new_arr[i] = '0'; }short carry = 0, sum_carry = 0, temp_j = 0;;
        for (int i = 0; i < other._length; i++) {
            for (int j = 0; j < _length; j++) {
                short tmp = static_cast<short>((_data[j] - '0') * (other._data[i] - '0')) + carry + sum_carry;
                sum_carry = 0;
                carry = tmp / 10;
                if (tmp > 9) {
                    tmp = tmp % 10;
                }
                short sum_tmp = static_cast<short>(new_arr[i + j] - '0') + tmp;
                sum_carry = sum_tmp / 10;
                if (sum_tmp > 9) {
                    sum_tmp = sum_tmp % 10;
                }

                new_arr[i + j] = static_cast<char>(sum_tmp + '0');
                temp_j = j + 1;
            }
            if (carry != 0) { new_arr[i + temp_j] = static_cast<char>(carry + '0'); carry = 0; }
            if (sum_carry != 0) { new_arr[i + temp_j] = new_arr[i + temp_j] + static_cast<char>(sum_carry); sum_carry = 0; }
        }
        if (new_arr[new_arr_len - 1] == '0') { new_arr_len--; }
        new_arr[new_arr_len] = 0;

        char* tmp_arr = _data;
        _data = new_arr;
        new_arr = tmp_arr;
        delete[] new_arr;

        _length = new_arr_len;

        return *this;
    }

public:
    BigInt() = default;

    BigInt(size_t capacity) {
        //_isNegative = false;
        _capacity = capacity;
        _length = 0;
        _data = new char(_capacity);
        _data[0] = 0;
    }

    BigInt(const char* number) {
        short start_point = 0;
        if (number[0] == '-') {
            _isNegative = true;
            start_point = 1;
        }
        _capacity = 0;
        for (int i = start_point; ; i++) {
            char tmp = number[i];
            if (tmp == 0) {
                _length = i - start_point;
                break;
            }
        }
        _capacity = _length + 8;
        _data = new char[_capacity];
        //for (int i = start_point; i < _length + start_point; i++) { _data[i - start_point] = number[_length + start_point - i - 1]; }
        for (int i = _length - 1; i >= 0; i--) {
            _data[_length - i - 1] = number[i + start_point];
        }
        _data[_length] = 0;
    }

    BigInt(const BigInt& other) {
        _isNegative = other._isNegative;
        _length = other._length;
        _capacity = other._capacity;
        _data = new char[_capacity];
        for (int i = 0; i < _length; i++) _data[i] = other._data[i];
    }

    BigInt& operator=(const BigInt& other) {
        _isNegative = other._isNegative;
        _length = other._length;
        _capacity = other._capacity;
        if (_data != nullptr) delete[] _data;
        _data = new char[_capacity];
        for (int i = 0; i < _length; i++) _data[i] = other._data[i];
        _data[_length + 1] = 0;
        return *this;
    }

    ~BigInt() {
        if (_data != nullptr) delete[] _data;
    }

    bool isNegative() { return _isNegative; }

    size_t capacity() { return _capacity; }

    size_t length() { return _length; }

    void print() {
        if (_length == 1 && _data[0] == '0') { _isNegative = false; }
        if (_isNegative) { fputc('-', stdout); }
        for (int i = _length - 1; i >= 0; i--) fputc(_data[i], stdout);
        fputc('\n', stdout);
    }

    BigInt& operator+=(const BigInt& other) {
        if (!_isNegative && !other._isNegative) { return this->Sum(other); }

        else if (_isNegative && other._isNegative) { return this->Sum(other); }

        else if (!_isNegative && other._isNegative) { 
            if (*this >= other) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                return this->Subtraction(temp);
            }
        }

        else {
            if (*this >= other) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                return this->Subtraction(temp);
             }
        }
    }

    BigInt operator+(const BigInt& other) {
        BigInt a = *this;
        a += other;
        return a;
    }

    BigInt& operator*=(const BigInt& other) {
        if (other._isNegative) { _isNegative = !_isNegative; }
        return this->Multiplication(other);
    }

    BigInt operator*(const BigInt& other) {
        BigInt a = *this;
        a *= other;
        return a;
    }

    BigInt& operator-=(const BigInt& other) {
        if (!_isNegative && !other._isNegative) { 
            if (*this >= other) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                _isNegative = true;
               return this->Subtraction(temp);
            }
        }
        
        else if (_isNegative && other._isNegative) { 
            if (*this >= other) { 
                _isNegative = true;
                return this->Subtraction(other); 
            }
            else {
                BigInt temp = *this;
                *this = other;
                _isNegative = false;
               return this->Subtraction(temp);
            }
        }

        else if (!_isNegative && other._isNegative) { 
            return this->Sum(other);
        }

        else { return this->Sum(other); }
    }

    bool operator<(const BigInt& other) {
        if (_length < other._length) return true;
        if (_length > other._length) return false;for (int i = _length - 1; i >= 0; i--) {
            if (_data[i] < other._data[i]) return true;
            if (_data[i] > other._data[i]) return false;
        }
        return false;
    }

    bool operator>=(const BigInt& other) {
        return !(*this < other);
    }

    bool operator>(const BigInt& other) {
        if (_length < other._length) return false;
        if (_length > other._length) return true;

        for (int i = _length - 1; i >= 0; i--) {
            if (_data[i] < other._data[i]) return false;
            if (_data[i] > other._data[i]) return true;
        }
        return false;
    }

    bool operator<=(const BigInt& other) {
        return !(*this > other);
    }

    bool operator==(const BigInt& other) {
        if (_length != other._length) return false;

        for (int i = 0; i < _length; i++) {
            if (_data[i] != other._data[i]) return false;
        }
        return true;
    }

    bool operator!=(const BigInt& other) {
        return !(*this == other);
    }
};

int main() {
    //BigInt a = "-12345";
    BigInt a("100");
    BigInt b = "10";
    //BigInt a("199");
    //BigInt b = "11";
    a *= b;
    //cout << a.length() << endl;
    //cout << b.length() << endl;
    //BigInt c(3);
    //cout << a.length() << endl;
    //cout << b.length() << endl;
    //cout << c.length() << endl;
    //cout << c.capacity() << endl;
    cout << a.length() << endl;
    a.print();
    //cout << (a != b) << endl;
}

/*
for (int i = 0; i < _length; i++) {

}

if (!_isNegative) { // Работаем с положительн числом

            
            if (!other._isNegative) { return this->Subtraction(other); }
            else { return this->Sum(other); }
            
        }
        // Здесь работаем с негативным числом
        else if (_length >= other._length) { // Если длина первого больше или равна длине второго
            if (!other._isNegative) { return this->Subtraction(other); }
            else { return this->Sum(other); }
        }
        else { // Если длина первого меньше длины второго
            if (!other._isNegative) { return this->Sum(other); }
            //else { return }
        }


BigInt& operator*=(const BigInt& other) {
            short new_arr_len = _length + other._length;
            CheckCapacity(new_arr_len + 1);
            char *new_arr = new char[_capacity];

            for (int i = 0; i < new_arr_len + 1; i++) { new_arr[i] = '0'; }

            short carry, sum_carry = 0;
            for (int i = 0; i < other._length; i++) {
                //carry = 0; sum_carry = 0;
                for (int j = 0; j < _length; j++) {
                    short tmp = static_cast<short>((_data[j] - '0') * (other._data[i] - '0')) + carry + sum_carry;
                    sum_carry = 0;
                    carry = tmp / 10;
                    if (tmp > 9) {
                        tmp = tmp % 10;
                    }
                    short sum_tmp = static_cast<short>(new_arr[i + j] - '0') + tmp;
                    sum_carry = sum_tmp / 10;
                    if (sum_tmp > 9) {
                        sum_tmp = sum_tmp % 10;
                    }

                    new_arr[i + j] = static_cast<char>(sum_tmp + '0');
                }
            }
            if (new_arr[new_arr_len - 1] == '0') { new_arr_len--; }
            new_arr[new_arr_len] = 0;

            char *tmp_arr = _data;
            _data = new_arr;
            new_arr = tmp_arr;
            delete[] new_arr;

            _length = new_arr_len;

            return *this;
        }BigInt& operator+=(const BigInt& other) {
            CheckCapacity(other._length + 1); // потом попробовать убрать единицу
            _data[_length] = '0';
            short carry = 0;
            bool flag = true;
            if (other._length > _length) { _length = other._length; flag = false; }
            for (int i = 0; i < other._length; i++) {
                short tmp = static_cast<short>((_data[i] - '0') + (other._data[i] - '0')) + carry;
                carry = 0;
                if (9 < tmp && tmp < 100) { carry = tmp / 10; }
                _data[i] = static_cast<char>((tmp % 10) + '0');
            }
            if (flag) {
                for (int i = other._length; i < _length + 1; i++) {
                    short tmp = static_cast<short>(_data[i] - '0') + carry;
                    carry = 0;
                    if (9 < tmp && tmp < 100) { carry = tmp / 10; }
                    _data[i] = static_cast<char>((tmp % 10) + '0');
                }
                if (_data[_length] != '0') { _length++; }
            }

            _data[_length] = 0;
            return *this;
        }


*/

/*
BigInt& operator+=(const BigInt& other) {
    short tmp;
    if (other._length > _length) {
        if (other._length >= _capacity) {
            ExtendCapacity(other._length - _capacity + 8);
        }
    }
    for (int i = 0; i < other._length; i++) {
        if (i >= _length) {
            _length++;
            _data[i + 1] = 0;
            _data[i] = '0';
        }
        tmp = static_cast<short>((_data[i] - '0') + (other._data[i] - '0'));
        if (tmp > 9) {
            if (CheckCapacity(i + 1)) {
                _data[i + 1] = '0';
                _length++;
            }
            _data[i + 1]++;
            tmp -= 10;
        }
        _data[i] = static_cast<char>(tmp + '0');
    }
    return *this;
}
*/
/*
        BigInt& operator+=(const BigInt& other) {
            for (int i = 0; i < other._length; i++) {
                AddDigits(_data, other._data[i], i, *this);
            }
            return *this;
        }

        void AddDigits(char *data, char c, size_t index, BigInt& current) {
            short tmp = static_cast<short>((data[index] - '0') + (c - '0'));
            if (tmp > 9) {
                short remainder = tmp % 10;
                AddDigits(data, static_cast<short>((tmp / 10) + '0'), index + 1, current);
                current._length++;
            }
            data[index] = static_cast<short>(tmp + '0');
        }
*/
/*
        BigInt& operator+=(const BigInt& other) {
            char *tmp_arr = new char[other._length + 8];
            tmp_arr[0] = '0';
            for (int i = 0; i < _length; i++) { // Складываем все цифры, пока не закончится длина числа к которому прибалвяем
                short tmp = static_cast<short>((_data[i] - '0') + (other._data[i] - '0'));
                if (9 < tmp && tmp < 100) { tmp_arr[i + 1] = static_cast<char>((tmp / 10) + '0'); }
                _data[i] = static_cast<short>((tmp % 10) + '0');
            }
            tmp_arr[_length + 1] = 0;
            if (other._length > _length) { // Добавляем непоместившиеся цифры в число
                CheckCapacity(other._length);
                for (int i = _length; i < other._length; i++) {
                    _length++;
                    _data[i] = other._data[i];
                }
                _data[_length] = 0;
            }
            short carry = 0;
            for (int i = 1; i < _length; i++) { // Складываем цифры из числа с цифрами из массива tmp_arr
                short tmp = static_cast<short>((_data[i] - '0') + (tmp_arr[i] - '0')) + carry;
                carry = 0;
                if (9 < tmp && tmp < 100) {
                    carry = tmp / 10;
                }
                _data[i] = static_cast<char>((tmp % 10) + '0');
            }
            return *this;
        }
        */