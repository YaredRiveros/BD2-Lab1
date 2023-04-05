#include <iostream>
#include "variableRecord.h"

using namespace std;

int main() {
    VariableRecord vr("datos.txt");
    vector<Alumno> alumnos = vr.load();

    for (size_t i = 0; i < alumnos.size(); i++) {
        cout << alumnos[i].Nombre << " "
             << alumnos[i].Apellidos << " "
             << alumnos[i].Carrera << " "
             << alumnos[i].mensualidad << endl;
    }

    Alumno nuevo;
    nuevo.Nombre = "Rajesh";
    nuevo.Apellidos = "Koothrappali";
    nuevo.Carrera = "Fisica";
    nuevo.mensualidad = 1700.0;

    vr.add(nuevo);

    alumnos = vr.load();

    for (size_t i = 0; i < alumnos.size(); i++) {
        cout << alumnos[i].Nombre << " "
             << alumnos[i].Apellidos << " "
             << alumnos[i].Carrera << " "
             << alumnos[i].mensualidad << endl;
    }

    int pos = 4;
    Alumno registro = vr.readRecord(pos);

    cout << "Registro en la posición " << pos << ": "
         << registro.Nombre << " "
         << registro.Apellidos << " "
         << registro.Carrera << " "
         << registro.mensualidad << endl;

    return 0;
}
