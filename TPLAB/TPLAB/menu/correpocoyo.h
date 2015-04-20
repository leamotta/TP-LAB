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
	while(n->valor!=cansado){
		n= n->atras;
	}

	n->atras->adelante = n->adelante; //El de atras del cansado ahora tiene adelante a quien tenia el cansado adelante
	n->adelante->atras = n->atras;    //El de adelante del cansado ahora tiene atras a quien tenia el cansado atras
	
	delete n; //Elimino al cansado de la carrera
	cantCorredores--;
}

template<class T>
void CorrePocoyo <T>:: sobrepasar(const T& corredor) {
	Nodo* n = primero;
	while(n->valor!=corredor){
		n=n->atras;
	}
	if (n==ultimo)
		ultimo=n->adelante;
	if(n==primero->atras)
		primero=n;
	

	Nodo* aSobrepasar = n->adelante;
	if(n != primero)
	{
		aSobrepasar->adelante->atras=n;
	}
	if(n->adelante!=ultimo)
	{
		n->atras->adelante=aSobrepasar;
	}
	aSobrepasar->atras = n->atras;
	n->adelante=aSobrepasar->adelante;
	aSobrepasar->adelante = n;
	n->atras=aSobrepasar;
}

#endif //CORREPOCOYO_H_
