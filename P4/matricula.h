#include <iostream>
#include <cstring>
#include <string>
// para usar sprintf_s
#include <stdio.h>

using namespace std;

struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;

    Matricula(){
        codigo = "";
        ciclo = 0;
        mensualidad = 0;
        observaciones = "";
    }

    Matricula(string codigo, int ciclo, float mensualidad, string observaciones){
        this->codigo = codigo;
        this->ciclo = ciclo;
        this->mensualidad = mensualidad;
        this->observaciones = observaciones;
    }

    size_t getSize(){
        return sizeof(codigo.length()+1) + sizeof(string)+ sizeof(int) + sizeof(float) + sizeof(observaciones.length()+1) + sizeof(string);
    }
    
    char* empaquetar(){
        char *buffer = new char[getSize()];

        char *ptr = buffer;
        auto size_c = codigo.length();

        //sprintf_s lo que hace es escribir en el buffer que le pasamos
        sprintf_s(ptr, sizeof(size_c), "%s", (char *) &size_c);
        ptr += sizeof(size_c); //avanzamos el puntero
        sprintf_s(ptr, size_c + 1, "%s", (char *) codigo.c_str()); //+1 para el \0
        ptr += size_c + 1;


        sprintf_s(ptr, sizeof(int), "%s", (char *) &ciclo); 
        ptr += sizeof(int);

        sprintf_s(ptr, sizeof(float) , "%s", (char *) &mensualidad);
        ptr += sizeof(float);
        
        // usamos el mismo buffer para el tamaño de la observacion
        auto size_o = observaciones.length();
        sprintf_s(ptr, sizeof(size_o), "%s", (char *) &size_o);
        ptr += sizeof(size_o);
        
        sprintf_s(ptr, size_o + 1, "%s", (char *) observaciones.c_str());

        return buffer;
    }

    void desempaquetar(char* buffer, size_t size){
        char *ptr = buffer;
        auto size_c = codigo.length();

        //sprintf_s lo que hace es escribir en el buffer que le pasamos
        sprintf_s((char *) &size_c, sizeof(size_c), "%s", ptr);
        ptr += sizeof(size_c); //avanzamos el puntero
        sprintf_s((char *) codigo.c_str(), size_c + 1, "%s", ptr); //+1 para el \0
        ptr += size_c + 1;


        sprintf_s((char *) &ciclo, sizeof(int), "%s", ptr);
        ptr += sizeof(int);

        sprintf_s((char *) &mensualidad, sizeof(float) , "%s", ptr);
        ptr += sizeof(float);

        // usamos el mismo buffer para el tamaño de la observacion
        auto size_o = observaciones.length();
        sprintf_s((char *) &size_o, sizeof(size_o), "%s", ptr);
        ptr += sizeof(size_o);

        sprintf_s((char *) observaciones.c_str(), size_o + 1, "%s", ptr);  

    }
};