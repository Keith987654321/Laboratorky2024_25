#include <iostream>

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

    void CheckIsInegative() {
        if (_length == 1 && _data[0] == '0') { _isNegative = false; }
    }

    size_t DigitLength(long long n) {
        n = abs(n);
        size_t tmp = n;
        size_t length = 0;
        while (tmp != 0) {
            ++length;
            tmp /= 10;
        }
        return length;
    }

    const char* FromNumberToString(long long n, size_t length = -1) {
        if (length == -1) { length = DigitLength(n); }
        char *new_arr = new char[length + 1];
        for (int i = length - 1; i >= 0; --i) {
            new_arr[i] = static_cast<char>((n % 10) + '0');
            n /= 10;
        }
        new_arr[length] = 0;
        return new_arr;
    } 
    
    bool AbsLess(const BigInt& other) {
        bool result;
        if (_length < other._length) result = true;
        else if (_length > other._length) result = false;
        else {
            for (int i = _length - 1; i >= 0; i--) {
                if (_data[i] < other._data[i]) { result = true; break; }
                if (_data[i] > other._data[i]) { result = false; break; }
            }
        }

        return result;
    }

    bool AbsGreaterOrEqual(const BigInt& other) { // Сравнивает по абсолютному значению 
        return !(this->AbsLess(other));
    }

    BigInt& Sum(const BigInt& other) { // Функция сложения двух БигИнтов
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

    BigInt& Subtraction(const BigInt& other) { // Функция вычитания двух БигИнтов
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

        if (_length == 1 && _data[0] == '0') { _isNegative = false; }

        return *this;
    }

    BigInt& Multiplication(const BigInt& other) { // Функция умножения двух БигИнтов
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

        if (_length == 1 && _data[0] == '0') { _isNegative = false; }

        return *this;
    }

public:
    BigInt() = default; // Стандартный коструктор

    BigInt(size_t capacity, bool makeEmpty) { // Конструктор, создающий не инициализированную переменную
        _capacity = capacity;
        _length = 0;
        _data = new char(_capacity);
        _data[0] = 0;
    }

    BigInt(const char* number) { // Конструктор, берущий значение БигИнта из строки
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
        if (_data != nullptr) { delete[] _data; }
        _data = new char[_capacity];
        for (int i = _length - 1; i >= 0; i--) {
            _data[_length - i - 1] = number[i + start_point];
        }
        _data[_length] = 0;
    }

    BigInt (size_t number) { // Конструктор, берущий значение БигИнта из числа
        _length = DigitLength(number);
        const char *char_number = FromNumberToString(number, _length);
        if (number < 0 ) { _isNegative = true; }
        _capacity = _length + 8;
        if (_data != nullptr) delete[] _data;
        _data = new char[_capacity];
        for (int i = _length - 1; i >= 0; i--) _data[_length - i - 1] = char_number[i];
        _data[_length] = 0;
        delete[] char_number;
    }

    BigInt(const BigInt& other) { // Конструктор копирования
        _isNegative = other._isNegative;
        _length = other._length;
        _capacity = other._capacity;
        _data = new char[_capacity];
        for (int i = 0; i < _length; i++) _data[i] = other._data[i];
    }

    BigInt& operator=(const BigInt& other) { // Оператор присваивания копированием
        _isNegative = other._isNegative;
        _length = other._length;
        _capacity = other._capacity;
        if (_data != nullptr) delete[] _data;
        _data = new char[_capacity];
        for (int i = 0; i < _length; i++) _data[i] = other._data[i];
        _data[_length + 1] = 0;
        return *this;
    }

    ~BigInt() { // Деструктор
        if (_data != nullptr) delete[] _data;
    }

    bool isNegative() const { return _isNegative; }

    size_t capacity() const { return _capacity; }

    size_t length() const { return _length; }

    const char& operator[] (size_t index) const { // Возвращает символ по индексу (изменять нельзя, только считывать)
        if (0 <= index && index < _length) { return _data[index]; }
        else { return _data[0]; }
    }

    void print() const {
        if (_isNegative) { fputc('-', stdout); }
        for (int i = _length - 1; i >= 0; i--) fputc(_data[i], stdout);
        fputc('\n', stdout);
    }

    BigInt& operator+=(const BigInt& other) { // Оператор += для сложения БигИнта с БигИнтом
        if (!_isNegative && !other._isNegative) { return this->Sum(other); }

        else if (_isNegative && other._isNegative) { return this->Sum(other); }

        else if (!_isNegative && other._isNegative) { 
            if (this->AbsGreaterOrEqual(other)) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                return this->Subtraction(temp);
            }
        }

        else {
            if (this->AbsGreaterOrEqual(other)) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                return this->Subtraction(temp);
             }
        }
    }

    BigInt& operator+=(size_t number) { // Оператор += для сложения БигИнта с числом
        BigInt other = number;
        if (!_isNegative && !other._isNegative) { return this->Sum(other); }

        else if (_isNegative && other._isNegative) { return this->Sum(other); }

        else if (!_isNegative && other._isNegative) { 
            if (this->AbsGreaterOrEqual(other)) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                return this->Subtraction(temp);
            }
        }

        else {
            if (this->AbsGreaterOrEqual(other)) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                return this->Subtraction(temp);
             }
        }
    }

    BigInt operator+(const BigInt& other) { // Оператор + для сложения БигИнта с БигИнтом
        BigInt a = *this;
        a += other;
        return a;
    }

    BigInt& operator-=(const BigInt& other) { // Оператор -= для вычитания БигИнта БигИнтом
        if (!_isNegative && !other._isNegative) { 
            if (this->AbsGreaterOrEqual(other)) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                _isNegative = true;
               return this->Subtraction(temp);
            }
        }
        
        else if (_isNegative && other._isNegative) { 
            if (this->AbsGreaterOrEqual(other)) { 
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

    BigInt& operator-=(size_t number) { // Оператор -= для вычитания БигИнта числом
        BigInt other = number;
        if (!_isNegative && !other._isNegative) { 
            if (this->AbsGreaterOrEqual(other)) { return this->Subtraction(other); }
            else {
                BigInt temp = *this;
                *this = other;
                _isNegative = true;
               return this->Subtraction(temp);
            }
        }
        
        else if (_isNegative && other._isNegative) { 
            if (this->AbsGreaterOrEqual(other)) { 
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

    BigInt operator-(const BigInt other) { // Оператор - для вычитания БигИнта БигИнтом
        BigInt a = *this;
        a -= other;
        return a;
    }

    BigInt& operator*=(const BigInt& other) { // Оператор *= для умножения БигИнта БигИнтом
        if (other._isNegative) { _isNegative = !_isNegative; }
        return this->Multiplication(other);
    }

    BigInt& operator*=(size_t number) { // Оператор *= для умножения БигИнта числом
        BigInt other = number;
        if (other._isNegative) { _isNegative = !_isNegative; }
        return this->Multiplication(other);
    }

    BigInt operator*(const BigInt& other) { // Оператор * для умножения БигИнта БигИнтом
        BigInt a = *this;
        a *= other;
        return a;
    }

    BigInt operator++(int) { // Оператор постфиксного инкремента (возвращает сначала старое значение, а потом прибавляет 1)
        BigInt copy = *this;
        *this += 1;
        return copy;
    }

    BigInt& operator++() { // Оператор префиксного инкремента (прибавляет 1 к бигинту и возвращает уже новое значение)
        *this += 1;
        return *this;
    }

    BigInt operator--(int) {
        BigInt copy = *this;
        *this -= 1;
        return copy;
    }

    BigInt& operator--() { // int в скобочках нужен, чтобы компилятор мог различить две одинаковые по написанию функции 
        *this -= 1;
        return *this;
    }

    bool operator<(const BigInt& other) {
        if (!_isNegative && !other._isNegative) {
            if (_length > other._length) { return false; }
            if (_length < other._length) { return true; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return false; }
                if (_data[i] < other._data[i]) { return true; }
            }
        }

        else if (_isNegative && other._isNegative) {
            if (_length > other._length) { return true; }
            if (_length < other._length) { return false; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return true; }
                if (_data[i] < other._data[i]) { return false; }
            }
        }

        else if (!_isNegative && other._isNegative) { return false; }

        return false;
    }

    bool operator<(size_t number) {
        BigInt other = number;
        if (!_isNegative && !other._isNegative) {
            if (_length > other._length) { return false; }
            if (_length < other._length) { return true; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return false; }
                if (_data[i] < other._data[i]) { return true; }
            }
        }

        else if (_isNegative && other._isNegative) {
            if (_length > other._length) { return true; }
            if (_length < other._length) { return false; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return true; }
                if (_data[i] < other._data[i]) { return false; }
            }
        }

        else if (!_isNegative && other._isNegative) { return false; }

        else { return true; }
    }

    bool operator>=(const BigInt& other) {
        return !(*this < other);
    }

    bool operator>=(size_t number) {
        BigInt other = number;
        return !(*this < other);
    }

    bool operator>(const BigInt& other) {
        if (!_isNegative && !other._isNegative) {
            if (_length > other._length) { return true; }
            if (_length < other._length) { return false; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return true; }
                if (_data[i] < other._data[i]) { return false; }
            }
        }

        else if (_isNegative && other._isNegative) {
            if (_length > other._length) { return false; }
            if (_length < other._length) { return true; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return false; }
                if (_data[i] < other._data[i]) { return true; }
            }
        }

        else if (!_isNegative && other._isNegative) { return true; }

        return false;
    }

    bool operator>(size_t number) {
        BigInt other = number;
        if (!_isNegative && !other._isNegative) {
            if (_length > other._length) { return true; }
            if (_length < other._length) { return false; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return true; }
                if (_data[i] < other._data[i]) { return false; }
            }
        }

        else if (_isNegative && other._isNegative) {
            if (_length > other._length) { return false; }
            if (_length < other._length) { return true; }

            for (int i = _length - 1; i >= 0; --i) {
                if (_data[i] > other._data[i]) { return false; }
                if (_data[i] < other._data[i]) { return true; }
            }
        }

        else if (!_isNegative && other._isNegative) { return true; }

        else { return false; }
    }

    bool operator<=(const BigInt& other) {
        return !(*this > other);
    }

    bool operator<=(size_t number) {
        BigInt other = number;
        return !(*this > other);
    }

    bool operator==(const BigInt& other) {
        if (_length != other._length) return false;

        for (int i = 0; i < _length; i++) {
            if (_data[i] != other._data[i]) return false;
        }
        return true;
    }

    bool operator==(size_t number) {
        BigInt other = number;
        if (_length != other._length) return false;

        for (int i = 0; i < _length; i++) {
            if (_data[i] != other._data[i]) return false;
        }
        return true;
    }

    bool operator!=(const BigInt& other) {
        return !(*this == other);
    }

    bool operator!=(size_t number) {
        BigInt other = number;
        return !(*this == other);
    }
};

