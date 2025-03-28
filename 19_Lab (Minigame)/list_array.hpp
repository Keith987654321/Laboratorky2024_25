#pragma once

#define FIELD_SIZE 10

struct Node {
    Node* right;
    Node* left;
    short x_coord;
    short y_coord;
    bool data;
};

Node* MakeList();
void PushBack(Node* sent, short Xvalue, short Yvalue, bool value = 0);
void PrintList(Node* sent);
void ClearList(Node* sent);
Node* GetElemByIndex(Node* sent, int index);
void DeleteElemByIndex(Node* sent, int index);
void InsertElemByIndex(Node* sent, int Xvalue, int Yvalue, bool value, int index);
