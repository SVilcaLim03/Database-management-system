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
    list<string> columns;
    template <typename U>
    friend class Database;
public:
    Table(){}
};

template <typename T>
class Database
{
private:
    string key;
    list< Table<T> > tables;
    template <typename U>
    friend class Hash;

public:
    Database()
    {
        key = "";
    }
    Database(string k)
    {
        key = k;
    }
    void insertTable(string name)
    {
        tables.push_back(Table<T>(name));
        fstream nueva_bd;
        nueva_bd.open("Tablas/"+name+".txt",ios::out);
    }
    void deleteTable(string name){
        tables.remove(name.c_str());
        string eliminado="Tablas/"+name+".txt";
        remove(eliminado.c_str());
    }
};

template <typename T>
class Hash
{
private:
    int tam;
    list< Database<T> > *tabla;
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
        tabla = new list< Database<T> >[tam];
    }
    int hash(string k)
    {
        return fd(k, tam);
    }
    void insert(string k)
    {
        int indice = fd(k, tam);
        tabla[indice].push_back(Database<T>(k));
        fstream nueva_bd;
        nueva_bd.open("Tablas/"+k+".txt",ios::out);

    }
    void remove(string k)
    {
        int indice = fd(k, tam);
        list< Database<int> >::iterator it;
        for (it = tabla[indice].begin(); it != tabla[indice].end(); ++it)
        {
            if((*it).key==k){
                tabla[indice].erase(it);
                break;
            }
        }
    }

    void print()
    {
        list< Database<int> >::iterator it;
        for (int i = 0; i < tam; i++)
        {
            for (it = tabla[i].begin(); it != tabla[i].end(); ++it)
            {
                if((*it).key!=""){
                    cout << (*it).key << "    ";
                }
            }
        }
    }
};
int main()
{
    Hash<int> h(10);
    h.insert("mi base de datos");

    h.print();
    cout << endl
         << endl;
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