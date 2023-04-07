#include <iostream>

using namespace std;

struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
    const char* arr[2]; //array de strings

    size_t getSize(){
        //Devuelve el total de bytes reales de todos los atributos de texto y empaqueta
        arr[0] = codigo.c_str();
        arr[1] = observaciones.c_str();
        return sizeof(arr)/sizeof(*arr);
    }
    
    const char** empaquetar(){
        //devuelve los atributos empaquetados
        return arr; 
    }

    void desempaquetar(char** buffer, size_t size){
        //Desempaqueta el buffer y guarda los atributos en el objeto
        codigo = buffer[0];
        observaciones = buffer[1];
    }
};