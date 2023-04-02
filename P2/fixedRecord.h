#include <iostream>
#include <fstream>
#include "alumno.h"
#include <vector>

using namespace std;

// Sobrecarga de lectura de un alumno
istream &operator>>(istream &stream, Alumno &a)
{
    // Guardo el registro en a
    stream.read((char *)&a, sizeof(a));
    // Me muevo al siguiente registro
    stream.seekg(sizeof(a));
    return stream;
}

ostream &operator<<(ostream &stream, Alumno &p)
{
    stream.write((char *)&p, sizeof(p));
    return stream;
}

class FixedRecord
{
private:
    string fileName;
    fstream file;

public:
    FixedRecord(string fileName)
    {
        this->fileName = fileName;
    }

    vector<Alumno> load()
    {
        //Abro el archivo como binario y de lectura
        file.open(fileName, ios::in | ios::binary);
        vector<Alumno> temps;
        Alumno temp;
        int freeList;

        // Leo el header
        file.read((char *)&freeList, sizeof(freeList));

        //Apunto al primer registro
        int cursor = sizeof(freeList);
        file.seekg(cursor, ios::beg);

        //Leo todos los registros
        while (file >> temp)
        {
            if (temp.nextD == 0)
                temps.push_back(temp);
            cursor += sizeof(temp);
            file.seekg(cursor, ios::beg);
        }
        file.close();
        return temps;
    }

    void add(Alumno record)
    {
        //Abro el archivo como binario, de lectura y escritura
        int freeList;
        file.open(fileName, ios::in | ios::out | ios::binary);
        //Leo el header
        file.read((char *)&freeList, sizeof(freeList));
        record.nextD = 0;
        //Si no hay registros eliminados
        if (freeList == -1)
        {
            //Escribe el nuevo registro al final del archivo
            file.seekg(0, ios::end);
            file.write((char *)&record, sizeof(record));
        }
        //Si hay registros eliminados
        else
        {
            //Me dirijo al registro eliminado
            Alumno tmp;
            int cursor = sizeof(freeList) + (freeList - 1) * sizeof(record);
            file.seekg(cursor, ios::beg);
            //Lo leo
            file.read((char *)&tmp, sizeof(tmp)); //Internamente avanzo al final de ese registro
            //Vuelvo al inicio de ese registro y escribo el nuevo registro
            file.seekg(cursor, ios::beg);
            file.write((char *)&record, sizeof(record));
            //El header ahora apunta al siguiente registro eliminado
            freeList = tmp.nextD;
            file.seekg(0, ios::beg);
            file.write((char *)&freeList, sizeof(freeList));
        }
        file.close();
    }

    Alumno readRecord(int pos)
    {
        //Abro el archivo como binario y de lectura
        file.open(fileName, ios::in | ios::binary);
        Alumno temp;
        int freeList;
        //Me muevo al registro en la posición indicada
        int cursor = sizeof(freeList) + (pos - 1) * sizeof(temp);
        file.seekg(cursor, ios::beg);
        //Leo el registro en la posición indicada
        file.read((char *)&temp, sizeof(temp));
        //Si no está eliminado, entonces se devuelve el registro
        if (temp.nextD == 0)
        {
            file.close();
            return temp;
        }
        //Si está eliminado
        else
        {
            //Se devuelve un registro vacío y un mensaje
            Alumno empty;
            cout << "Registro eliminado\n";
            file.close();
            return empty;
        }
    }

    bool deleteRecord(int pos)
    {
        //Abro el archivo como binario, de lectura y escritura
        int freeList;
        file.open(fileName, ios::in | ios::out | ios::binary);
        //Leo el header
        file.read((char *)&freeList, sizeof(freeList));

        Alumno temp;
        //Me muevo a la posición del registro a eliminar
        file.seekg(((pos - 1) * sizeof(temp)) + sizeof(freeList), ios::beg);
        //Leo el registro
        file.read((char *)&temp, sizeof(temp));
        //Si está eliminado, no se elimina y se devuelve false
        if (temp.nextD != 0)
            return false;
        //Si no está eliminado, se le reemplaza por un registro vacío
        temp.nextD = freeList;
        file.seekg(((pos - 1) * sizeof(temp)) + sizeof(freeList), ios::beg);
        file.write((char *)&temp, sizeof(temp));
        //Se actualiza el header con la pos del registro eliminado
        freeList = pos;
        file.seekg(0, ios::beg);
        file.write((char *)&freeList, sizeof(freeList));
        file.close();
        return true;
    }
};