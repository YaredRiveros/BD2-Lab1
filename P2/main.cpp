#include <iostream>
#include <fstream>
#include <vector>
#include "fixedRecord.h"

using namespace std;

void llenarArray(char conteiner[], int sizeCont, string data){
	for(int i=0; i<sizeCont; i++){
		if(i < data.size())
			conteiner[i] = data[i];
		else
			conteiner[i] = ' ';
	}
	conteiner[sizeCont - 1] = '\0';
}

int main(){
    //Escribir registros por defecto en el archivo binario
    fstream file("alumnos.dat", ios::out | ios::binary);
    //Creación de header
	int i = -1;
	file.write((char*) &i, sizeof(i));
	file.close();

    //Creación de registros
    FixedRecord f("alumnos.dat");
    Alumno a;
    llenarArray(a.codigo, 5, "0001");
    llenarArray(a.nombre, 11, "Juan");
    llenarArray(a.apellidos, 20, "Perez Perez");
    llenarArray(a.carrera, 15, "Mecatronica");
    a.ciclo = 1;
    a.mensualidad = 1500;
    //Imprimo alumno
    cout << "ADD: Alumno 1" << endl;
    cout << "Codigo: " << a.codigo << endl;
    cout << "Nombre: " << a.nombre << endl;
    cout << "Apellidos: " << a.apellidos << endl;
    cout << "Carrera: " << a.carrera << endl;
    cout << "Ciclo: " << a.ciclo << endl;
    cout << "Mensualidad: " << a.mensualidad << endl;
    cout << "------------------------" << endl;
    f.add(a);

    llenarArray(a.codigo, 5, "0002");
    llenarArray(a.nombre, 11, "Maria");
    llenarArray(a.apellidos, 20, "Gomez Gomez");
    llenarArray(a.carrera, 15, "CS");
    a.ciclo = 2;
    a.mensualidad = 2200;
    cout << "ADD: Alumno 2" << endl;
    cout << "Codigo: " << a.codigo << endl;
    cout << "Nombre: " << a.nombre << endl;
    cout << "Apellidos: " << a.apellidos << endl;
    cout << "Carrera: " << a.carrera << endl;
    cout << "Ciclo: " << a.ciclo << endl;
    cout << "Mensualidad: " << a.mensualidad << endl;
    cout << "------------------------" << endl;
    f.add(a);

    llenarArray(a.codigo, 5, "0003");
    llenarArray(a.nombre, 11, "Pedro");
    llenarArray(a.apellidos, 20, "Lopez Lopez");
    llenarArray(a.carrera, 15, "DS");
    a.ciclo = 3;
    a.mensualidad = 3000;
    cout << "ADD: Alumno 3" << endl;
    cout << "Codigo: " << a.codigo << endl;
    cout << "Nombre: " << a.nombre << endl;
    cout << "Apellidos: " << a.apellidos << endl;
    cout << "Carrera: " << a.carrera << endl;
    cout << "Ciclo: " << a.ciclo << endl;
    cout << "Mensualidad: " << a.mensualidad << endl;
    cout << "------------------------" << endl;
    f.add(a);

    //Obtengo los registros del archivo binario
    vector<Alumno> alumnos = f.load();
    cout << "Cantidad de registros: " << alumnos.size() << endl;
    cout << "------------------------" << endl;
    cout << "---Registros---" << endl;
    //Imprimo los registros
    for(int i=0; i<alumnos.size(); i++){
        cout << "Codigo: " << alumnos[i].codigo << endl;
        cout << "Nombre: " << alumnos[i].nombre << endl;
        cout << "Apellidos: " << alumnos[i].apellidos << endl;
        cout << "Carrera: " << alumnos[i].carrera << endl;
        cout << "Ciclo: " << alumnos[i].ciclo << endl;
        cout << "Mensualidad: " << alumnos[i].mensualidad << endl;
        cout << "NextD: " << alumnos[i].nextD << endl;
        cout << endl;
    }

    //Obtengo un registro en especifico
    Alumno alumno = f.readRecord(1);
    cout << "------------------------" << endl;
    //Imprimo el registro (Los registros empiezan en 1)
    cout << "Imprimo registro de la posición 1:" << endl;
    cout << "Codigo: " << alumno.codigo << endl;
    cout << "Nombre: " << alumno.nombre << endl;
    cout << "Apellidos: " << alumno.apellidos << endl;
    cout << "Carrera: " << alumno.carrera << endl;
    cout << "Ciclo: " << alumno.ciclo << endl;
    cout << "Mensualidad: " << alumno.mensualidad << endl;
    cout << "NextD: " << alumno.nextD << endl;
    cout << endl;

    //Leo registro en la pos 2
    alumno = f.readRecord(2);
    cout << "------------------------" << endl;
    cout << "Imprimo registro de la posición 2:" << endl;
    cout << "Codigo: " << alumno.codigo << endl;
    cout << "Nombre: " << alumno.nombre << endl;
    cout << "Apellidos: " << alumno.apellidos << endl;
    cout << "Carrera: " << alumno.carrera << endl;
    cout << "Ciclo: " << alumno.ciclo << endl;
    cout << "Mensualidad: " << alumno.mensualidad << endl;
    cout << "NextD: " << alumno.nextD << endl;
    cout << endl;

    //Elimino registro
    cout << "------------------------" << endl;
    cout << "Elimino registro en las posiciones 1 y 2" << endl;
    f.deleteRecord(1);
    f.deleteRecord(2);

    //Obtengo los nuevos registros
    alumnos = f.load();
    cout << "Cantidad de registros: " << alumnos.size() << endl;
    cout << "------------------------" << endl;
    cout << "---Registros restantes---" << endl;
    //Imprimo los registros
    for(int i=0; i<alumnos.size(); i++){
        cout << "Codigo: " << alumnos[i].codigo << endl;
        cout << "Nombre: " << alumnos[i].nombre << endl;
        cout << "Apellidos: " << alumnos[i].apellidos << endl;
        cout << "Carrera: " << alumnos[i].carrera << endl;
        cout << "Ciclo: " << alumnos[i].ciclo << endl;
        cout << "Mensualidad: " << alumnos[i].mensualidad << endl;
        cout << "NextD: " << alumnos[i].nextD << endl;
        cout << endl;
    }
    return 0;
}