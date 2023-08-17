#ifndef ArbolBinario_H_
#define ArbolBinario_H_

#include <list>
#include "NodoA.h"
#include <iostream>
using namespace std;

template <class Tipo>
class ArbolBinario
{
	private:
		NodoA<Tipo>* Raiz;
		
		void AlturaBrazo(NodoA<Tipo>* ActualNodo,int &Altura,int AlturaActual,bool &band,Tipo Dato);
		void Diametro(list< Tipo > &ListaNodo,NodoA<Tipo>* ActualNodo,Tipo Dato,bool &band);
		int Camino(list< Tipo > &ListaNodo1,list< Tipo > &ListaNodo2);
		void MostrarTamano(list<Tipo> ListaNodo);
		void CompletoYLleno(NodoA<Tipo>* Padre,int &CantNodos,bool &lleno,bool &completo);
		void Diametro2(list< NodoA<Tipo>* > &ListaNodo,NodoA<Tipo>* P,Tipo Dato,bool &band);
		void ObtenerPrimos(NodoA<Tipo>* Abuelo,NodoA<Tipo>* Padre,int nivel);
		NodoA<Tipo>* crearArbolPreInOrden(list<Tipo> &PreOrden,list<Tipo> &InOrden);
		NodoA<Tipo>* crearPostInOrden(list<Tipo> &PostOrden,list<Tipo> &InOrden);
		void frontera(list<Tipo> &Lista,NodoA<Tipo>* ActualNodo);

	public:

		ArbolBinario();
		ArbolBinario(Tipo Dato);
		
		Tipo ObtenerRaiz();
		NodoA<Tipo>* ObtenerNodoRaiz();
		void CrearABB(NodoA<Tipo>* ActualNodo,Tipo Dato);
		void MostrarArbol(NodoA<Tipo>* ActualNodo,int espacio);
		int AlturaBrazo(Tipo Dato);
		void preOrden(NodoA<Tipo>* ActualNodo,list<Tipo> &Recorrido);
		void inOrden(NodoA<Tipo>* ActualNodo,list<Tipo> &Recorrido);
		void postOrden(NodoA<Tipo>* ActualNodo,list<Tipo> &Recorrido);
		void LevelOrden(list<Tipo> &Recorrido);
		int DiametroNodos(Tipo Dato1,Tipo Dato2);
		void CompletoYLleno();
		void Primos(Tipo Dato1);
		void preInOrden(list<Tipo> PreOrden,list<Tipo> InOrden);
		void postInOrden(list<Tipo> PostOrden,list<Tipo> InOrden);
		void frontera(list<Tipo> &Lista);

};

//constructor 
template <class Tipo>
ArbolBinario<Tipo>::ArbolBinario()
{
	this->Raiz=NULL;
}

//constructor con un dato de parametro
template <class Tipo>		
ArbolBinario<Tipo>::ArbolBinario(Tipo Dato)
{
	this->Raiz=new NodoA<Tipo>(Dato);
}

//retorna el dato almacenado en el nodo raiz
template <class Tipo>
Tipo ArbolBinario<Tipo>::ObtenerRaiz()
{
	return (this->Raiz->ObtenerDato());
}

//obtiene el nodo raiz
template <class Tipo>
NodoA<Tipo>* ArbolBinario<Tipo>::ObtenerNodoRaiz()
{
	return (this->Raiz);
}

//funcion que crea un arbol de busqueda binaria 
template <class Tipo>
void ArbolBinario<Tipo>::CrearABB(NodoA<Tipo>* ActualNodo,Tipo Dato)
{
	
	if( Dato > ActualNodo->ObtenerDato() )
	{
		if ( ActualNodo->ObtenerHijoDerecho() != NULL )
		{
			this->CrearABB(ActualNodo->ObtenerHijoDerecho(),Dato);
		}else
		{
			NodoA<Tipo>* NuevoNodo=new NodoA<Tipo>(Dato);
			ActualNodo->ModificarHijoDerecho( NuevoNodo );
		}
			
	}else
	{
		if ( ActualNodo->ObtenerHijoIzquierdo() != NULL )
		{
				this->CrearABB( ActualNodo->ObtenerHijoIzquierdo() ,Dato );
		}else
		{
				NodoA<Tipo>* NuevoNodo=new NodoA<Tipo>( Dato );
				ActualNodo->ModificarHijoIzquierdo( NuevoNodo );
		}
	}
	
}

