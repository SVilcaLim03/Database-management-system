#include <iostream>
#include <math.h>
#include <list>
#include <fstream>
#include "adaptarSistemasOp.h"

using namespace std;

void menu();
bool ConsultaPrimo(int num);
int sigPrimo(int val);
int fd(string key, int n);

template<typename T>
class Table{
private:
    string name;
    list<string> *colums;
    template <typename U>
    friend class Database;
public:
    Table(){
        name="";
        colums=new list<string>[1];
    }
    Table(string t){
        name=t;
        colums=new list<string>[1];
    }
    void insert(string columna){
        colums->push_back(columna);
    }

    void insertData(string bd,string tabla){
        fstream archivo;
        archivo.open("BasesDeDatos/"+bd+"/"+tabla+".txt",ios::app);
        archivo<<endl;
        for (list<string>::iterator it = colums->begin(); it != colums->end(); ++it)
        {
            string data;
            cout<<(*it)<<": ";
            getline(cin,data);
            archivo<<data<<"\t\t";
        }
        archivo.close();
    }

    void deleteData(string bd,string tabla){
        fstream archivo,aux;
        archivo.open("BasesDeDatos/"+bd+"/"+tabla+".txt",ios::in);
        aux.open("BasesDeDatos/"+bd+"/aux"+".txt",ios::out);

        string _column,_condition,_lectura;
        cout<<"Columna ";
        getline(cin,_column);
        cout<<"Dato ";
        getline(cin,_condition);

        int eliminar,cont=1;
        for (list<string>::iterator it = colums->begin(); it != colums->end(); ++it)
        {
            archivo>>_lectura;
            aux<<_lectura<<"\t\t";
            if(_lectura==_column)
                eliminar=cont;
            cont++;
        }
        while(!archivo.eof()){
            string _ingreso="";
            bool _find=false;
            for(int i=0;i<eliminar;i++){
                archivo>>_lectura;
                if(i==eliminar-1 && _lectura==_condition){
                    _find=true;
                    _ingreso+=_lectura;
                }
                else if(i==eliminar-1){
                    _ingreso+=_lectura;
                }
                else{
                    _ingreso+=_lectura+"\t\t";
                }
            }

            getline(archivo,_lectura);
            if(_find!=true){
                aux<<endl<<_ingreso;
                aux<<_lectura;
            }       
        }

        archivo.close();
        aux.close();

        string _remove="BasesDeDatos/"+bd+"/"+tabla+".txt";
        string _rename="BasesDeDatos/"+bd+"/aux"+".txt";
        remove(_remove.c_str());                    
        rename(_rename.c_str(), _remove.c_str());
    }

    void updateData(string bd,string tabla){
        fstream archivo,aux;
        archivo.open("BasesDeDatos/"+bd+"/"+tabla+".txt",ios::in);
        aux.open("BasesDeDatos/"+bd+"/aux"+".txt",ios::out);

        string _column,_condition,_nuevo,_lectura;
        cout<<"Columna ";
        getline(cin,_column);
        cout<<"Dato a reemplazar ";
        getline(cin,_condition);
        cout<<"Dato nuevo ";
        getline(cin,_nuevo);

        int eliminar,cont=1;
        for (list<string>::iterator it = colums->begin(); it != colums->end(); ++it)
        {
            archivo>>_lectura;
            aux<<_lectura<<"\t\t";
            if(_lectura==_column)
                eliminar=cont;
            cont++;
        }
        while(!archivo.eof()){
            string _ingreso="";
            bool _find=false;
            for(int i=0;i<eliminar;i++){
                archivo>>_lectura;
                if(i==eliminar-1 && _lectura==_condition){
                    _find=true;
                    _ingreso+=_nuevo;
                }
                else if(i==eliminar-1){
                    _ingreso+=_lectura;
                }
                else{
                    _ingreso+=_lectura+"\t\t";
                }
            }
            getline(archivo,_lectura);
            aux<<endl<<_ingreso;
            aux<<_lectura;   
        }
        archivo.close();
        aux.close();

        string _remove="BasesDeDatos/"+bd+"/"+tabla+".txt";
        string _rename="BasesDeDatos/"+bd+"/aux"+".txt";
        remove(_remove.c_str());                    
        rename(_rename.c_str(), _remove.c_str());
    }

    void printData(string bd,string tabla){
        fstream archivo,aux;
        archivo.open("BasesDeDatos/"+bd+"/"+tabla+".txt",ios::in);

        string _lectura;
        while(!archivo.eof()){
            getline(archivo,_lectura);
            cout<<_lectura<<endl;
        }
    }
};

template <typename T>
class Database
{
private:
    string key;
    list< Table<T> > *tables;
    
    template <typename U>
    friend class Hash;

public:
    Database()
    {
        key = "";
        tables= new list< Table<T> > [1];
    }
    Database(string k)
    {
        key = k;
        tables= new list< Table<T> > [1];
    }
    void insertTable(string name,string database)
    {
        Table<T>* nueva_tabla= new Table<T>(name);
        tables->push_back(*nueva_tabla);
       
        fstream tabla_txt;
        tabla_txt.open("BasesDeDatos/"+database+"/"+name+".txt",ios::out);

        string nueva_columna;
        cout<<"\tNo ingrese nada para dejar de insertar columnas"<<endl;
        do
        {
            cout<<"\tColumna: ";
            getline(cin,nueva_columna);
            if(nueva_columna != "\0"){
                (*nueva_tabla).insert(nueva_columna);
                tabla_txt<<nueva_columna<<"\t\t";
            }
            else
                break;
        } while (true);
        tabla_txt.close();
    }

    void deleteTable(string _table){
        string borrar="BasesDeDatos/"+key+"/"+_table+".txt";
        remove(borrar.c_str());
    }

