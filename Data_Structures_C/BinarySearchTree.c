#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left, *right;
};

struct Node *MakeRoot(int value) {
  struct Node *root = malloc(sizeof(struct Node));
  root->left = NULL;
  root->right = NULL;
  root->data = value;
}

void InsertNode(struct Node *Node, int value) {
  if (value < Node->data) {
    if (Node->left != NULL) {
      return InsertNode(Node->left, value);
    }
    else {
      struct Node *p = malloc(sizeof(struct Node));
      p->data = value;
      p->left = NULL;
      p->right = NULL;
      Node->left = p;
    }
  }
  else {
    if (Node->right != NULL) {
      return InsertNode(Node->right, value);
    }
    else {
      struct Node *p = malloc(sizeof(struct Node));
      p->data = value;
      p->left = NULL;
      p->right = NULL;
      Node->right = p;
    }
  }
}

struct Node *Search(struct Node *Node, int value) {
  if (Node == NULL) return NULL;
  if (Node->data == value) return Node;
  return (value < Node->data) ? Search(Node->left, value) : Search(Node->right, value);
}

struct Node *GetMin(struct Node *Node) {
  if (Node == NULL) return NULL;
  if (Node->left == NULL) return Node;
  return GetMin(Node->left);
}

struct Node *GetMax(struct Node *Node) {
  if (Node == NULL) return NULL;
  if (Node->right == NULL) return Node;
  return GetMin(Node->right);
}

struct Node *Delete(struct Node *Node, int value) {
  if (Node == NULL) return NULL;
  else if (value < Node->data) Node->left = Delete(Node->left, value);
  else if (value > Node->data) Node->right = Delete(Node->right, value);
  else {
    if (Node->right == NULL || Node->left == NULL) 
      Node = (Node->left == NULL) ? Node->right : Node->left;
    else {
      struct Node *MaxInLeft = GetMax(Node);
      Node->data = MaxInLeft->data;
      Node->left = Delete(Node->left, MaxInLeft->data);
    }
  }
  return Node;
}

void PrintTree(struct Node *Node) {
  if (Node == NULL) return;
  PrintTree(Node->left);
  printf("%d ", Node->data);
  PrintTree(Node->right);
}

void InversePrintTree(struct Node *Node) {
  if (Node == NULL) return;
  InversePrintTree(Node->right);
  printf("%d ", Node->data);
  InversePrintTree(Node->left);
}

void DeleteTree(struct Node *Node) {
  if (Node == NULL) return;
  DeleteTree(Node->right);
  DeleteTree(Node->left);
  free(Node);
}

void CopyTree(struct Node *Node) { // Выводит элементы дерева в том порядке, в котором были изначально добавлены
  if (Node == NULL) return;
  printf("%d ", Node->data);
  CopyTree(Node->left);
  CopyTree(Node->right);
}

int main() {
  struct Node *root = MakeRoot(7);
  InsertNode(root, 4);
  InsertNode(root, 9);
  InsertNode(root, 8);
  InsertNode(root, 10);
  InsertNode(root, 11);
  PrintTree(root);
  printf("\n");
  InversePrintTree(root);
  printf("\n");
  CopyTree(root);
  DeleteTree(root);
  return 0;
}