//funcion que imprime el arbol en pantalla
template <class Tipo>
void ArbolBinario<Tipo>::MostrarArbol(NodoA<Tipo>* ActualNodo,int espacio)
{

	if ( ActualNodo->ObtenerHijoDerecho() != NULL )
	{
		this->MostrarArbol( ActualNodo->ObtenerHijoDerecho(), espacio+1 );
	}

	for (int i = 0; i < espacio; i++)
	{
		cout<<"       ";
	}
	
	cout<<ActualNodo->ObtenerDato()<<endl;

	if ( ActualNodo->ObtenerHijoIzquierdo() != NULL )
	{
		this->MostrarArbol( ActualNodo->ObtenerHijoIzquierdo(), espacio+1 );
	}
}

//busca el nivel del nodo al que se esta buscando
template <class Tipo>
void ArbolBinario<Tipo>::AlturaBrazo(NodoA<Tipo>* ActualNodo,int &Altura,int AlturaActual,bool &band,Tipo Dato)
{
	if ( ActualNodo->ObtenerDato() == Dato )
	{
		band=true;
		Altura=AlturaActual;
	}

	
	if ( ActualNodo->ObtenerHijoIzquierdo() != NULL &&  band != true )
	{
		this->AlturaBrazo( ActualNodo->ObtenerHijoIzquierdo(), Altura, AlturaActual+1, band, Dato );
	}

	if (ActualNodo->ObtenerHijoDerecho()!=NULL && band!=true)
	{
		this->AlturaBrazo( ActualNodo->ObtenerHijoDerecho(), Altura, AlturaActual+1, band, Dato );
	}
}

//funcion encarga de buscar a que brazo pertenece el nodo que se esta buscando, ademas del nivel, de no encontrarse el nodo retorna -1
template <class Tipo>
int ArbolBinario<Tipo>::AlturaBrazo(Tipo Dato)
{
	int aux=0;
	bool band=false;
	NodoA<Tipo>* Nodo=this->ObtenerNodoRaiz();

	if ( this->ObtenerRaiz() != Dato )
	{
		this->AlturaBrazo( Nodo->ObtenerHijoIzquierdo(), aux, 1, band, Dato);

		if ( band != true )
		{
			this->AlturaBrazo( Nodo->ObtenerHijoDerecho(), aux, 1, band, Dato);
		}

		if ( band != true )
		{
			aux=-1;
		}
	}

	return aux;
}

//recorre el arbol en preorden
template <class Tipo>
void ArbolBinario<Tipo>::preOrden(NodoA<Tipo>* ActualNodo,list<Tipo> &Recorrido)
{
	Recorrido.push_back ( ActualNodo->ObtenerDato() );

	if ( ActualNodo->ObtenerHijoIzquierdo() != NULL )
	{
		this->preOrden(ActualNodo->ObtenerHijoIzquierdo(),Recorrido);
	}

	if (ActualNodo->ObtenerHijoDerecho()!=NULL)
	{
		this->preOrden(ActualNodo->ObtenerHijoDerecho(),Recorrido);
	}
}

//reocorre el arbol en inorden
template <class Tipo>
void ArbolBinario<Tipo>::inOrden(NodoA<Tipo>* ActualNodo,list<Tipo> &Recorrido)
{

	if ( ActualNodo->ObtenerHijoIzquierdo() != NULL )
	{
		this->inOrden(ActualNodo->ObtenerHijoIzquierdo(),Recorrido);
	}

	Recorrido.push_back ( ActualNodo->ObtenerDato() );

	if (ActualNodo->ObtenerHijoDerecho()!=NULL)
	{
		this->inOrden(ActualNodo->ObtenerHijoDerecho(),Recorrido);
	}
}

