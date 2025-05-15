#include <iostream>

struct BoolRef {
    friend class BoolVector;

    BoolRef(char Value, int Index, char* Data) : value(Value), index(Index), _data(Data) {}

    BoolRef& operator= (int value) {
        int byte = index / 8;
        int offset = index % 8;
        if (value) {
            _data[byte] |= (1 << offset);
        }
        else {
            _data[byte] &= ~(1 << offset);
        }
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& out, const BoolRef& Other) {
        out << Other.value;
        return out;
    }

private:
    bool value;
    int index;
    char *_data;
};

class BoolVector {
    char *data = nullptr;
    int length;
    int capacity;

    void IncreaseCapacity(int newCapacity = 0);

public:
    BoolVector(int len = 1) : length(0), capacity(len) { data = new char[capacity]; }

    ~BoolVector() { delete[] data; }

    void PushBack(int value);

    void Print();

    int Size() { return length; }

    void Insert(int index, int value);

    void Erase(int index);

    BoolRef operator[] (int index) {
        int byte = index / 8;
        int offset = index % 8;
        BoolRef a((data[byte] & (1 << offset)), index, data);
        return a;
    }

    BoolRef Get(int index) { return this->operator[](index); }
};

void BoolVector::IncreaseCapacity(int newCapacity) {
        char *newData;
        if (newCapacity == 0) {
            newData = new char[capacity + 8];
            for (int i = 0; i < capacity; ++i) 
                newData[i] = data[i];
            
            capacity += 8;
        }
        else {
            newData = new char[newCapacity];
            for (int i = 0; i < capacity; ++i) 
                newData[i] = data[i];
            
            capacity = newCapacity;
        }

        delete[] data;
        data = newData;
    }

void BoolVector::PushBack(int value) {
        int byte = length / 8;
        int offset = length % 8;

        if (length == capacity * 8) { IncreaseCapacity(); }

        if (value) {
            data[byte] |= (1 << offset);
        }
        else {
            data[byte] &= ~(1 << offset);
        }
        ++length;
    }

void BoolVector::Print() {
    for (int i = 0; i < length; ++i) {
        int byte = i / 8;
        int offset = i % 8;
        std::cout << ( (data[byte] & (1 << offset)) ? 1 : 0 )<< " ";
    }
    std::cout << std::endl;
}

void BoolVector::Insert(int index, int value) {
    char previous = 0;
    char temp = 0;
    int byte = index / 8;
    int offset = index % 8;

    if (index >= length) {
        PushBack(value);
        return;
    }

    previous |= (data[byte] & (1 << offset));
    if (value) {
            data[byte] |= (1 << offset);
        }
    else {
            data[byte] &= ~(1 << offset);
    }

    for (int i = index + 1; i < length; ++i) {
        temp = previous;
        byte = i / 8;
        offset = i % 8;
        previous = (data[byte] & (1 << offset));
        if (previous) {
            data[byte] |= (1 << offset);
        }
        else {
            data[byte] &= ~(1 << offset);
        }
        previous = temp;
    }
    PushBack(previous);
}

void BoolVector::Erase(int index) {
    int byte;
    int offset;
    for (int i = index; i < length - 1; ++i) {
        byte = (i + 1) / 8;
        offset = (i + 1) % 8;
        char next = (data[byte] & (1 << offset));

        byte = i / 8;
        offset = i % 8;
        if (next) {
            data[byte] |= (1 << offset);
        }
        else {
            data[byte] &= ~(1 << offset);
        }
    }
    byte = length / 8;
    offset = length % 8;
    data[byte] &= ~(1 << offset);
    --length;
}

int main() {
    BoolVector a;
    for (int i =0; i < 6; i++) { 
        a.PushBack(i % 2);
    }
    a.Print();
    a.Insert(6, 1);
    a.Print();
    a.Erase(1);
    a.Print();

    std::cout << a.Size() << " - Vector size\n";
    std::cout << a[2] << std::endl;
    a[2] = 0;
    std::cout << a.Get(2) << std::endl;
    a.Print();

    return 0;
}