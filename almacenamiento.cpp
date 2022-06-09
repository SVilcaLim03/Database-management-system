#include <iostream>
#include <math.h>
#include <list>
#include <fstream>

using namespace std;

bool ConsultaPrimo(int num);
int sigPrimo(int val);
int fd(string key, int n);

template<typename T>
class Table{
private:
    list<string> tables;
    template <typename U>
    friend class Objeto;
public:
    Table(){}
};

template <typename T>
class Objeto
{
private:
    string key;
    T value;
    template <typename U>
    friend class Hash;

public:
    Objeto()
    {
        key = "";
        value = 0;
    }
    Objeto(string k, T val)
    {
        key = k;
        value = val;
    }
};

template <typename T>
class Hash
{
private:
    int tam;
    list< Objeto<T> > *tabla;
    int fd(string key, int n)
    {
        const char *k = key.c_str();
        int s = 0;
        while (*k)
        {
            s = s + int(*k);
            k++;
        }
        return s % n;
    }

public:
    Hash()
    {
        tam = 0;
        tabla = NULL;
    }
    Hash(int t)
    {
        //el tamaño sera el siguiente primo de esta manera hay menos coliciones :D
        tam = sigPrimo(t);
        tabla = new list< Objeto<T> >[tam];
    }
    int hash(string k)
    {
        return fd(k, tam);
    }
    void insert(string k, T val)
    {
        int indice = fd(k, tam);
        tabla[indice].push_back(Objeto<T>(k, val));
        fstream nueva_bd;
        nueva_bd.open("/Users/eltimo/Documents/3ro primer semestre/BD/ProyectoFinal/Tablas/"+k+".txt",ios::out);

    }
    void remove(string k)
    {
        int indice = fd(k, tam);
        list< Objeto<int> >::iterator it;
        for (it = tabla[indice].begin(); it != tabla[indice].end(); ++it)
        {
            if((*it).key==k){
                tabla[indice].erase(it);
                break;
            }
        }
    }
    T search(string k){
        int indice = fd(k, tam);
        list< Objeto<int> >::iterator it;
        for (it = tabla[indice].begin(); it != tabla[indice].end(); ++it)
        {
            if((*it).key==k){
                return (*it).value;
            }
        }
        return -1;
    }

    void print()
    {
        list< Objeto<int> >::iterator it;
        for (int i = 0; i < tam; i++)
        {
            for (it = tabla[i].begin(); it != tabla[i].end(); ++it)
            {
                if((*it).key!=""){
                    cout << (*it).key << "    ";
                    cout << (*it).value << endl;
                }
            }
        }
    }
};
int main()
{
    Hash<int> h(10);
    h.insert("Miriam", 100);
    h.insert("Noemi", 100);
    h.insert("Alvaro", 130);
    h.insert("Joel", 100);
    h.insert("Benjamin", 100);
    h.insert("Alejandro", 100);
    h.insert("Jose", 100);
    h.insert("Daniel", 100);
    h.insert("Fernando", 100);
    h.insert("Alexander", 100);
    h.insert("Donny", 100);
    h.print();
    cout << endl
         << endl;
    cout<<"El valor de la llave ingresada es "<<h.search("Alvaro")<<endl;
    h.remove("Alvaro");
    h.print();
    return 0;
}

int sigPrimo(int val)

{
    for (int i = val;; i++, val++)
    {
        if (ConsultaPrimo(val))
            return val;
    }
}
bool ConsultaPrimo(int num)
{
    if (num % 2 == 0)
        return false;
    else
    {
        for (int y = 3; y <= sqrt(num); y += 2)
            if (num % y == 0)
                return false;
        return true;
    }
}