//recorre el arbol en postorden
template <class Tipo>
void ArbolBinario<Tipo>::postOrden(NodoA<Tipo>* ActualNodo,list<Tipo> &Recorrido)
{
	if ( ActualNodo->ObtenerHijoIzquierdo() != NULL )
	{
		this->postOrden(ActualNodo->ObtenerHijoIzquierdo(),Recorrido);
	}

	if (ActualNodo->ObtenerHijoDerecho()!=NULL)
	{
		this->postOrden(ActualNodo->ObtenerHijoDerecho(),Recorrido);
	}

	Recorrido.push_back ( ActualNodo->ObtenerDato() );
}

//recorre el arbol por niveles
template <class Tipo>
void ArbolBinario<Tipo>::LevelOrden(list<Tipo> &Recorrido)
{
	list< NodoA<Tipo>* > ListaNodo;
	NodoA<Tipo>* ActualNodo=this->ObtenerNodoRaiz();

	ListaNodo.push_back( this->ObtenerNodoRaiz() );
	Recorrido.push_back( ActualNodo->ObtenerDato() );
	
	while( !ListaNodo.empty() ) 
	{
		if ( ActualNodo->ObtenerHijoIzquierdo() != NULL )
		{
			ListaNodo.push_back( ActualNodo->ObtenerHijoIzquierdo() );
		}

		if ( ActualNodo->ObtenerHijoDerecho() != NULL )
		{
			ListaNodo.push_back( ActualNodo->ObtenerHijoDerecho() );
		}

		ListaNodo.pop_front();

		if( !ListaNodo.empty() )
		{
			ActualNodo=ListaNodo.front();
			Recorrido.push_back( ActualNodo->ObtenerDato() );
		}
	}
}

//funcion que determina la distancia entre nodos, a traves del numero de aristas entre ellos 
template <class Tipo>
int ArbolBinario<Tipo>::DiametroNodos(Tipo Dato1,Tipo Dato2)
{
	//en la variable aux almaceno la distancia entre los nodos
	int aux=0;
	//en las siguientes listas almaceno el reocorrido de los nodos 
	list< Tipo > ListaNodo1;
	list< Tipo > ListaNodo2;
	//estas variables son utilizadas para verificar que el nodo si esta en el arbol
	bool band1=false,band2=false;
	//ayuda a determinar en que parte se encuentra el nodo
	NodoA<Tipo>* Padre=this->ObtenerNodoRaiz();
	
	//verifico que los 2 nodos sean distintos, de ser iguales no hay distancia que calcular
	if ( Dato1 != Dato2 )
	{
		//los primeros 2 condiconales, son para verifcar que uno de los 2 nodos no sea el padre, caso de serlo, hace una busqueda por niveles, 
		//para determinar el nivel, ya que este determina la cantidad de aristas que hay entre los nodos
		if ( Dato1 == this->ObtenerRaiz() )
		{
			aux=this->AlturaBrazo( Dato2 );
		}else
		{
			if ( Dato2 == this->ObtenerRaiz() )
			{
				aux=this->AlturaBrazo( Dato1 );
			}else
			{	
				//aqui se buscan los nodos y se guarda en una lista para cada uno, el camino de ambos
				this->Diametro( ListaNodo1, Padre->ObtenerHijoIzquierdo(), Dato1, band1);
				this->Diametro( ListaNodo2, Padre->ObtenerHijoIzquierdo(), Dato2, band2);

				if ( band1 == false )
				{
					this->Diametro( ListaNodo1, Padre->ObtenerHijoDerecho(), Dato1, band1);	
				}

				if ( band2 == false )
				{
					this->Diametro( ListaNodo2, Padre->ObtenerHijoDerecho(), Dato2, band2);
				}

				//en caso de no existir, se retorna -1
				if ( band1 == false || band2 == false )
				{
					aux=-1;
				}else
				{
					//como mayormente hay un camino mas largo que el otro, procedo con este condicional, 
					//ayuda a la funcion a obtener mas eficazmente las aristas
					if( ListaNodo1.size() > ListaNodo2.size() )
					{

						aux=this->Camino( ListaNodo1, ListaNodo2);
			
					}else
					{

						aux=this->Camino( ListaNodo2, ListaNodo1);
												
					}
				}
			}
		}
	}

	return aux;
}

