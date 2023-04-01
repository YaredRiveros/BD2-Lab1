#include <iostream>
#include "fixedRecord.h"

using namespace std;


int main(){

    cout << "Antes del nuevo alumno" << endl;
	FixedRecord f("datos1.txt");
	vector<Alumno> vec = f.load();
    cout << "Cantidad de registros: " << vec.size() << endl;
	for(size_t i = 0; i < vec.size(); i++){
        // cout << "codigo: " << vec[i].codigo << endl;
        // cout << "nombre: " << vec[i].nombre << endl;
        // cout << "apellidos: " << vec[i].apellidos << endl;
        // cout << "carrera: " << vec[i].carrera << endl;
        
		cout<<vec[i].codigo <<" "<< vec[i].nombre <<" "<< vec[i].apellidos <<" "<< vec[i].carrera << endl;
    }

    cout << endl << "--Ingreso del nuevo alumno--" << endl;
    Alumno nuevo;
    cout<< "Ingresar codigo: ";
    cin>>nuevo.codigo;
    cout<< "Ingresar nombre: ";
    cin>>nuevo.nombre;
    cin.ignore();
    cout<< "Ingresar apellidos: ";
    getline(cin,nuevo.apellidos);
    cout<< "Ingresar carrera: ";
    getline(cin,nuevo.carrera);	

    f.add(nuevo);
    vec = f.load();

    cout << "Cantidad de registros: " << vec.size() << endl;
    for(size_t i = 0; i < vec.size(); i++){
        // cout << "codigo: " << vec[i].codigo << endl;
        // cout << "nombre: " << vec[i].nombre << endl;
        // cout << "apellidos: " << vec[i].apellidos << endl;
        // cout << "carrera: " << vec[i].carrera << endl;
        
		cout<<vec[i].codigo <<" "<< vec[i].nombre <<" "<< vec[i].apellidos <<" "<< vec[i].carrera << endl;
    }

    //Leo un registro
    cout << endl << "--Lectura de un registro--" << endl;
    cout << "Ingrese el numero de registro a leer (desde 0):" << endl;
    int n;
    cin >> n;
    Alumno escogido = f.readRecord(n);
    cout << "Registro escogido: " << endl;
    cout<<escogido.codigo <<" "<< escogido.nombre <<" "<< escogido.apellidos <<" "<< escogido.carrera << endl;

    

    return 0;
}