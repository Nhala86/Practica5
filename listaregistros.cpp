#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

#include "ListaRegistros.h"


void inicializar(tListaRegistros &registros, int capacidadInicial){
	registros.registro = new tRegistro[capacidadInicial];
	registros.contador = 0;
	registros.capacidad = capacidadInicial;
}

void cargar(tListaRegistros &registros, ifstream& archivo){
	float elementos, redondeo;
	tRegistro registro;

	archivo >> elementos;
	redondeo = (ceil(elementos / 10)) * 10;
	inicializar (registros, (int)redondeo);
	if(elementos>0){
		for(int i = 0; i < elementos; i++){
			cargarRegistro(registro, archivo);
			insertar(registros, registro);
		}
	}
}

void guardar(const tListaRegistros &registros, ofstream& archivo){
	for(int i= 0; i < registros.contador; i++){
		archivo << registros.registro[i].idcorreo << " " << registros.registro[i].leido << endl;
	}
}

void insertar(tListaRegistros &registros, tRegistro registro){
	if(registros.contador == registros.capacidad){
		redimensionar (registros);
	}
	registros.registro[registros.contador] = registro;
	registros.contador++;

}

bool borrar(tListaRegistros &registros, string id){
	bool borrado = false;
	int posicion = buscar(registros,id);
	if(posicion != -1){	//Si se encuentra el registro se elimina
			for (posicion; posicion < registros.contador; posicion++){
				registros.registro[posicion] = registros.registro[posicion+1]; //Desde la posicion elminada se desplazan una posicion a la izquierda
		}
		registros.contador--;
		borrado = true;
	}
return borrado;
}

bool correoLeido(tListaRegistros &registros, string id){
	bool check = false;
	int posicion = buscar(registros,id);

	if(posicion != -1){
		registros.registro[posicion].leido = true;
		check = true;
	}
	return check;
}

int buscar(const tListaRegistros &registros, string id){
	int posicion;
	int ini = 0, fin = registros.contador-1, mitad;

	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca

	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < registros.registro[mitad].idcorreo){
		fin = mitad - 1;			//acoto la busqueda por la derecha
		}
		else if(registros.registro[mitad].idcorreo < id){
		ini = mitad + 1;			//acoto la busqueda por la izquierda
		}
		else{
		encontrado = true;
		}
	}
	if(encontrado) posicion = mitad;
	else posicion = -1;

	return posicion;
}


void cargarRegistro(tRegistro& registro, ifstream& archivo){
		archivo >>registro.idcorreo;
		archivo >>registro.leido;
}

void redimensionar (tListaRegistros & registros){
	tListaRegistros listaNueva;
	int capacidadNueva = (registros.capacidad * 3)/ 2 + 1;
	int i = 0;
	inicializar (listaNueva, capacidadNueva);
	while (i < registros.contador){
		insertar (listaNueva, registros.registro[i++]);
	}
	registros = listaNueva;

}

void destruir (tListaRegistros & registros){
	delete[] registros.registro;
}
