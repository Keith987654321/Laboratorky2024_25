#include <iostream>
using namespace std;


struct Node {
    Node* right;
    Node* left;
    int data = -1;
};


void PushBack(Node* sent, int value) {
    Node* p = new Node;
    p->data = value;
    p->right = sent;
    p->left = sent->left;
    sent->left->right = p;
    sent->left = p;
}


void FillList(Node* sent, int length) {
    for (int i = 0; i < length; i++) {
        int data;
        cout << "Введите число: ";
        cin >> data;
        PushBack(sent, data);
    }
    
}


void PrintList(Node* sent) {
    Node* p = sent->right;
    while (p != sent) {
        cout << p->data << endl;
        p = p->right;
    }
}


void ClearList(Node* sent) {
    Node* p = sent->right;
    Node* q;
    while (p != sent) {
        q = p->right;
        delete p;
        p = q;
    }
    sent->right = sent;
    sent->left = sent;
}


Node* GetElemByIndex(Node* sent, int index) {
    Node* p = sent->right;
    for (int i = 0; i < index; i++) {
        p = p->right;
    }
    return p;
}


void DeleteElemByIndex(Node* sent, int index) {
    Node* p = sent->right;
    for (int i = 0; i < index; i++) {
        p = p->right;
    }
    p->left->right = p->right;
    p->right->left = p->left;
    delete p;
}


void InsertElemByIndex(Node* sent, int value, int index) {
    Node* p = sent->right;
    Node* q = new Node;
    q->data = value;
    for (int i = 0; i < index-1; i++) {
        p = p->right;
    }
    q->left = p;
    q->right = p->right;
    p->right->left = q;
    p->right = q;
}


void SortList(Node* sent) {
    Node* p = sent->right;
    for (Node* a = p; a->right != sent; a = a->right) {
        for (Node* b = a->right; b != sent; b = b->right) {
            if (a->data < b->data) swap(a->data, b->data);
        }
    }
}


int GetFirstDigit(int n) {
    while (n > 9) {
        n /= 10;
    }
    return n;
}


bool IsListSortedByLastDigit(Node* sent) {
    Node* p = sent->right;
    while (p->right != sent) {
        if ((p->data % 10) > (p->right->data % 10)) {
            return false;
        }
        p = p->right;
    }
    return true;
}


bool IsListSortedByFirstDigit(Node* sent) {
    Node* p = sent->right;
    while (p->right != sent) {
        if (GetFirstDigit(p->data) > GetFirstDigit(p->right->data)) {
            return false;
        }
        p = p->right;
    }
    return true;
}


bool IsOneToFive(int n) { // Проверяет, состоит ли число только из цифр 1,2,3,4 и 5
    while (n > 0) {
        if (n % 10 > 5 || n % 10 == 0) {
            return false;
        }
        n /= 10;
    }
    return true;
}


bool IsContainsSixOrEight(int n) { // Проверяет, есть ли в числе цифры 6 или 8
    while (n > 0) {
        if (n % 10 == 6 || n % 10 == 8) {
            return true;
        }
        n /= 10;
    }
    return false;
}


void DelAllOneToFiveNumbers(Node* sent) {
    Node* p = sent->right;
    for (int i = 0; p != sent;) {
        if (IsOneToFive(p->data)) {
            p = p->right;
            DeleteElemByIndex(sent, i);
        }
        else {
            p = p->right;
            ++i;
        }
    }
}


void DublicateAllNumbersWithSixOrEight(Node* sent) {
    Node* p = sent->right;
    for (int i = 0; p != sent;) {
        if (IsContainsSixOrEight(p->data)) {
            p = p->right;
            InsertElemByIndex(sent, p->left->data, i);
            i += 2;
        }
        else {
            p = p->right;
            ++i;
        }
    }
}


int main() {
    
    Node* sent = new Node;
    sent->left = sent;
    sent->right = sent;

    cout << "Введите длину списка: ";
    int length = 0;
    cin >> length;
    FillList(sent, length);

    if (IsListSortedByFirstDigit(sent) || IsListSortedByLastDigit(sent)) {
        DelAllOneToFiveNumbers(sent);
        DublicateAllNumbersWithSixOrEight(sent);
    }
    else {
        SortList(sent);
    }

    PrintList(sent);
    ClearList(sent);
    
    delete sent;
    return 0;
}