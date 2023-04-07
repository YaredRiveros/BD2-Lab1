#include <iostream>
#include "matricula.h"
#include <vector>
#include <fstream>

using namespace std;


class FixedRecord{
private:
    string fileName;
    string headerName = "header.bin";
public:
    FixedRecord(string fileName){
        this->fileName = fileName;
    }

    void add(Matricula m){
        fstream file(fileName,ios::out | ios::binary | ios::app);
        //1. Anoto su posición al final del header
        ofstream header(headerName, ios::out | ios::binary | ios::app);
        int pos = file.tellp();
        header.write((char*)&pos, sizeof(pos));
        header.close();
        //2. Escribo la matricula al final del archivo

        //Escribo los atributos
        ///Codigo
        int lenCodigo = m.codigo.length();
        file.write((char*) &lenCodigo, sizeof(lenCodigo));
        file.write(m.codigo.c_str(), lenCodigo);
        ///Ciclo
        file.write((char*) &m.ciclo, sizeof(m.ciclo));
        ///Mensualidad
        file.write((char*) &m.mensualidad, sizeof(m.mensualidad));
        ///Observaciones
        int lenObservaciones = m.observaciones.length();
        file.write((char*) &lenObservaciones, sizeof(lenObservaciones));
        file.write(m.observaciones.c_str(), lenObservaciones);
        file.close();
    }

    vector<Matricula> load(){
        vector<Matricula> matriculas;
        ifstream file(fileName, ios::in | ios::binary);
        //Me aseguro que no estoy en el final
        file.seekg(0, ios::end);
        int fin = file.tellg();
        file.seekg(0, ios::beg);
        while(file.tellg() < fin){ //Si no he llegado al final del archivo
            Matricula m;
            //Leo los atributos
            ///Codigo
            int lenCodigo;
            file.read((char*) &lenCodigo, sizeof(lenCodigo));
            char* codigo = new char[lenCodigo];
            file.read(codigo, lenCodigo);
            codigo[lenCodigo] = '\0';
            m.codigo = codigo;
            ///Ciclo
            file.read((char*) &m.ciclo, sizeof(m.ciclo));
            ///Mensualidad
            float value;
            char buffer[sizeof(float)];
            file.read((char*) buffer, sizeof(float));
            value = *(float*) buffer;
            m.mensualidad = value;
            ///Observaciones
            int lenObservaciones;
            file.read((char*) &lenObservaciones, sizeof(lenObservaciones));
            char* observaciones = new char[lenObservaciones];
            file.read(observaciones, lenObservaciones);
            observaciones[lenObservaciones] = '\0';
            m.observaciones = observaciones;
            //Agrego la matricula al vector
            matriculas.push_back(m);
        }
        file.close();
        return matriculas;
    }

    Matricula readRecord(int pos){
        //1. Abro el header
        ifstream file(headerName, ios::in | ios::binary);
        //2. Me muevo a la posición pos
        file.seekg(pos * sizeof(int),ios::beg); //pos * sizeof(int) porque cada posición del header es un int
        //3. Leo la posición del registro
        int posRegistro;
        file.read((char*) &posRegistro, sizeof(posRegistro));
        // //4. Cierro el header
        file.close();
        //5. Abro el archivo
        ifstream file2(fileName, ios::in | ios::binary);
        //6. Me muevo a la posición del registro
        file2.seekg(posRegistro, ios::beg);
        //7. Leo el registro
        Matricula m;
        // Leo los atributos
        /// Codigo
        int lenCodigo;
        file2.read((char *)&lenCodigo, sizeof(lenCodigo));
        char *codigo = new char[lenCodigo];
        file2.read(codigo, lenCodigo);
        codigo[lenCodigo] = '\0';
        m.codigo = codigo;
        /// Ciclo
        file2.read((char *)&m.ciclo, sizeof(m.ciclo));
        /// Mensualidad
        float value;
        char buffer[sizeof(float)];
        file2.read((char *)buffer, sizeof(float));
        value = *(float *)buffer;
        m.mensualidad = value;
        /// Observaciones
        int lenObservaciones;
        file2.read((char *)&lenObservaciones, sizeof(lenObservaciones));
        char *observaciones = new char[lenObservaciones];
        file2.read(observaciones, lenObservaciones);
        observaciones[lenObservaciones] = '\0';
        m.observaciones = observaciones;
        //8. Cierro el archivo
        file2.close();

        return m;
    }
};