//esta funcion se encarga de buscar los nodos y almacenar el camino
template <class Tipo>
void ArbolBinario<Tipo>::Diametro(list< Tipo > &ListaNodo,NodoA<Tipo>* ActualNodo,Tipo Dato,bool &band)
{
	if ( Dato == ActualNodo->ObtenerDato() )
	{
		band=true;
	}

	if ( band != true && ActualNodo->ObtenerHijoIzquierdo() != NULL )
	{
		this->Diametro( ListaNodo,ActualNodo->ObtenerHijoIzquierdo(), Dato, band );
	}

	if ( band != true && ActualNodo->ObtenerHijoDerecho() != NULL )
	{
		this->Diametro( ListaNodo, ActualNodo->ObtenerHijoDerecho(), Dato, band );
	}

	if ( band == true )
	{
		ListaNodo.push_front( ActualNodo->ObtenerDato() );
	}
}

//funcion encargada de obtener el numero de aristas que exiten entre los nodos
template <class Tipo>
int ArbolBinario<Tipo>::Camino(list< Tipo > &ListaGrande,list< Tipo > &ListaChica)
{
	int aux=0;
	
	//Mientras la lista grande tenga elementos, se repetira el ciclo
	while( !ListaGrande.empty() )
	{

		//si la lista chica no es vacia
		if ( !ListaChica.empty() )
		{	
			//se verifica que los nodos sean distintos, para empezar a sumar
			if ( ListaGrande.front() != ListaChica.front() )
			{
				//de ser distintos, se sumaran 2 aristas
				aux=aux+2;
			}
			
			//elimino el elemento para evaluar el siguiente
			ListaChica.pop_front();

		}else
		{
			//si la lista chica es vacia, sumo una arista
			if ( ListaChica.empty() )
			{
				aux=aux+1;
			}
		}
		
		//elimino el elemento actual para seguir el conteo
		ListaGrande.pop_front();
	}
	
	//retorno la cantidad de aristas distintas entre los nodos
	return ( aux );
}

//retorna la longitud de una lista, la utilice para hacer algunas verificaciones en mi libreria
template <class Tipo>
void ArbolBinario<Tipo>::MostrarTamano(list<Tipo> ListaNodo)
{
	cout<<ListaNodo.size()<<endl<<endl;
}

//veifica si un arbol es completo y lleno
template <class Tipo>
void ArbolBinario<Tipo>::CompletoYLleno()
{
	bool lleno,completo;
	int n;

	this->CompletoYLleno( this->Raiz, n, lleno, completo );

	if (lleno==true)
	{
		cout<<"\nes lleno\n";
	}else
	{
		cout<<"\nno es lleno\n";
	}

	if (completo==true)
	{
		cout<<"\nes completo\n";
	}else
	{
		cout<<"\nno es completo\n";
	}
}

//funcion que verifica que los subarboles del arbol sean llenos y completos
template <class Tipo>
void ArbolBinario<Tipo>::CompletoYLleno(NodoA<Tipo>* Padre,int &CantNodos,bool &lleno,bool &completo)
{
	int cantDerecha=0,cantizq=0;
	bool llenoizq=false,llenoderecha=false,completoizq=false,completoderecha=false,tiene2hijos=false;

	if ( Padre != NULL )
	{
		
		if ( Padre->ObtenerHijoIzquierdo() == NULL && Padre->ObtenerHijoDerecho() == NULL )
		{
			CantNodos=1;
			completo=true;
			lleno=true;
		}else
		{
			if ( Padre->ObtenerHijoIzquierdo() != NULL && Padre->ObtenerHijoDerecho() != NULL )
			{
				tiene2hijos=true;
			}
			
			this->CompletoYLleno( Padre->ObtenerHijoIzquierdo(), cantizq, llenoizq, completoizq );
			this->CompletoYLleno(Padre->ObtenerHijoDerecho(),cantDerecha,llenoderecha,completoderecha);
			
			if ( tiene2hijos == true && completoderecha == true && completoizq == true )
			{
				completo=true;
			}else
			{
				completo=false;
			}

			if ( completo == true && cantDerecha == cantizq )
			{
				lleno=true;
			}else
			{
				lleno=false;
			}
			
			CantNodos=cantizq+cantDerecha;
		}

	}else
	{
		CantNodos=0;
		completo=true;
		lleno=true;
	}
}

