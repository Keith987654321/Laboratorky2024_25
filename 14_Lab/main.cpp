#include <iostream>
using namespace std;

class BigInt {
    private:
        char* _data = nullptr;
        size_t _capacity;
        size_t _length;

        void ExtendCapacity(size_t x = 8) {
            char *tmp = _data;
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

    public:
        BigInt() = default;

        BigInt(size_t capacity) {
            _capacity = capacity;
            _length = 0;
            _data = new char(_capacity);
            _data[0] = 0;
        }

        BigInt(const char *number) {
            _capacity = 0;
            for (int i = 0; ; i++) {
                char tmp = number[i];
                if (tmp == 0) {
                    _length = i;
                    break;
                }
            }
            _capacity = _length + 8;
            _data = new char[_capacity];
            for (int i = 0; i < _length; i++) _data[i] = number[_length - i - 1];
            _data[_length + 1] = 0;
        }

        BigInt(const BigInt& other) {
            _length = other._length;
            _capacity = other._capacity;
            _data = new char[_capacity];
            for (int i = 0; i < _length; i++) _data[i] = other._data[i];
        }

        BigInt& operator=(const BigInt& other) {
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
        
        size_t capacity() { return _capacity; }

        size_t length() { return _length; }

        void print() {
            for (int i = _length - 1; i >= 0; i--) fputc(_data[i], stdout);
            fputc('\n', stdout);
        }

        BigInt& operator*=(const BigInt& other) {
            short new_arr_len = _length + other._length;
            //char *new_arr = new char(new_arr_len);
            BigInt new_big_int(new_arr_len + 8);
            new_big_int.MakeNulls(new_arr_len);
            //new_big_int._data[_length] = '0';
            short carry = 0;
            for (int i = 0; i < other._length; i++) {
                for (int j = 0; j < _length; j++) {
                    short temporal = static_cast<short>((other._data[i] - '0') * (_data[j] - '0')) + carry;
                    carry = 0;
                    if (9 < temporal && temporal < 100) { carry = temporal / 10; } 
                    temporal %= 10;
                    /*
                    for (int i = 0; i < other._length; i++) {
                        short tmp = static_cast<short>((_data[i] - '0') + (other._data[i] - '0')) + carry;
                        carry = 0;
                        if (9 < tmp && tmp < 100) { carry = tmp / 10; }
                        _data[i] = static_cast<char>((tmp % 10) + '0');
                    }
                    */
                    short tmp_carry = 0;
                    short tmp = static_cast<short>(new_big_int._data[i + j] - '0') + temporal + tmp_carry;
                    tmp_carry = 0;
                    if (9 < tmp && tmp < 100) { tmp_carry = tmp / 10; }
                    //new_big_int._data[]

                    for (int k = i + j; k < new_arr_len; k++) {
                        if (tmp_carry == 0) { break; }
                        short tmp = static_cast<short>(new_big_int._data[k] - '0') + tmp_carry;
                        tmp_carry = 0;
                        if (9 < tmp && tmp < 100) { tmp_carry = tmp / 10; }
                        new_big_int._data[k] = static_cast<char>((tmp % 10) + '0');
                    }
                    if (tmp_carry != 0) { new_big_int._data[new_arr_len] = static_cast<char>(carry + '0'); }
                }
            }
            _length = new_big_int._length;
            _capacity = new_big_int._capacity;
            swap(_data, new_big_int._data);
            delete[] new_big_int._data;
            
            return *this;
        }

        BigInt& operator+=(const BigInt& other) { 
            CheckCapacity(other._length + 1); //  + 1 потому что потом можем отодвинуть 
            bool flag = true;                // символ окончания строки на один элемент вправо
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
            //BigInt c = *this;
            return *this;
        }

        BigInt operator+(const BigInt& other) {
            BigInt a = *this;
            a += other;
            return a; 
        }
};

int main() {
    BigInt a("11");
    BigInt b = "2";
    a *= b;
    //BigInt c(3);
    //cout << b.length() << endl;
    //cout << b.length() << endl;
    //cout << c.length() << endl;
    //cout << c.capacity() << endl;
    a.print();
}

/* 
for (int i = 0; i < _length; i++) {
                
}

BigInt& operator+=(const BigInt& other) {
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