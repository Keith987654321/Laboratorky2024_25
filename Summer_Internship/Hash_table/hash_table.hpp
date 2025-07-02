#include <iostream>
#include "buckets.hpp"

template<typename N, typename T>
class HashTable{
private:
    int capacity;
    int elemCounter;
    Node<T, N>* array;

    int GetHash(N key);

    int GetIndex(N key);

    void Resize();

public:
    HashTable(int length = 5) : capacity(length), elemCounter(0) {
        array = new Node<T, N>[capacity];
    }

    HashTable(const HashTable& other);

    HashTable<N, T>& operator= (const HashTable<N, T>& other);

    ~HashTable();

    void print(); // debug only

    int add(N key, T value);

    int length();

    T get(N key);

    T popItem(N key);

    bool erase(N key);

    T* values();

    N* keys();

    HashTable<N, T> copy();

    void clear();
};

template<typename N, typename T>
int HashTable<N, T>::GetHash(N key) {
    std::hash<N> intHash;
    int index = intHash(key);
    return abs(index);
}

template<typename N, typename T>
int HashTable<N, T>::GetIndex(N key) {
    int index = GetHash(key);
    return (index % capacity);
}

template<typename N, typename T>
HashTable<N, T>::HashTable(const HashTable& other) : HashTable(other.capacity) {
    for (int i = 0; i < capacity; i++) {
        Node<T, N>* temp = other.array[i].next;
        while (temp) {
            this->add(temp->key, temp->data);
            temp = temp->next;
        }
    }
}

template<typename N, typename T>
HashTable<N, T>::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        array[i].Clear();
    }
    delete[] array;
}

template<typename N, typename T>
HashTable<N, T>& HashTable<N, T>::operator= (const HashTable<N, T>& other){
    if (this == &other) return *this;
    this->clear();
    delete[] array;
    capacity = other.capacity;
    array = new Node<T, N>[capacity];
    elemCounter = 0;
    
    for (int i = 0; i < capacity; i++) {
        Node<T, N>* temp = other.array[i].next;
        while (temp) {
            this->add(temp->key, temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

template<typename N, typename T>
void HashTable<N, T>::Resize() {
        int oldCapacity = capacity;
        capacity *= 2;
        Node<T, N>* new_array = new Node<T, N>[capacity];
        for (int i = 0; i < oldCapacity; i++) {
            Node<T, N>* temp = array[i].next;
            while(temp) {
                int new_index = GetIndex(temp->key);
                new_array[new_index].Pushback(temp->key, temp->data);
                temp = temp->next;
            } 
        }
        delete[] array;
        array = new_array;
}

template<typename N, typename T>
void HashTable<N, T>::print() { // Debug only
    for (int i = 0; i < capacity; i++) {
        array[i].PrintList();
    }
}

template<typename N, typename T>
int HashTable<N, T>::add(N key, T value) {
    int index = GetIndex(key);
    bool newWasCreated = array[index].Pushback(key, value);
    if (newWasCreated) {                         
        ++elemCounter;
        float loadFactor = elemCounter * 1.0f / capacity;
        if (loadFactor >= 0.7) { Resize(); }
    }
    return index;
}

template<typename N, typename T>
int HashTable<N, T>::length() {
    return elemCounter;
}

template<typename N, typename T>
T HashTable<N, T>::get(N key) {
    int index = GetIndex(key);
    return array[index].GetByKey(key);
}

template<typename N, typename T>
T HashTable<N, T>::popItem(N key) {
    int index = GetIndex(key);
    --elemCounter;
    return array[index].PopItem(key);
}

template<typename N, typename T>
bool HashTable<N, T>::erase(N key) {
    try {   
        popItem(key);
        --elemCounter;
        return true;
    }
    catch (...) {
        return false;
    }
}

template<typename N, typename T>
T* HashTable<N, T>::values() {
    T* arr = new T[elemCounter];
    int counter = 0;
    for (int i = 0; (i < capacity) && (counter < elemCounter); i++) {
        Node<T, N>* temp = array[i].next;
        while (temp) {
            arr[counter] = temp->data;
            ++counter;
            temp = temp->next;
        }
    }
    return arr;
}

template<typename N, typename T>
N* HashTable<N, T>::keys() {
    N* arr = new N[elemCounter];
    int counter = 0;
    for (int i = 0; (i < capacity) && (counter < elemCounter); i++) {
        Node<T, N>* temp = array[i].next;
        while (temp) {
            arr[counter] = temp->key;
            ++counter;
            temp = temp->next;
        }
    }
    return arr;
}

template<typename N, typename T>
HashTable<N, T> HashTable<N, T>::copy() {
    HashTable<N, T> temp(*this);
    return temp;
}

template<typename N, typename T>
void HashTable<N, T>::clear() {
    for (int i = 0; i < capacity; i++) {
        array[i].Clear();
    }
    elemCounter = 0;
}