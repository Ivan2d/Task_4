#include <iostream>
#include "list"

using namespace std;

class HashTable 
{
    class Entry {
    public:
        int key;
        int value;

        Entry(int key, int value) 
        {
            this->key = key;
            this->value = value;
        }
    };
    class Iterator 
    {
    public:
        explicit Iterator(HashTable& ptr) : tableSize(ptr.tableSize), ptr((ptr.pEntry)), id(0) {};
        Iterator(HashTable& ptr, int id) : tableSize(ptr.tableSize), ptr((ptr.pEntry)), id(id) {};
        Iterator& operator++();
        int operator*();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const { return !(other == *this); };
        Iterator& operator=(const Iterator& copy);
    private:
        const unsigned int tableSize;
        unsigned id;
        Entry** ptr;
    };
    Entry** pEntry;
    const unsigned int tableSize;
public:
    HashTable();
    HashTable(unsigned int tableSize);
    int hashFunction(int k) const;
    void add(int k, int v);
    void remove(int k);
    int searchKey(int k);
    void clear();
    bool isEmpty();
    Iterator begin();
    Iterator end();
};

HashTable::HashTable() : tableSize(10) {
    pEntry = new Entry * [tableSize];
    clear();
}

HashTable::HashTable(unsigned int tableSize) : tableSize(tableSize) {
    pEntry = new Entry * [tableSize];
    clear();
}

int HashTable::hashFunction(int k) const {
    return k % tableSize;
}

void HashTable::add(int k, int v) {
    int h = hashFunction(k);
    while (pEntry[h] != nullptr && pEntry[h]->key != k) {
        h = hashFunction(h + 1);
    }
    if (pEntry[h] != nullptr) {
        delete pEntry[h];
        pEntry[h] = nullptr;
    }
    pEntry[h] = new Entry(k, v);
}

void HashTable::remove(int k) {
    int h = hashFunction(k);
    while (pEntry[h] != nullptr) {
        if (pEntry[h]->key == k)
            break;
        h = hashFunction(h + 1);
    }
    if (pEntry[h] == nullptr) {
        return;
    }
    else {
        delete pEntry[h];
    }
}

int HashTable::searchKey(int k) {
    int h = hashFunction(k);
    while (pEntry[h] != nullptr && pEntry[h]->key != k) {
        h = hashFunction(h + 1);
    }
    if (pEntry[h] == nullptr)
        return -1;
    else
        return pEntry[h]->value;
}

void HashTable::clear() {
    for (int i = 0; i < tableSize; i++) {
        pEntry[i] = nullptr;
    }
}

bool HashTable::isEmpty() {
    for (int i = 0; i < tableSize; i++) {
        if (pEntry[i] != nullptr) {
            return false;
        }
    }
    return true;
}

HashTable::Iterator& HashTable::Iterator::operator++() {
    id++;
    if (ptr[id] == nullptr) {
        while (ptr[id] == nullptr && id < tableSize - 1) {
            id++;
        }
    }
    return *this;
}

HashTable::Iterator HashTable::begin() {
    return Iterator(*this);
}

HashTable::Iterator HashTable::end() {
    return Iterator(*this, tableSize - 1);
}

int HashTable::Iterator::operator*() {
    if (ptr[id] != nullptr) {
        return ptr[id]->value;
    }
}

bool HashTable::Iterator::operator==(const HashTable::Iterator& other) const {
    return this->ptr == other.ptr && this->id == other.id;
}

HashTable::Iterator& HashTable::Iterator::operator=(const HashTable::Iterator& copy) {
    if (this != &copy) {
        this->ptr = copy.ptr;
        this->id = copy.id;
    }
    return *this;
}

int main() 
{
    HashTable p;
    p.add(10, 14);
    p.add(88, 66);
    p.add(43, 92);
    p.add(0, 321321);
    p.add(111, 222);

    cout << p.searchKey(111) << endl;
    cout << p.searchKey(0) << endl;

    p.remove(111);
    cout << p.searchKey(111) << endl;

    for (auto it = p.begin(); it != p.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}