#ifndef NodoA_H_
#define NodoA_H_
#include <iostream>
using namespace std;

template <class Tipo>
class NodoA
{
	private:
		
		Tipo Dato;
		NodoA<Tipo>* HijoIzquierdo;
		NodoA<Tipo>* HijoDerecho;

	public:
		NodoA();
		NodoA(Tipo NuevoDato);

		Tipo ObtenerDato();

		void ModificarDato( Tipo NuevoDato );

		NodoA<Tipo>* ObtenerHijoIzquierdo();

		NodoA<Tipo>* ObtenerHijoDerecho();

		void ModificarHijoIzquierdo( NodoA<Tipo>* NuevoHijoIzquierdo );

		void ModificarHijoDerecho( NodoA<Tipo>* NuevoHijoDerecho );

		bool EsHoja();
	
};

template <class Tipo>
NodoA<Tipo>::NodoA()
{
	this->HijoDerecho=NULL;
	this->HijoIzquierdo=NULL;
}

template <class Tipo>
NodoA<Tipo>::NodoA(Tipo NuevoDato)
{
	this->Dato=NuevoDato;
	this->HijoDerecho=NULL;
	this->HijoIzquierdo=NULL; 
}

template <class Tipo>
Tipo NodoA<Tipo>::ObtenerDato()
{
	return (this->Dato);
}

template <class Tipo>
void NodoA<Tipo>::ModificarDato( Tipo NuevoDato )
{
	this->Dato=NuevoDato;
}

template <class Tipo>
NodoA<Tipo>* NodoA<Tipo>::ObtenerHijoIzquierdo()
{
	return (this->HijoIzquierdo);
}

template <class Tipo>
NodoA<Tipo>* NodoA<Tipo>::ObtenerHijoDerecho()
{
	return (this->HijoDerecho);
}

template <class Tipo>
void NodoA<Tipo>::ModificarHijoIzquierdo( NodoA<Tipo>* NuevoHijoIzquierdo )
{
	this->HijoIzquierdo=NuevoHijoIzquierdo;
}

template <class Tipo>
void NodoA<Tipo>::ModificarHijoDerecho( NodoA<Tipo>* NuevoHijoDerecho )
{
	this->HijoDerecho=NuevoHijoDerecho;
}

template <class Tipo>
bool NodoA<Tipo>::EsHoja()
{
	bool aux=false;

	if (this->HijoIzquierdo==NULL && this->HijoDerecho==NULL)
	{
		aux=true;
	}

	return aux;
}



#endif