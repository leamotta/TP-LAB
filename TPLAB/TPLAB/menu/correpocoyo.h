#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CorrePocoyo{

  public:

	/*
	 * Crea una nueva carrera
	 */	
	CorrePocoyo();

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CorrePocoyo(const CorrePocoyo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CorrePocoyo();

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. Lo agregará al final 
	 */
	void nuevoCorredor(const T&);
	
	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor 
	 */
	void nuevoCorredor(const T&, const T&);
	
	/*
	 * Elimina del pocoyo al que se envía
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T&);
	/*
	 * El corredor pasa al que está adelante 
	 *
	 * PRE: Existe un corredor delante de él y T es un corredor 
	 */
	void sobrepasar(const T&);
	
	/*
	 * Devuelve el corredor que está siendo filmado.
	 *
	 * PRE: Hay adeptos en la CorrePocoyo.
	 */
	const T& corredorFilmado() const;
	
    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de atás 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxPerdedor();
	    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de adelante 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxExitoso();
	
	/*
	 * Devuelve al Primero. 
	 *
	 * PRE: Hay elementos 
	 */
	const T& damePrimero() const;	

	/*
	 * Devuelve la posición del elemento pasado por parámetro. 
	 *
	 * PRE: Existe ese corredor 
	 */
	int damePosicion(const T& ) const;	

	/*
	 * Devuelve el corredor de la posición. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int) const;	




	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	bool esVacia() const;

	
	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	bool operator==(const CorrePocoyo<T>&) const;	
	
	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	ostream& mostrarCorrePocoyo(ostream&) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		Nodo* atras;
		Nodo* adelante;
		T valor;
	};

	Nodo* primero;
	Nodo* filmado;
	Nodo* ultimo;
	int cantCorredores;

};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

// Implementación a hacer por los alumnos.
template<class T>
int CorrePocoyo <T>:: tamanio() const {
	return cantCorredores;
}

template<class T>
CorrePocoyo <T>:: CorrePocoyo()  {
	cantCorredores = 0;
	primero=NULL;
	ultimo=NULL;
}

template<class T>
CorrePocoyo <T>:: ~CorrePocoyo()  {
}

template<class T>
void CorrePocoyo <T>:: nuevoCorredor(const T& corredor)  {
	 Nodo* nuevo = new Nodo;
	 nuevo->valor = corredor;
	 nuevo->atras= NULL;
	 nuevo->adelante=ultimo;

	 if(primero==NULL)
	 {
		 primero=nuevo;
		 filmado=nuevo;
	}
	 else{
		 Nodo* n = primero;
		 while(n->atras!=NULL)
		 {
			n=n->atras;
		 }
		 n->atras=nuevo;
	 }
	 ultimo=nuevo;
	 cantCorredores++;
}

template<class T>
const T& CorrePocoyo <T>:: damePrimero() const  {
	return primero->valor;
}

template<class T>
void CorrePocoyo <T>:: nuevoCorredor(const T& corredornuevo, const T& corredor) {
	Nodo* nuevo = new Nodo;
	nuevo->valor = corredornuevo;
	Nodo* n = primero;
	while(n->valor!=corredor){
		n= n->atras;
	}
	nuevo->atras=n;
	nuevo->adelante=n->adelante;
	if(n==primero)
		primero=nuevo;
	n->adelante=nuevo;
	cantCorredores ++;
}

template<class T>
void CorrePocoyo<T>::seCansa(const T& cansado){
	Nodo* n = primero;

	//Busco al corredor cansado
	while(n!=NULL && n->valor!=cansado){
		n= n->atras; 
	}

	//Si bien por PRE el corredor existe, para evitar problemas con operaciones de memoria, lo valido
	if(n!=NULL){
		if(n->atras !=NULL)
			n->atras->adelante = n->adelante; //El de atras del cansado ahora tiene adelante a quien tenia el cansado adelante
		else
			ultimo = n->adelante; //Si no habia nadie atras,redefino el ultimo
	
		if(n->adelante!=NULL){
			n->adelante->atras = n->atras;    //El de adelante del cansado ahora tiene atras a quien tenia el cansado atras
		}
		else
			primero = n->atras; //Si no habia nadie adelante, redefino al primero
	
		delete n; //Libero la memoria del cansado
		cantCorredores--; //Siempre hay un corredor menos
	}
}

template<class T>
void CorrePocoyo <T>:: sobrepasar(const T& corredor) {
	Nodo* n = primero;
	while(n->valor!=corredor){
		n=n->atras;
	}
	if (n==ultimo)
		ultimo=n->adelante; //Si el ultimo es el que sobrepasa hay un nuevo ultimo
	if(n==primero->atras)
		primero=n;	//Si el segundo es el que sobrepasa, queda primero
	

	Nodo* aSobrepasar = n->adelante;
	if(n != primero)	//Si el segundo no es el que sobrepasa
	{
		aSobrepasar->adelante->atras=n; // Actualizo el que quedara adelante del que sobrepasa
	}
	if(n->adelante!=ultimo) // Si el ultimo no es el que sobrepasa
	{
		n->atras->adelante=aSobrepasar; // Actualizo el que quedara detras del relegado
	}
	// Ahora implemento el sobrepaso
	aSobrepasar->atras = n->atras;
	n->adelante=aSobrepasar->adelante;
	aSobrepasar->adelante = n;
	n->atras=aSobrepasar;
}

template<class T>
const T& CorrePocoyo <T>:: dameCorredorEnPos(int num) const {
	int i=1;
	Nodo* n = primero;
	while(i!=num)
	{
		n=n->atras;
		i++;
	}
	return n->valor;
}

template<class T>
int CorrePocoyo<T>::damePosicion(const T& corredor) const{
	int i=1;
	Nodo* n = primero;
	while(n!=NULL && n->valor!=corredor){
		n=n->atras;
		i++;
	}
	return i;
}

template<class T>
const T& CorrePocoyo <T>:: corredorFilmado() const {
	return filmado->valor;
}

template<class T>
void CorrePocoyo <T>:: filmarProxPerdedor() {
	 filmado=filmado->atras;
}

template<class T>
void CorrePocoyo <T>:: filmarProxExitoso() {
	 filmado=filmado->adelante;
}

template<class T>
ostream& CorrePocoyo<T> :: mostrarCorrePocoyo(ostream& os) const{
	os<<"[";
	Nodo* n = primero;
	while(n!=NULL){
		if(n!=primero)
			os<<",";
		os<<n->valor;
		n=n->atras;
	}
	os<<"]";
	return os;
}

template<class T>
bool CorrePocoyo<T>:: esVacia() const{
	return primero==NULL;
}
	
#endif //CORREPOCOYO_H_
