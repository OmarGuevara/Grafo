// Grafo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include "iostream"
#define X 8 //Cantidad de nodos del grafo
#define Y 8 //Cantidad de nodos del grafo
#define HEAD 4 //Nodo por el cual empezaremos a buscar los nodos más lejanos a este funciona como HEAD

int A[X][Y]; //Matriz que representa el grafo
int B[X][Y]; //Matriz que utilizo para ordenar los nodos respecto a su numero de aristas
//int cont = 0;

using namespace std;

void find_nodes(int node, int cont){  //función para buscar nodos
	vector<int> v; // construimos un vector cuyo tamaño empieza en 0
	for (int i = 0; i<X; i++){
		for (int j = 0; j < Y; j++){
			if ((i == node || j == node) && A[i][j] == 1)
			{				
				A[i][j] = 2; // Cambio el valor 1 por dos para los nodos que he visitado
				if (i == node)
				{
					v.push_back(j); // agregamos el elemento a v
				}
				if (j == node)
				{
					v.push_back(i); // agregamos el elemento a v
				}
			}
		}
	}
	cont++;
	for (int i = 0; i < v.size(); i++) //Empiezo a ordenar los nodos de acuerdo a su numero de aristas en la matriz B
	{
		if (B[cont][i] == (X + 1))
			B[cont][i] = v[i];
		else
			B[cont][i + 1] = v[i];
		find_nodes(v[i], cont); //Utilizo recursividad
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> nodostmp; //declaramos un vector para los nodos mas lejanos del nodo que usamos como head
	int flag = 0; //bandera para poder hacer el break del ciclo for
	//inicializar todo a 0 para A la matriz de nuestros nodos y para B todo un numero mas del ultimo valor de nuestro nodo
	for (int i = 0; i<X; i++)
		for (int j = 0; j < Y; j++)
		{
			A[i][j] = 0;
			B[i][j] = (X+1);
		}
	/*
	Aqui declaramos todas las aristas de los nodos del grafo este ejemplo pertenece al grafo de la entrevista
	1 = arista entre dos nodos 
	Ejemplo A[0][1] = 1 significa que existe una arista que une los dos nodos 
	*/
	A[0][1] = 1;
	A[1][2] = 1;
	A[2][4] = 1;
	A[3][4] = 1;
	A[4][6] = 1;
	A[5][6] = 1;
	A[6][7] = 1;

	/*Impresion de matriz A con aristas
	for (int i = 0; i<X; i++){
		for (int j = 0; j<Y; j++)
			cout << A[i][j]<<" ";
		cout <<endl;
	}*/

	find_nodes(HEAD,0); //Mandamos llamar la función encontrar nodos para que comience con el valor del HEAD y el numero de aristas 0
	
	/*cout << "Impresion de matriz B" << endl;
	for (int i = 0; i<X; i++){
		for (int j = 0; j<Y; j++)
			cout << B[i][j] << " ";
		cout << endl;
	}*/
	
	cout << "Nodos mas lejanos respecto al nodo: "<<HEAD << endl;
	for (int i = (X-1); i>=0; i--){
		for (int j = (Y - 1); j >= 0; j--)
		{
			if (B[i][j] != (X + 1))
			{
				cout << "Nodo: " << B[i][j] << " Aristas: " << i << endl;
				nodostmp.push_back(B[i][j]);
				flag = 1;
			}
		}
		if (flag == 1)
			break;
	}

	cout << "Los nodos mas lejanos entre si son: "<<endl;
	for (int k = 0; k < nodostmp.size(); k++)
	{
		//inicializar todo a 0
		for (int i = 0; i<X; i++)
			for (int j = 0; j < Y; j++)
			{ 
				if (A[i][j] == 2)
					A[i][j] = 1;
				B[i][j] = (X + 1);
			}
		
		find_nodes(nodostmp[k], 0);
		flag = 0;
		
		for (int i = (X - 1); i >= 0; i--){
			for (int j = (Y - 1); j >= 0; j--){
				if (B[i][j] != (X + 1))
				{
					cout << "Del nodo: " << nodostmp[k] << " al nodo: " << B[i][j] << " Cantidad de aristas que los separan: " << i << endl;
					//nodostmp.push_back(B[i][j]);
					flag = 1;
				}
			}
			if (flag == 1)
				break;
		}
	}
	

	system("PAUSE");
	return 0;
}

