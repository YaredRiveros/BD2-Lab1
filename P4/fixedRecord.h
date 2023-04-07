#include <iostream>
#include "matricula.h"
#include <vector>
#include <fstream>

using namespace std;


void writeToFile(const char** arr, int size, const char* fileName){
    ofstream file(fileName, ios::out | ios::binary);
    file.write((char*) &size, sizeof(size));
    file.write((char*) arr, sizeof(char*) * size); //escribo paquete de atributos de texto
    file.close();
}

void readFromFile(char**& arr, int& size, const char* fileName){
    ifstream file(fileName, ios::in | ios::binary);
    file.read((char*) &size, sizeof(size));
    arr = new char*[size];
    file.read((char*) arr, sizeof(char*) * size);
    file.close();
}


class FixedRecord{
private:
    string fileName;
    string headerName = "header.bin";
public:
    FixedRecord(string fileName){
        this->fileName = fileName;
    }

    void add(Matricula m){
        ofstream file(fileName, ios::out | ios::binary | ios::app);
        //1. Anoto su posición al final del header
        ofstream header(headerName, ios::out | ios::binary | ios::app);
        size_t pos = file.tellp();
        header.write((char*)&pos, sizeof(header.tellp()));
        header.close();
        //2. Escribo la matricula al final del archivo
        const char** arr = m.empaquetar(); //obtengo el array de atributos de texto

        //Escribo el paquete de atributos de texto
        // writeToFile(arr, m.getSize(), fileName.c_str());
        int size = m.getSize();
        file.write((char*) &size, sizeof(size));
        file.write((char*) arr, sizeof(char*) * size); //escribo paquete de atributos de texto
        //Escribo los atributos de tipo numérico
        file.write((char*) &m.ciclo, sizeof(m.ciclo));
        file.write((char*) &m.mensualidad, sizeof(m.mensualidad));
        file.close();
    }

    vector<Matricula> load(){
        vector<Matricula> matriculas;
        ifstream file(fileName, ios::in | ios::binary);
        //Me aseguro que no esté vacío
        // file.seekg(sizeof(int), ios::beg);
        file.seekg(0, ios::beg);
        int i = 1;
        while(i>0){ //Si el archivo no está vacío
            cout << "no vacio" << endl;
            // file.seekg(0, ios::beg); //Ya que comprobé que no está vacío, me muevo al inicio
            char** newArr;
            int newSize;
            Matricula m;
            //Leo el paquete de atributos de texto
            // readFromFile(newArr, newSize, fileName.c_str());
            file.read((char*) &newSize, sizeof(newSize));
            newArr = new char*[newSize];
            file.read((char*) newArr, sizeof(char*) * newSize);
            m.desempaquetar(newArr, newSize);
            //Leo los atributos de tipo numérico
            file.read((char*) &m.ciclo, sizeof(m.ciclo));
            float value;
            char buffer[sizeof(float)];
            file.read((char*) buffer, sizeof(float));
            value = *(float*) buffer;
            m.mensualidad = value;
            matriculas.push_back(m);
            i--;
        }
        file.close();
        return matriculas;
    }

    Matricula readRecord(int pos){
        //1. Abro el header
        ifstream file(headerName, ios::in | ios::binary);
        //2. Me muevo a la posición pos
        file.seekg(pos * sizeof(file.tellg())); //sizeof(file.tellg()) es el tamaño de toda posición escrita en el header
        //3. Leo la posición del registro
        char **newArr;
        int newSize;
        Matricula m;
        readFromFile(newArr, newSize, fileName.c_str());
        m.desempaquetar(newArr, newSize);
        //4. Cierro el header
        file.close();

        return m;
    }
};