//funcion para obtener primos de los nodos
template <class Tipo>
void ArbolBinario<Tipo>::Primos(Tipo Dato1)
{
	//lista donde guardare los nodos del camino 
	list< NodoA<Tipo>* > ListaNodo;
	//con esta variable verifico que el dato buscado, pertenezca a un nodo
	bool band=false;
	//asigno la raiz a esta variable para facilitar la busqueda
	NodoA<Tipo>* ActualNodo=this->ObtenerNodoRaiz();

	//verifico que no me esten mando el dato de la raiz
	if ( ActualNodo->ObtenerDato() != Dato1 )
	{
		//busco en el subarbol izquierdo de la raiz
		this->Diametro2( ListaNodo, ActualNodo->ObtenerHijoIzquierdo(), Dato1, band );

		//busco en el subarbol derecho de la raiz
		if ( band == false )
		{
			this->Diametro2(ListaNodo,ActualNodo->ObtenerHijoDerecho(),Dato1,band);
		}

		//agrego el nodo raiz a la lista, es necesario agragarlo, ocasionalmente es el abuelo
		ListaNodo.push_front(ActualNodo);
		
		//elimino los nodos de la lista que no son utiles, dejando solo al padre, el abuelo y al hijo
		while( band == true && ListaNodo.size() > 3 )
		{
			ListaNodo.pop_front();
		}	

		//verifico que la lista contenga mas de 3 nodos, caso contrario no tendra primos
		if ( band == true && ListaNodo.size() == 3 )
		{
			//actualizo la variable actual nodo, con el abuelo del nodo buscado 
			ActualNodo=ListaNodo.front();
			//elimino al abuelo del nodo
			ListaNodo.pop_front();
			//ingreso a la funciom obtener primos, la cual los imprimira en pantalla
			this->ObtenerPrimos(ActualNodo,ListaNodo.front(),2);
		}else
		{
			//en caso de que la lista tenga menos de 3 elementos, el nodo no tendra primos
			if ( ListaNodo.size() < 3 && band == true )
			{
				cout<<"no tiene Primos"<<endl;
			}
		}
	}
	
	//
	if ( band == false )
	{
		cout<<"no existe, verifique los datos ingesados"<<endl;
	}
	

}

//esta es la funcion que guarda el camino de nodos para luego encontrar a los primos
template <class Tipo>
void ArbolBinario<Tipo>::Diametro2(list< NodoA<Tipo>* > &ListaNodo,NodoA<Tipo>* P,Tipo Dato,bool &band)
{
	if ( Dato == P->ObtenerDato() )
	{
		band=true;
	}

	if ( band != true && P->ObtenerHijoIzquierdo() != NULL )
	{
		this->Diametro2( ListaNodo, P->ObtenerHijoIzquierdo(), Dato, band );
	}

	if ( band != true && P->ObtenerHijoDerecho() != NULL )
	{
		this->Diametro2( ListaNodo, P->ObtenerHijoDerecho(), Dato, band );
	}

	if ( band == true )
	{
		ListaNodo.push_front( P );
	}
}

//funcion que imprime a los primos en caso de tenerlos, es como una busqueda en preorden
template <class Tipo>
void ArbolBinario<Tipo>::ObtenerPrimos(NodoA<Tipo>* Abuelo,NodoA<Tipo>* Padre,int nivel)
{
	if (nivel>0 && Abuelo->ObtenerHijoIzquierdo()!=NULL && Abuelo->ObtenerHijoIzquierdo()->ObtenerDato()!=Padre->ObtenerDato())
	{
		this->ObtenerPrimos(Abuelo->ObtenerHijoIzquierdo(),Padre,nivel-1);
	}

	if (nivel>0 && Abuelo->ObtenerHijoDerecho()!=NULL && Abuelo->ObtenerHijoDerecho()->ObtenerDato()!=Padre->ObtenerDato())
	{
		this->ObtenerPrimos(Abuelo->ObtenerHijoDerecho(),Padre,nivel-1);	
	}

	if (nivel==0)
	{
		cout<<Abuelo->ObtenerDato()<<endl;
	}
}

