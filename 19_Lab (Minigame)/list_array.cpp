#include <iostream>
#include "list_array.hpp"
using namespace std;

/*
struct Node {
    Node* right;
    Node* left;
    short x_coord;
    short y_coord;
    bool data;
};
*/

Node* MakeList() {
    Node* p = new Node;
    p->right = p;
    p->left = p;
    return p;
}

void PushBack(Node* sent, short Xvalue, short Yvalue, bool value) {
    Node* p = new Node;
    p->x_coord = Xvalue;
    p->y_coord = Yvalue;
    p->data = value;
    p->right = sent;
    p->left = sent->left;
    sent->left->right = p;
    sent->left = p;
}


void PrintList(Node* sent) {
    Node* p = sent->right;
    while (p != sent) {
        cout << "X coord: " << p->x_coord << " Y coord: " << p->y_coord << " data value: " << p->data << endl;
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


void InsertElemByIndex(Node* sent, int Xvalue, int Yvalue, bool value, int index) {
    Node* p = sent->right;
    Node* q = new Node;
    q->x_coord = Xvalue;
    q->y_coord = Yvalue;
    q->data = value;
    for (int i = 0; i < index-1; i++) {
        p = p->right;
    }
    q->left = p;
    q->right = p->right;
    p->right->left = q;
    p->right = q;
}


#if 0
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
#endif