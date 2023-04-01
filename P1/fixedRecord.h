#include <iostream>
#include "alumno.h"
#include <vector>
#include <fstream>

using namespace std;

istream &operator>>(istream &stream, Alumno &record)
{
    stream.read(record.codigo, sizeof(record.codigo));
    stream.read(record.nombre, sizeof(record.nombre));
    stream.read(record.apellidos, sizeof(record.apellidos));
    stream.read(record.carrera, sizeof(record.carrera));
    stream.get();
    stream.get(); //doble salto de linea para que el atributo del siguiente alumno no tomen el salto de línea

    //Lleno con espacios vacíos aquellos no utilizados según el string más grande de cada atributo
    record.codigo[4] = '\0';
    // cout << "tamanio codigo: " << sizeof(record.codigo) << endl;
    // cout << "codigo: " << record.codigo << endl;
    record.nombre[6] = '\0';
    // cout << "tamanio nombre: " << sizeof(record.nombre) << endl;
    // cout << "nombre: " << record.nombre << endl;
    record.apellidos[16] = '\0';
    // cout << "tamanio apellidos: " << sizeof(record.apellidos) << endl;
    // cout << "apellidos: " << record.apellidos << endl;
    record.carrera[12] = '\0';
    // cout << "tamanio carrera: " << sizeof(record.carrera) << endl;
    // cout << "carrera: " << record.carrera << endl;
    return stream;
}

ostream &operator<<(ostream &stream, Alumno &record)
{
    stream.write(record.codigo, sizeof(record.codigo));
    stream.write(record.nombre, sizeof(record.nombre));
    stream.write(record.apellidos, sizeof(record.apellidos));
    stream.write(record.carrera, sizeof(record.carrera));
    stream << "\n";
    stream << flush;
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
        ofstream file(nombreArchivo.c_str(), ios::app);
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
            file.seekg(pos * (sizeof(record)+1), ios::beg);
            file >> record;
            file.close();
        }
        return record;
    }
};
