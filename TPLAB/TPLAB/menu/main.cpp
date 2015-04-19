#include <stdio.h>
#include <iostream>
#include <fstream>
#include "correpocoyo.h"

using namespace std;


int main() {
	int pausa;

	CorrePocoyo<int> carrera;
	carrera.tamanio();
	cout << "Hola" << carrera.tamanio();
	cin >> pausa;
	return 0;
}
