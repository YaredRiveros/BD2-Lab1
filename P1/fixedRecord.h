#include <iostream>
#include "alumno.h"
#include <vector>
#include <fstream>

using namespace std;

//sobrecarga para leer y escribir registros en archivo de texto (no binario)
istream &operator>>(istream &stream, Alumno &record)
{
    std::getline(stream, record.codigo, ' ');
    std::getline(stream, record.nombre, ' ');
    std::getline(stream, record.apellidos, ' ');
    std::getline(stream, record.carrera,'\n'); 
    return stream;
}

ostream &operator<<(ostream &stream, Alumno &record)
{
    stream << record.codigo;
    int espaciado = 5-record.codigo.length();
    for(int i=0;i<espaciado;i++){
        stream<<" ";
    }
    stream << record.nombre;
    espaciado = 11-record.nombre.length();
    for(int i=0;i<espaciado;i++){
        stream<<" ";
    }
    stream << record.apellidos;
    espaciado = 20-record.apellidos.length();
    for(int i=0;i<espaciado;i++){
        stream<<" ";
    }
    stream << record.carrera << endl;
    return stream;
}

class FixedRecord
{
private:
    string nombreArchivo;

public:
    FixedRecord(string nombreArchivo)
    {
        this->nombreArchivo = nombreArchivo;
    }
    ~FixedRecord()
    {
        // cout<<"Destructor de FixedRecord"<<endl;
    }
    vector<Alumno> load()
    {
        vector<Alumno> alumnos;
        ifstream file(nombreArchivo.c_str());
        if (file.is_open())
        {
            cout << "Archivo abierto" << endl;
            Alumno record;
            while (file >> record)
            {
                alumnos.push_back(record);
            }
            file.close();
        }
        return alumnos;
    }
    void add(Alumno record)
    {
        ofstream file(nombreArchivo.c_str(), ios::app | ios::binary);
        if (file.is_open())
        {
            file << record;
            file.close();
        }
    }

    Alumno readRecord(int pos)
    {
        Alumno record;
        ifstream file(nombreArchivo.c_str());
        if (file.is_open())
        {
            int i=0;
            if(pos==0)
                file >> record;
            else if(pos>0){
                while (file >> record){
                    if(i==pos){
                        break;
                    }
                    i++;
                }
            }
            file.close();
        }
        return record;
    }
};