    void deleteData(string _bd){
        string _table;
        cout<<"Ingrese la tabla: "<<endl;
        getline(cin,_table);

        typename list<Table <T> >:: iterator it=search(_table);
        if(it!=tables->end() && (*it).name==_table){
            (*it).deleteData(_bd,_table);
        }

    }

    void insertData(string _bd){
        cout<<endl<<"Ingrese la tabla: "<<endl;
        string _table;
        getline(cin,_table);
        typename list<Table <T> >:: iterator it=search(_table);
        if(it!=tables->end() && (*it).name==_table){
            (*it).insertData(_bd,_table);
        }
    }

    void updateData(string _bd){
        cout<<endl<<"Ingrese la tabla: "<<endl;
        string _table;
        getline(cin,_table);
        typename list<Table <T> >:: iterator it=search(_table);
        if(it!=tables->end() && (*it).name==_table){
            (*it).updateData(_bd,_table);
        }
    }

    void printData(string _bd){
        cout<<endl<<"Ingrese la tabla: "<<endl;
        string _table;
        getline(cin,_table);
        typename list<Table <T> >:: iterator it=search(_table);
        if(it!=tables->end() && (*it).name==_table){
            (*it).printData(_bd,_table);
        }
    }

    typename list<Table <T> >:: iterator search(string _table){
        for (typename list<Table <T> >:: iterator it = tables->begin(); it != tables->end(); ++it){
            if((*it).name==_table){
                return it;
            }
        }
        cout<<"No encontrado"<<endl;
        return tables->end();
    }

    void printTables(){
        cout<<endl;
        for (typename list<Table <T> >:: iterator it = tables->begin(); it != tables->end(); ++it){
            cout<<"\t\t"<<(*it).name;
        }
        cout<<endl;
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

    typename list<Database <T> >:: iterator search(string _bd){
        int indice = fd(_bd, tam);
        for (typename list<Database <T> >:: iterator it = tabla[indice].begin(); it != tabla[indice].end(); ++it){
            if((*it).key==_bd){
                return it;
            }
        }
        cout<<"No encontrado"<<endl;
        return tabla[indice].end();
    }

    void insert(string k)
    {
        int indice = fd(k, tam);
        Database<T> * nueva= new Database<T>(k);
        tabla[indice].push_back(*nueva);

        string carpeta="mkdir "+k;
        system(carpeta.c_str());
        string mover = "";
        mover += MOVER;
        mover += " ";
        mover += k+" BasesDeDatos/"+k;
        system(mover.c_str());
        fstream nueva_bd;
        nueva_bd.open("BasesDeDatos/"+k+"/"+k+".txt",ios::out);

        string nueva_tabla;
        cout<<"No ingrese nada para dejar de insertar tablas"<<endl;
        do
        {
            cout<<"Tabla: ";
            getline(cin,nueva_tabla);
            if(nueva_tabla != "\0"){
                (*nueva).insertTable(nueva_tabla,k);
                nueva_bd<<nueva_tabla<<"\t\t";
            }
            else
                break;
        } while (true);
        nueva_bd.close();
    }
    void remove(string bd)
    {
        string borrar="rm -r BasesDeDatos/"+bd;
        system(borrar.c_str());
    }

    void print()
    {
        for (int i = 0; i < tam; i++)
        {
            for (typename list<Database <T> >:: iterator it = tabla[i].begin(); it != tabla[i].end(); ++it)
            {
                if((*it).key!=""){
                    cout << (*it).key << "    ";
                    (*it).printTables();
                }
            }
        }
    }

    void printData(){
        cout<<endl<<"Ingrese la base de datos: "<<endl;
        string bd;
        getline(cin,bd);
        typename list<Database <T> >:: iterator it=search(bd);
        if((*it).key==bd){
            (*it).printData(bd);
        }
    }

    void insertData(){
        cout<<endl<<"Ingrese la base de datos: "<<endl;
        string bd;
        getline(cin,bd);
        typename list<Database <T> >:: iterator it=search(bd);
        if((*it).key==bd){
            (*it).insertData(bd);
        }
    }

    void deleteData(){
        cout<<endl<<"Ingrese la base de datos: "<<endl;
        string bd;
        getline(cin,bd);
        typename list<Database <T> >:: iterator it=search(bd);
        if((*it).key==bd){
            (*it).deleteData(bd);
        }
    }

    void updateData(){
        cout<<endl<<"Ingrese la base de datos: "<<endl;
        string bd;
        getline(cin,bd);
        typename list<Database <T> >:: iterator it=search(bd);
        if((*it).key==bd){
            (*it).updateData(bd);
        }
    }
};

int main()
{
    menu();
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

void menu(){
    Hash<string> h(17);
    int opcion;
    string bd;
    do
    {
        cout<<"¿Que accion desea realizar?"<<endl;
        cout<<"1 Crear"<<endl;
        cout<<"2 Insertar"<<endl;
        cout<<"3 Mostrar"<<endl;
        cout<<"4 Eliminar"<<endl;
        cout<<"5 Actualizar"<<endl;
        cout<<"6 Ninguna"<<endl;
        cin>>opcion;
        system(LIMPIAR);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            cout<<"Nombre de la BD: ";
            getline(cin,bd);
            h.insert(bd);
            break;
        case 2:
            h.insertData();
            break;
        case 3:
            h.printData();
            cout<<"Pulse una tecla para continuar"<<endl;
            cin.get();
            break;
        case 4:
            // cout<<"Nombre de la BD: ";
            // getline(cin,bd);
            // h.remove(bd);
            h.deleteData();
            break;
        case 5:
            h.updateData();
            break;
        default:
            break;
        }
    } while (opcion!=6);
}
//ordenar, modificar, consultas a una tabla