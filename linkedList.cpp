#include <iostream>
#include <vector>
using namespace std;

template<class T>
class linkedList{
private:
    struct node{
        T data;
        node* next;
    };
    node* head;
    node* tail;
    int count;
public:
    linkedList();
    ~linkedList();
    void insert(T data);
    bool search(T data);
    void remove(T data);
    void print();
};
template<class T>
linkedList<T>::linkedList(){
    head = NULL;
    tail = NULL;
    count = 0;
}
template<class T>
linkedList<T>::~linkedList(){
    node* temp = head;
    while(temp != NULL){
        node* temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
}
template<class T>
void linkedList<T>::insert(T data){
    node* temp = new node;
    temp->data = data;
    temp->next = NULL;
    if(head == NULL){
        head = temp;
        tail = temp;
    }
    else{
        tail->next = temp;
        tail = temp;
    }
    count++;
}
template<class T>
bool linkedList<T>::search(T data){
    node* temp = head;
    while(temp != NULL){
        if(temp->data == data){
            return true;
        }
        temp = temp->next;
    }
    return false;
}
template<class T>
void linkedList<T>::remove(T data){
    node* temp = head;
    node* prev = NULL;
    while(temp != NULL){
        if(temp->data == data){
            if(prev == NULL){
                head = temp->next;
            }
            else{
                prev->next = temp->next;
            }
            delete temp;
            count--;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}
template<class T>
void linkedList<T>::print(){
    node* temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main(){
    linkedList<int> l;
    l.insert(1);
    l.insert(2);
    l.insert(3);
    l.insert(4);
    l.insert(5);
    l.print();
    l.remove(3);
    l.print();
    return 0;
}