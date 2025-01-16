#include <iostream>
using namespace std;


struct Node
{   
    Node* next;
    int data;
};


void makeList(Node* head, int n) 
{
    Node* p = head;
    for (int i = 0; i < n; i++)
    {
        Node* q = new Node;
        p->next = q;

        cout << "Enter a value: ";
        cin >> q->data;
        q->next = nullptr;

        p = p->next;
    }
}


void printList(Node* head) 
{
    Node* p = head;
    while (p->next != nullptr)
    {
        cout << p->next->data << " ";
        p = p->next;
    }
    cout << endl;
}


void clearList(Node* head) 
{
    Node* p = head;
    while (p->next != nullptr)
    {
        Node* tmp = p->next;
        p->next = p->next->next;
        delete tmp;
    }
    delete p;
}


bool containsIdenticalDigits(int n) 
{
    n = abs(n);

    for (int i = 0; i < 10; i++)
    {
        int counter = 0;
        int number = n;
        while (number != 0)
        {
            if (number % 10 == i)
            {
                counter++;
            }
            number /= 10;
        }
        if (counter > 1) return true;
    }

    return false;
}


bool doesListContainsNumberWithIdenticalDigits(Node* head) 
{
    Node* p = head;
    while (p->next != nullptr)
    {
        if (containsIdenticalDigits(p->next->data))
        {
            return true;
        }
        p = p->next;
    }
    return false;
}


int getLastDigit(int n) 
{
    return abs(n) % 10;
}


int getFirstDigit(int n) 
{
    while (n > 9)
    {
        n /= 10;
    }
    return n;
}


void removeElemFromList(Node* head, Node* elem) 
{
    Node* p = head;
    while (p->next != nullptr)
    {
        if (p->next == elem)
        {
            Node* tmp = p->next;
            p->next = p->next->next;
            delete tmp;
            return;
        }
        p = p->next;
    }
}


void copyElemFromList(Node* head, Node* elem) 
{
    Node* p = head;
    while (p->next != nullptr)
    {
        if (p->next == elem)
        {
            Node* q = new Node;
            q->data = p->next->data;
            q->next = p->next->next;
            p->next->next = q;  
            return;
        }
        p = p->next;
    }
}


/* Ввести последовательность натуральных чисел. Если в последовательности нет ни одного числа, содержащего две одинаковых цифры, 
 упорядочить последовательность по невозрастанию последней цифры числа. В противном случае удалить из последовательности числа, 
 начинающиеся четной цифрой и продублировать остальные числа. Последовательность хранить в односвязном списке.*/


int main() 
{
    Node* head = new Node{nullptr, 0};
    int n;
    cout << "Введите длину списка: ";
    cin >> n;
    makeList(head,  n);
    
    if (!doesListContainsNumberWithIdenticalDigits(head))
    {
        Node* p = head->next;
        for (Node * a = p; a->next != nullptr; a = a->next)
            for (Node * b = a->next; ; b = b->next)
            {
                if (getLastDigit(a->data) < getLastDigit(b->data)) swap(a->data, b->data);
                if (b->next == nullptr) break;
            }
    }
    else
    {
        Node* p = head;
        while (p->next != nullptr)
        {
            if ((getFirstDigit(p->next->data)) % 2 == 0)
            {
                removeElemFromList(head, p->next);
            }
            else
            {
                p = p->next;
            } 
        }
        p = head;
        while (p->next != nullptr)
        {
            copyElemFromList(head, p->next);
            p = p->next->next;
        }
    }
    
    printList(head);
    clearList(head);
    return 0;
}