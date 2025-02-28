#include <iostream>

class MyVector {
    private:
        int _size, _capacity;
        int *_data;
    
        void Swap(MyVector& a, MyVector& b) {
            std::swap(a._size, b._size);
            std::swap(a._capacity, b._capacity);
            std::swap(a._data, b._data);
        }

        void ExtendCapacity(int newCapacity) {
            int *tmp = new int[newCapacity];

            for (int i = 0; i < _size; i++) 
                tmp[i] = _data[i];
            delete[] _data;
            _data = tmp;
            _capacity = newCapacity;
        }

    public:
        MyVector() {                                            // Конструктор по умолчанию
            _size = 0;
            _capacity = 8;
            _data = new int[8];
        }

        MyVector(int capacity) {                                // Конструктор с заранее заданной вместительностью
            _size = 0;
            _capacity = capacity;
            _data = new int[_capacity];
        }

        MyVector(int capacity, int defaultValue) {              // Конструктор с заранее заданными вмест. и изначальным значением всех его элем.
            _size = capacity;
            _capacity = capacity;
            _data = new int[_capacity];

            for (int i = 0; i < _capacity; i++) {
                _data[i] = defaultValue;
            }
        }

        MyVector(const MyVector & other) {                      // Копирующий конструктор
            _size = other._size;
            _capacity = other._capacity;
            _data = new int[_capacity];

            for (int i = 0; i < _size; i++)
                _data[i] = other._data[i];
        }

       MyVector& operator=(MyVector tmp) {                      // Оператор присваивания копированием
            Swap(tmp,*this);
            return *this;
       }

       void resize(int newCapacity) {                           // Меняет максимальную вместительность
            if (newCapacity < 0) { std::cout << "Invalid capacity\n"; return; }
            if (_capacity < newCapacity)
                ExtendCapacity(newCapacity);
            else if (_capacity > newCapacity) {
                int *tmp = new int[newCapacity];
                for (int i = 0; i < ((newCapacity < _size) ? newCapacity : _size); i++)
                    tmp[i] = _data[i];
                delete _data;
                _data = tmp;
                _capacity = newCapacity;
            }
       }

       void reverse() {                                         // Переставляет элементы в обратном порядке
        for (int i = 0; i < _size / 2; i++) 
            std::swap(_data[i], _data[_size - 1 - i]);
       }

       void push_back(int item) {                               // Добавляет новый элем. в конец
            if (_size < _capacity) {
                _data[_size] = item;
                _size++;
            }
            else {
                ExtendCapacity(_capacity + 8);
                push_back(item);
            }
       }

       void print() {                                           
        for (int i = 0; i < _size; i++) {
            std::cout << _data[i] << " ";
        }
        std::cout << "\n";
       }

       void shrink_to_fit() {                                   // Делает вместительность равной количеству элементов
            if (_size == _capacity) return;
            int *tmp = new int[_size];

            for (int i = 0; i < _size; i++)
                tmp[i] = _data[i];
            delete[] _data;
            _data = tmp;
            _capacity = _size;
       }

       int& back() { return _data[_size - 1]; }                 

       int& front() { return _data[0]; }                       

       int size() { return _size; }                             

       bool empty() { return (_size == 0) ? true : false; }     

       int capacity() { return _capacity; }                     

       void insert(int index, int item) {                       // Вставляет новый элемент в указанный индекс
            if (index >= _size || index < 0) { std::cout << "Index out of range\n"; return; }
            if (_size + 1 > _capacity) { 
                int newCapacity = _capacity + 8;
                int *tmp = new int[newCapacity];

                for (int i = 0; i < index; i++) 
                    tmp[i] = _data[i];
                
                tmp[index] = item;

                for (int i = index; i < _size; i++)
                    tmp[i + 1] = _data[i];
                
                delete[] _data;
                _data = tmp;
                _capacity = newCapacity;
            }

            else {
                for (int i = _size - 1; i >= index; i--) 
                    _data[i + 1] = _data[i];
                _data[index] = item;
            }
        _size++;
       }

       void erase(int index) {                                  // Стирает элемент в указанном индексе  сдвигает все элементы справа в лево
            if (index >= _size || index < 0) { std::cout << "Index out of range\n"; return; }

            for (int i = index; i < _size - 1; i++) 
                _data[i] = _data[i + 1];
            
            _data[_size - 1] = 0;
            _size--;
       }

       const int& operator[](int index) {
            if (index >= _size || index < 0) { 
                std::cout << "Index out of range, returns first index\n"; 
                return _data[0]; 
            }
            return _data[index];
       }

       MyVector operator+(const MyVector& other) {
            MyVector a(_capacity);
            if (_size != other._size) { std::cout << "Length isn't equal\n"; return a; }
            for (int i = 0; i < _size; i++) 
                a.push_back(_data[i] + other._data[i]);
            return a;
       }

       MyVector operator-(const MyVector& other) {
            MyVector a(_capacity);
            if (_size != other._size) { std::cout << "Length isn't equal\n"; return a; }
            for (int i = 0; i < _size; i++) 
                a.push_back(_data[i] - other._data[i]);
            return a;
        }

        MyVector operator*(int x) {
            MyVector a(_capacity);
            for (int i = 0; i < _size; i++) {
                a.push_back(_data[i] * x);
            }
            return a;
        }

        int dot_product(const MyVector& other) {                // Скалярное произведение векторов
            if (_size != other._size) { std::cout << "Length isn't equal\n"; return -1; }
            int product = 0;
            for (int i = 0; i < _size; i++) 
                product += _data[i] * other._data[i];
            return product;
        }

        MyVector vector_product(const MyVector& other) {        // Векторное произведение векторов
            if (_size != 3 || _size != other._size) { std::cout << "Can't do vector product\n"; return *this; }
            MyVector a(3);
            a.push_back(_data[1] * other._data[2] - _data[2] * other._data[1]);
            a.push_back(-(_data[0] * other._data[2] - _data[2] * other._data[0]));
            a.push_back(_data[0] * other._data[1] - _data[1] * other._data[0]);
            return a;
        }

        ~MyVector() {                                           // Деструктор
            if (_data != nullptr) 
                delete[] _data;
        }
};


int main() {
    MyVector a;
    std::cout << a.empty() << std::endl;
    a.push_back(5);
    a.push_back(7);
    a.push_back(10);

    MyVector b;
    b = a;
    b.push_back(11);
    a.print();
    b.print();

    MyVector c = b;
    c.erase(1);
    c.shrink_to_fit();
    std::cout << c.capacity() << std::endl;

    std::cout << std::endl;

    MyVector d = c;
    d.resize(d.capacity() + 97);
    std::cout << d.capacity() << std::endl;
    std::cout << d.front() << " " << d.back() << std::endl;

    MyVector e = d;
    e.insert(1, 121);
    e.print();

    std::cout << std::endl;

    MyVector f(3, 1);
    f.print();
    f = f + a;
    f.print();
    f = f - a;
    f.print();
    f = f * 10;
    f.print();
    std::cout << f.dot_product(a) << std::endl;
    
    std::cout << std::endl;

    MyVector g, h;
    g.push_back(-2);
    g.push_back(3);
    g.push_back(0);

    h.push_back(-2);
    h.push_back(0);
    h.push_back(6);
    g = g.vector_product(h);
    g.print();

    return 0;
}