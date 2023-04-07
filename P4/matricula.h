#include <iostream>

using namespace std;

struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
    const char* arr[4]; //array de strings

    size_t getSize(){
        //Devuelve el total de bytes reales de todos los atributos y empaqueta
        arr[0] = codigo.c_str();
        cout << "Ciclo: " << ciclo << endl;
        string cicloString = to_string(ciclo);
        cout << "cicloString: " << cicloString << endl;
        const char* cicloCad = cicloString.c_str();
        cout << "cicloCad: " << cicloCad << endl;
        arr[1] = cicloCad;
        cout << "arr[1]: " << arr[1] << endl;
        string mensualidadString = to_string(mensualidad);
        const char* mensualidadCad = mensualidadString.c_str();
        arr[2] = mensualidadCad;
        cout << "Arr[2]: " << arr[2] << endl;
        arr[3] = observaciones.c_str();
        return sizeof(arr)/sizeof(*arr);
    }
    
    const char** empaquetar(){
        //devuelve los atributos empaquetados
        cout << "--empaquetado" << endl;
        cout << "arr[0]:" << arr[0] << endl;
        cout << "arr[1]:" << arr[1] << endl;
        cout << "arr[2]:" << arr[2] << endl;
        cout << "arr[3]:" << arr[3] << endl;
        return arr; 
    }

    void desempaquetar(char** buffer, size_t size){
        //Desempaqueta el buffer y guarda los atributos en el objeto
        // cout << "buffer[0]: " << buffer[0] << endl;
        // cout << "buffer[1]: " << buffer[1] << endl;
        // cout << "buffer[2]: " << buffer[2] << endl;
        // cout << "buffer[3]: " << buffer[3] << endl;

        codigo = buffer[0];
        // ciclo = stoi(buffer[1]);
        // mensualidad = stof(buffer[2]);
        ciclo = 3;
        mensualidad = 1022;
        observaciones = buffer[3];
    }
};