#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "alumno.h"

using namespace std;

class VariableRecord {
private:
    string nombreArchivo;

public:
    // constructor
    VariableRecord(string nombreArchivo) {
        this->nombreArchivo = nombreArchivo;
    }

    vector<Alumno> load() {
        vector<Alumno> alumnos;
        ifstream file(nombreArchivo);

        if (file.is_open()) {
            string line;
            // Ignorar la primera línea (nombres de campo)
            getline(file, line);
            // Leer cada registro en el archivo
            while (getline(file, line)) {
                stringstream ss(line);
                Alumno alumno;
                string temp;

                getline(ss, alumno.Nombre, '|');
                getline(ss, alumno.Apellidos, '|');
                getline(ss, alumno.Carrera, '|');
                // Leer y convertir el valor de mensualidad a float
                getline(ss, temp, '|');
                alumno.mensualidad = stof(temp);

                alumnos.push_back(alumno);
            }
            file.close();
        }
        return alumnos;
    }

    void add(Alumno record) {
        ofstream file(nombreArchivo, ios::app);

        if (file.is_open()) {
            file << record.Nombre << "|"
                 << record.Apellidos << "|"
                 << record.Carrera << "|"
                 << record.mensualidad << endl;

            file.close();
        }
    }

    Alumno readRecord(int pos) {
        Alumno record;
        vector<Alumno> alumnos = load();
        // Verificar si la posición está dentro de los límites del vector
        if (pos >= 0 && pos < alumnos.size()) {
            record = alumnos[pos];
        }
        else{
            cout << "La posición está fuera de rango" << endl;
        }
        return record;
    }
};
