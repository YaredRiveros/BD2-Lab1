#include <iostream>

using namespace std;

//Se utilizó atributos de tipo string porque al ser texto no binario no se necesita un tamaño fijo. Además, era necesario el uso 
//de strings para utilizar la función getline(), que se utiliza para leer las líneas del archivo de texto.

struct Alumno{
    string codigo;
    string nombre;
    string apellidos;
    string carrera;

    Alumno(){
        this->codigo = "";
        this->nombre = "";
        this->apellidos = "";
        this->carrera = "";
    }

    Alumno(string codigo, string nombre, string apellidos, string carrera){
        this->codigo = codigo;
        this->nombre = nombre;
        this->apellidos = apellidos;
        this->carrera = carrera;
    }
};