//Funcion que recibe 2 lista por referencia y crea un arbol a traves de ellas, como su nimbre lo indica preInOrden
template <class Tipo>
void ArbolBinario<Tipo>::preInOrden(list<Tipo> PreOrden,list<Tipo> InOrden)
{
	this->Raiz=this->crearArbolPreInOrden(PreOrden,InOrden);
}

//asigna el dato y crea a los nodos correspondientes para cada caso, con su respectivo dato
template <class Tipo>
NodoA<Tipo>* ArbolBinario<Tipo>::crearArbolPreInOrden(list<Tipo> &PreOrden,list<Tipo> &InOrden)
{
	NodoA<Tipo>* NodoRaiz=NULL;

	list<Tipo> InOrdenIzquierda;

	if ( !PreOrden.empty() && !InOrden.empty() )
	{

		while( PreOrden.front() != InOrden.front() )
		{
			InOrdenIzquierda.push_back( InOrden.front() );

			InOrden.pop_front();
		}

		NodoRaiz=new NodoA<Tipo>( PreOrden.front() );

		PreOrden.pop_front();

		InOrden.pop_front();

		NodoRaiz->ModificarHijoIzquierdo(this->crearArbolPreInOrden(PreOrden,InOrdenIzquierda));

		NodoRaiz->ModificarHijoDerecho(this->crearArbolPreInOrden(PreOrden,InOrden));

	}

	return NodoRaiz;
}

//Funcion que recibe 2 lista por referencia y crea un arbol a traves de ellas, como su nimbre lo indica postInOrden
template <class Tipo>
void ArbolBinario<Tipo>::postInOrden(list<Tipo> PostOrden,list<Tipo> InOrden)
{
	this->Raiz=this->crearPostInOrden(PostOrden,InOrden);
}

//asigna el dato y crea a los nodos correspondientes para cada caso, con su respectivo dato
template <class Tipo>
NodoA<Tipo>* ArbolBinario<Tipo>::crearPostInOrden(list<Tipo> &PostOrden,list<Tipo> &InOrden)
{
	NodoA<Tipo>* NodoRaiz=NULL;

	list<Tipo> InOrdenIzquierda;

	if ( !PostOrden.empty() && !InOrden.empty() )
	{

		while( PostOrden.back() != InOrden.front() )
		{
			InOrdenIzquierda.push_back( InOrden.front() );

			InOrden.pop_front();
		}

		NodoRaiz=new NodoA<Tipo>( PostOrden.back() );

		PostOrden.pop_back();

		InOrden.pop_front();

		NodoRaiz->ModificarHijoDerecho( this->crearPostInOrden( PostOrden, InOrden ) );

		NodoRaiz->ModificarHijoIzquierdo( this->crearPostInOrden( PostOrden, InOrdenIzquierda ) );

	}

	return NodoRaiz;
}

//esta funcion recibe una lista y llama a la funcion frontera donde comenzara a buscar los nodos hoja del arbol
template <class Tipo>
void ArbolBinario<Tipo>::frontera(list<Tipo> &Lista)
{
	this->frontera(Lista,this->Raiz);
}

//con esta busqueda en preorden, al encontrar un nodo hoja, almacenare el dato en una lista
template <class Tipo>
void ArbolBinario<Tipo>::frontera(list<Tipo> &Lista,NodoA<Tipo>* ActualNodo)
{
	if ( ActualNodo->ObtenerHijoDerecho() == NULL && ActualNodo->ObtenerHijoIzquierdo() == NULL )
	{
		Lista.push_back( ActualNodo->ObtenerDato() );
	}

	if ( ActualNodo->ObtenerHijoIzquierdo() != NULL )
	{
		this->frontera( Lista, ActualNodo->ObtenerHijoIzquierdo() );
	}

	if ( ActualNodo->ObtenerHijoDerecho() != NULL ) 
	{
		this->frontera( Lista, ActualNodo->ObtenerHijoDerecho() );
	}
}
#endif