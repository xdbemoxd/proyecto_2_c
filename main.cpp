#include <iostream>
#include <string>
#include "ArbolBinario.h"
using namespace std;

//funcion utilizada para ordenar los datos recibidos en la entrada estandar en una lista
void acomodarLista(string cadena,list<int> &Lista);
//muestra los resultados obtenidos
void mostrarlista(list<int> Lista);
//sirve para comparar los caminos entre las ciudades obtenidas
void caminosLargos(list<int> &Lista,ArbolBinario<int>* Arbol);

/* 
------------------Variables del main--------------------------------------------------------
Arbol= como su nombre lo indica, es el apuntados al nodo padre
prePostOrden= utilizada para obtener el orden en el que van los nodos del arbol
nodos= esta se utiliza para leer cadenas de caracter y el orden de entrada de cada nodo
ListaNodos1= esta guarda el ingreso de los nodos en pre o post orden
ListaNodos2= esta guarda el ingreso de los nodos en inorden
c= utilizada para dictaminar la cantidad de veces que se ejecutara el poderosisimo programa
*/
int main()
{
	ArbolBinario<int>* Arbol= new ArbolBinario<int>();
	string prePostOrden,nodos;
	list<int> ListaNodos1,ListaNodos2;
	int c;

	cin>>c;
	for (int i = 0; i < c ; ++i)
	{
		//ingreso el orden, si es post o pre orden
		cin>>prePostOrden;
		//leo la cadena de caracteres que hay despues que se dictamina el orden
		getline( cin, nodos );
		//los acomodo en la lista de pre o post orden
		acomodarLista( nodos, ListaNodos1 );
		//esto es leer el inorden
		cin>>nodos;
		//leo la cadena de caracteres que hay despues que se dictamina el orden, ota vez
		getline( cin, nodos );
		//los acomodo en la lista de inorden
		acomodarLista( nodos, ListaNodos2 );

		//creo el arbol
		if ( prePostOrden == "PREORDEN" )
		{

			Arbol->preInOrden( ListaNodos1, ListaNodos2 );

		}else
		{

			Arbol->postInOrden( ListaNodos1, ListaNodos2 );

		}

		//vacio ambas listas para no generar problemas
		ListaNodos1.clear();
		ListaNodos2.clear();

		//almaceno los datos de las ciudades que estan mas alejadas de la ciudad padre
		Arbol->frontera( ListaNodos1 );

		//busco cuales son las ciudades con el trayecto mas largo y las almaceno en una lista
		caminosLargos( ListaNodos1, Arbol );
		
		//imprimo la lista de ciudades con los trayectos mas largos
		mostrarlista( ListaNodos1 );

		//vacio la lista para evitar incovenientes
		ListaNodos1.clear();


	}
	return 0;
}

/*
paso la cadena donde se suponen que van los numeros de las ciudades y las ordeno en una lista
Laux= variable que se utiliza para ayudar a almacenar el ultimo numero de la cadena de caracteres, puesto que este no se guarda
i= iterador utilizado en el for, para recorrer la cadena de caracteres, caracter por caracter
aux= es el que almacena el numero que se va a ingresar en la lista
*/
void acomodarLista(string cadena,list<int> &Lista)
{
	int i,aux=0;
	list<char> Laux;


	for (i = 0; i < cadena.size(); ++i)
	{
		//verifico no estar sobre un ' ', porque ese no me interesa, en caso de no estarlo, guardo el numero entero
		if (cadena[i]!=' ')
		{
			//esta asi por si acaso hay mas de 1 numero consecutivo
			aux=(aux*10) + (cadena[i]-'0');

		}else
		{
			//si estoy en un ' ', guardo el numero en la lista de numero enteros
			if (i!=0 && cadena[i]==' ')
			{
	
				Lista.push_back(aux);
				aux=0;

			}

		}

	}

	//aqui fue donde tuve muchos problemas, con el ultimo numero
	//igualo i a la ultima posicion de la cadena
	i=cadena.size()-1;
	//este proceso se repetira hasta que encuentre un ' ', leyendo la cadena desde el final
	while(cadena[i]!=' ')
	{
		//los almaceno en Laux, claro se esta leyendo la cadena al revés, por ende debo simular una pila asi si entra 321, me los guarde 123
		Laux.push_front(cadena[i]);
		i=i-1;
	}

	//ya dije para que sirve aux XD
	aux=0;
	//aqui convierto los caracteres en numeros enteros segun la tabla ascii, se repetira mientras Laux tenga elementos
	while(!Laux.empty())
	{	

		aux=(aux*10) + (Laux.front()-'0');
		Laux.pop_front();

	}
	
	//agrego el numero obtenido en aux al final de la lista
	Lista.push_back(aux);
}

//muestro los resultados de la busqueda
void mostrarlista(list<int> Lista)
{
	list<int>::iterator it;
	int i=0;

	for ( it = Lista.begin(); it != Lista.end(); ++it)
	{
		if ( i%2 == 0 )
		{

			cout<<'('<<*it<<',';
			i++;

		}else
		{

			if (i%2==1)
			{

				cout<<*it<<')';
				i++;

				if (Lista.size()>2 && i<Lista.size())
				{
					cout<<',';
				}

			}
		}

		cout<<' ';

	}

	cout<<endl;
}

/*
aqui despues de obtener las ciudades mas alejadas del padre, las comparo entre ellas y las almaceno
Laux= en esta funcion se utiliza como un comparador de ciudades, porque aqui guardo todas las ciudades, menos la primera de la lista
DistaciasGrandes= guardo las ciudades entre las que tiene mayores distancias
distancia= almaceno la distancia entre ciudades mas alta
*/
void caminosLargos(list<int> &Lista, ArbolBinario<int>* Arbol)
{
	list<int> Laux, DistanciasGrandes;
	int distancia=0, aux, ciudad;

	//este ciclo es el ayuda a determinar las ciudades que tienen las distancias mas largas
	while( Lista.size() > 1 )
	{
		//asigno el primer elemento de la lista a la variable ciudad, puesto que esta la utilizare para hacer comparaciones
		ciudad=Lista.front();
		//lo elimino de la lista
		Lista.pop_front();
		//utilizo Laux, para guardar las ciudades a las cuales voy a comparar con la ciudad almacenada en la variable ciudad
		Laux=Lista;
		
		//en este ciclo almaceno las ciudades con distancias mas largos, las almacena en la variable DstanciasGrandes
		while( !Laux.empty() )
		{
			//aqui guardo la distancia entre las 2 ciudades
			aux=Arbol->DiametroNodos( ciudad,Laux.front() );
			
			//se compara con la variable distancia para verificar si es igual o mayor, de ser mayor debo vaciar la lista y almacenar las ciudades
			if ( aux > distancia )
			{
				//aqui almaceno los numeros de las ciudades y la distancia mas larga
				DistanciasGrandes.clear();
				DistanciasGrandes.push_back( ciudad );
				DistanciasGrandes.push_back( Laux.front() );
				distancia=aux;

			}else
			{
				//si existen otro par de ciudades con la misma distancia, las almaceno en la lista
				if ( aux == distancia )
				{
					DistanciasGrandes.push_back( ciudad );
					DistanciasGrandes.push_back( Laux.front() );
				}
				
			}
			
			Laux.pop_front();

		}

	}

	//almaceno las ciudades para luego imprimirla
	Lista=DistanciasGrandes;
}