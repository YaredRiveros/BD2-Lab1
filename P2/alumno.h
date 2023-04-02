#include <iostream>

using namespace std;

struct Alumno{
	char codigo[5];
	char nombre[11];
	char apellidos[20];
	char carrera[15];
	int ciclo;
	float mensualidad;
	int nextD = 0;

	// Alumno(){
	// 	for(int i=0; i<5; i++)	codigo[i] = ' ';
	// 	for(int i=0; i<11; i++)	nombre[i] = ' ';
	// 	for(int i=0; i<20; i++)	apellidos[i] = ' ';
	// 	for(int i=0; i<15; i++)	carrera[i] = ' ';
	// 	ciclo = 0;
	// 	mensualidad = 0;
	// 	nextD = 0;
	// }
}; 