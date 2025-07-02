#ifndef __BUCKETS__
#define __BUCKETS__

#include <iostream>
#include <stdexcept>

template<typename T, typename N>
struct Node {
    T data;
    N key;
    Node* next;

    Node(T new_data = T(), N new_key = N(), Node* next_elem = nullptr) 
    : data(new_data), key(new_key), next(next_elem) {}

    bool Pushback(N new_key, T new_data) {
        Node* temp = this;
        bool sameKey = false;
        while (temp->next) {
            if (temp->next->key == new_key) {
                sameKey = true;
                break;
            }
            temp = temp->next;
        }
        if (!sameKey) {
            temp->next = new Node(new_data, new_key, nullptr);
            return 1;
        }
        else {
            temp->next->data = new_data;
            return 0;
        }
    }

    void PrintList() {
        Node* temp = this->next;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        if (this->next) std::cout << std::endl;
    }

    T GetByKey(N key) {
        Node* temp = this->next;
        while (temp) {
            if (temp->key == key) {
                return temp->data;
            }
            temp = temp->next;
        }
        throw std::invalid_argument("No item with given key");
    }

    T PopItem(N key) {
        Node* temp = this;
        while (temp->next) {
            if (temp->next->key == key) {
                T returnValue = temp->next->data;
                Node* nodeToDelete = temp->next;
                temp->next = temp->next->next;
                delete nodeToDelete;
                return returnValue;
            }
            temp = temp->next;
        }
        throw std::invalid_argument("No item with given key");
    }

    void Clear() {
        Node* temp = this->next;
        while (temp) {
            this->next = temp->next;
            delete temp;
            temp = this->next;
        }
    }

};

#endif