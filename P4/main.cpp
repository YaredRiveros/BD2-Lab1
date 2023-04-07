#include <iostream>
#include <fstream>
#include "fixedRecord.h"
#include <vector>

using namespace std;

int main(){

    //Reinicio los archivos
    ofstream ofs("matriculas.bin", ios::out);
    ofs.close();

    ofstream ofs2("header.bin", ios::out);
    ofs2.close();

    //Inicializo el FixedRecord
    FixedRecord f("matriculas.bin");

    //Matricula por defecto
    Matricula m1;
    m1.codigo = "2018-1";
    m1.ciclo = 7;
    m1.mensualidad = 3000.67;
    m1.observaciones = "Un crack";
    f.add(m1);

    cout << "\t--Imprimo matrículas registradas hasta el momento--" << endl;
    vector<Matricula> matriculas = f.load();
    for(int i=0;i<matriculas.size();i++){
        cout << "Matrícula " << i+1 << endl;
        cout << "Código: " << matriculas[i].codigo << endl;
        cout << "Ciclo: " << matriculas[i].ciclo << endl;
        cout << "Mensualidad: " << matriculas[i].mensualidad << endl;
        cout << "Observaciones: " << matriculas[i].observaciones << endl;
        cout << "-----------------------------------------------" << endl;
    }

    cout << "\t--Agrego dos nuevas matrícula--" << endl; 
    Matricula m;
    cout << "Agrego la matrícula 2" << endl;
    //Nueva matricula 2
    m.codigo = "2019-1";
    m.ciclo = 1;
    m.mensualidad = 100;
    m.observaciones = "Un capo";
    f.add(m);

    // //Nueva matricula 3
    // cout << "Agrego la matrícula 3" << endl;
    // m.codigo = "2020-1";
    // m.ciclo = 2;
    // m.mensualidad = 200;
    // m.observaciones = "Cuídense de este";
    // f.add(m);

    cout << "\t--Imprimo matrículas registradas hasta el momento--" << endl;
    matriculas = f.load();
    for(int i=0;i<matriculas.size();i++){
        cout << "Matrícula " << i+1 << endl;
        cout << "Código: " << matriculas[i].codigo << endl;
        cout << "Ciclo: " << matriculas[i].ciclo << endl;
        cout << "Mensualidad: " << matriculas[i].mensualidad << endl;
        cout << "Observaciones: " << matriculas[i].observaciones << endl;
        cout << "-----------------------------------------------" << endl;
    }

    // cout << "\t--Leo la matrícula en la posición 1--" << endl;
    // Matricula m2 = f.readRecord(1);
    // cout << "Matrícula 1:" << endl << endl;
    // cout << "Código: " << m2.codigo << endl;
    // cout << "Ciclo: " << m2.ciclo << endl;
    // cout << "Mensualidad: " << m2.mensualidad << endl;
    // cout << "Observaciones: " << m2.observaciones << endl;
    // cout << "-----------------------------------------------" << endl;



    //errores:
    //1. El add agrega registros, pero no concuerdan con el código u observaciones ingresadas. Parece que se debe a que si cambio
    //el char** arr y lo escribo, se modifican todos los arrays escritos en el archivo. Por ello todas las matrículas tienen el
    //mismo código y observaciones. Sin embargo, esto no pasa con los enteros y floats porque los inserté directamente en el archivo.

    //La posible solución es dejar de intentar empaquetar los strings y escribirlos directamente en el archivo. 
    return 0;
}