BigInt operator+(size_t number, const BigInt& other) { // Оператор + для сложения числа с БигИнтом (предыдущие операторы + складывали наоборот, БигИнт с числом)
    BigInt a = number;
    a += other;
    return a;
}

BigInt operator-(size_t number, const BigInt& other) { // Оператор - для сложения числа с БигИнтом
    BigInt a = number;
    a -= other;
    return a;
}

BigInt operator*(size_t number, const BigInt& other) { // Оператор * для сложения числа с БигИнтом
    BigInt a = number;
    a *= other;
    return a;
}

std::istream& operator>>(std::istream& in, BigInt& other) { // Перегрузка оператора >> чтобы через std::cin записывать значение сразу в БигИнт
    std::string s;
    in >> s;
    other = BigInt(s.data());
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& other) { // Перегрузка оператора << чтобы через std::cout выводить значение БигИнта
    std::string s = "";
    if (other.isNegative()) { s += '-'; }
    for (int i = other.length() - 1; i >= 0; i--) s += other[i];
    out << s;
    return out;
}

int main() {
    BigInt a(10);
    BigInt b = 50;
    BigInt c = "-12345";

    a++;
    ++a;
    a.print();
    
    b--;
    --b;
    b.print();
    
    c += b;
    c -= a;
    c.print();
    #if 0
    std::cin >> a >> b;
    std::cout << "a + b = " << a + b << "\na - b = " << a - b << "\na * b = " << a * b << std::endl;
    std::cout << (a < b) << " " << (a > b) <<  " " << (a != b) << std::endl;
   #endif
    return 0;
}