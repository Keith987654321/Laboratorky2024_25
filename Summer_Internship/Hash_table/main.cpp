#include <iostream>
#include "hash_table.hpp"

int main() {
    using namespace std;

    HashTable MyTable = HashTable<int, string>();

    MyTable.add(0, "a");
    MyTable.add(1, "ab");
    MyTable.add(2, "abc");
    MyTable.add(3, "abcd");
    
    for (int i = 0; i < MyTable.length(); ++i) {
        cout << "key = " << i << ", value = " << MyTable.get(i) << endl;
    }
    cout << endl;

    string str = MyTable.popItem(3);
    MyTable.add(3, "ABCD");
    MyTable.add(1, "AB");
    HashTable tableCopy = MyTable;
    tableCopy.add(4, "New line");

    for (int i = 0; i < tableCopy.length(); ++i) {
        cout << "key = " << i << ", value = " << tableCopy.get(i) << endl;
    }
    cout << "str = " << str << endl << endl;
    MyTable.clear();
    tableCopy.clear();

    HashTable thirdTable = HashTable<string, bool>();

    thirdTable.add("Earth is round", true);
    thirdTable.add("Dota 2 players have 2 dads", true);
    thirdTable.add("Half-Life 3 will be released next year", false);
    thirdTable.add("Women have rights", false);
    
    string value;
    string* keys = thirdTable.keys();
    bool* values = thirdTable.values();

    for (int i = 0; i < thirdTable.length(); ++i) {
        if (values[i]) value = "True";
        else value = "False";
        cout << keys[i] << " - " << value << endl;
    }

    return 0;
}