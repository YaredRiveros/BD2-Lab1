#include <iostream>
#include "variableRecord.h"

using namespace std;

int main() {
    VariableRecord vr("datos.txt");
    vector<Alumno> alumnos = vr.load();

    cout << "\t--Lista de alumnos en el archivo--" << endl;
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

    cout << "\t--Lista de alumnos en el archivo luego de agregar al nuevo alumno (Rajesh Koothrappali)--" << endl;

    for (size_t i = 0; i < alumnos.size(); i++) {
        cout << alumnos[i].Nombre << " "
             << alumnos[i].Apellidos << " "
             << alumnos[i].Carrera << " "
             << alumnos[i].mensualidad << endl;
    }

    cout << endl << "\t--Leer el registro en la posición 4--" << endl;

    int pos = 4;
    Alumno registro = vr.readRecord(pos);

    cout << "Registro en la posición " << pos << ": " << endl; //La posición cuenta desde 0 (0 es la pos del primer registro)

    cout << "Nombre: " << registro.Nombre << endl;
    cout << "Apellidos: " << registro.Apellidos << endl;
    cout << "Carrera: " << registro.Carrera << endl;
    cout << "Mensualidad: " << registro.mensualidad << endl;

    return 0;
}
