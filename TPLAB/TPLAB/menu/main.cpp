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
	cout << "Tamanio Carrera: " << carrera.tamanio();
	cin >> pausa;
	return 0;
}
