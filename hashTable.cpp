//DEPENDENCIAS
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class HashTable{
private:
    vector<T>* table;
    int size;
    int count;
    int hash(T key);
public:
    HashTable(int size);
    ~HashTable();
    void insert(T key);
    bool search(T key);
    void remove(T key);
    void print();
};
template<class T>
HashTable<T>::HashTable(int size){
    this->size = size;
    this->count = 0;
    table = new vector<T>[size];
}
template<class T>
HashTable<T>::~HashTable(){
    delete[] table;
}
template<class T>
int HashTable<T>::hash(T key){
    return key % size;
}
template<class T>
void HashTable<T>::insert(T key){
    int index = hash(key);
    table[index].push_back(key);
    count++;
}
template<class T>
bool HashTable<T>::search(T key){
    int index = hash(key);
    for(int i = 0; i < table[index].size(); i++){
        if(table[index][i] == key){
            return true;
        }
    }
    return false;
}
template<class T>
void HashTable<T>::remove(T key){
    int index = hash(key);
    for(int i = 0; i < table[index].size(); i++){
        if(table[index][i] == key){
            table[index].erase(table[index].begin() + i);
            count--;
            return;
        }
    }
}
template<class T>
void HashTable<T>::print(){
    for(int i = 0; i < size; i++){
        cout << i << ": ";
        for(int j = 0; j < table[i].size(); j++){
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){
    
    HashTable<int>* hashTable = new HashTable<int>(10);
    hashTable->insert(1);
    hashTable->insert(2);
    hashTable->insert(3);
    hashTable->insert(4);
    hashTable->print();
    
    return 0;
}
