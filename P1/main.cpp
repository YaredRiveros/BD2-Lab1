#include <iostream>
#include "fixedRecord.h"

using namespace std;

int main(){

    cout << "Antes del nuevo alumno" << endl;
	FixedRecord f("datos1.txt");
	vector<Alumno> vec = f.load();
	for(size_t i = 0; i < vec.size(); i++){
        // cout << "codigo: " << vec[i].codigo << endl;
        // cout << "nombre: " << vec[i].nombre << endl;
        // cout << "apellidos: " << vec[i].apellidos << endl;
        // cout << "carrera: " << vec[i].carrera << endl;
        
		cout<<vec[i].codigo <<" "<< vec[i].nombre <<" "<< vec[i].apellidos <<" "<< vec[i].carrera << endl;
    }

    

    return 0;
}