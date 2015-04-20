#include <stdio.h>
#include <iostream>
#include <fstream>
#include "correpocoyo.h"

using namespace std;


int main() {
	int pausa;

	CorrePocoyo<int> carrera;
	carrera.nuevoCorredor(1);
	carrera.nuevoCorredor(2);
	carrera.nuevoCorredor(3);
	cout << "Tamanio Carrera: " << carrera.tamanio() << endl;
	cout << "Primero: " << carrera.damePrimero() << endl;
	carrera.nuevoCorredor(4,1);
	cout << "Primero: " << carrera.damePrimero() << endl;
	carrera.sobrepasar(2);
	carrera.sobrepasar(2);
	cout << "Primero: " << carrera.damePrimero() << endl;
	carrera.sobrepasar(4);
	cout << "Primero: " << carrera.damePrimero() << endl;
	cout << carrera.dameCorredorEnPos(1) << carrera.dameCorredorEnPos(2) << carrera.dameCorredorEnPos(3) << carrera.dameCorredorEnPos(4) << endl;
	cout << "Filmado: " << carrera.corredorFilmado() << endl;
	carrera.filmarProxPerdedor();
	cout << "Filmado: " << carrera.corredorFilmado() << endl;
	carrera.filmarProxExitoso();
	carrera.filmarProxExitoso();
	cout << "Filmado: " << carrera.corredorFilmado();
	

	cin >> pausa;
	return 0;
}
