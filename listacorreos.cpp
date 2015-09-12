#include<iostream>
#include<fstream>
#include<string>
#include<math.h>

using namespace std;

#include"ListaCorreos.h"


void inicializar(tListaCorreos & correos, int capacidad){
	correos.correo = new tCorreo [capacidad];
	correos.contador = 0;
	correos.capacidad = capacidad;
}

bool cargar(tListaCorreos & correos, string dominio){
	bool esCargar;
	ifstream archivo;
	float elementos, redondeo;
	string ficheroCorreo = dominio + "_" + mailCorreo;
	archivo.open(ficheroCorreo);
	if (archivo.is_open()){
		tCorreo correo;
		archivo >> elementos;
		redondeo = (ceil(elementos / 10)) * 10;
		inicializar(correos, (int) redondeo);
		for(int i = 0; i < elementos; i++){
			cargar (correo, archivo);
			insertar(correos, correo);
		}
		archivo.close();
		esCargar = true;
	}
	else{
		inicializar(correos, MAIL_INICIAL);
		esCargar = false;
	}
	return esCargar;
}

void guardar (const tListaCorreos & correos, string dominio){
	ofstream archivo;
	string ficheroCorreo = dominio + "_" + mailCorreo;
	archivo.open(ficheroCorreo);
	if (archivo.is_open()){
		archivo << correos.contador << endl;
		for(int i = 0; i < correos.contador; i++){
			guardar(correos.correo[i], archivo);
		}
		archivo.close();
	}
	else{
		cout << "No sé puedo guardar el archivo" << endl;
	}
}

void insertar(tListaCorreos & correos, const tCorreo & correo){
	int posicion;
	if (correos.contador == correos.capacidad){
		redimensionar (correos);
	}
		buscar(correos, correo.identificador, posicion);
		for(int i = correos.contador; i > posicion; i--)
			correos.correo[i] = correos.correo[i - 1];
		correos.correo[posicion] = correo;
		correos.contador++;
}


bool buscar (const tListaCorreos & correos, string id, int & pos){
	bool encontrado = false;
	pos = 0;
	while (pos < correos.contador && !encontrado){
		if(id == correos.correo[pos].identificador){
			encontrado = true;
		}
		else{
			pos++;
		}
	}
	return encontrado;
}

bool borrar(tListaCorreos &correos, string id){
	bool borrado = false;
	int posicion;
	if(buscar(correos, id , posicion)){
		system("pause");
				for (posicion; posicion < correos.contador; posicion++){
						correos.correo[posicion] = correos.correo[posicion + 1];
					}
		correos.contador--;
		borrado = true;
	}
return borrado;
}

void ordenar_AF(tListaCorreos & correos){
	int i = 0;
	bool esOrdenar = true;
	while ((i < correos.contador) && esOrdenar){
		esOrdenar = false;
		for (int j = correos.contador - 1; j > i; j--){
			if (correos.correo[j] < correos.correo[j - 1]){
				tCorreo tmp;
				tmp = correos.correo[j];
				correos.correo[j] = correos.correo[j - 1];
				correos.correo[j - 1] = tmp;
				esOrdenar = true;
			}
		}
		if (esOrdenar) i++;
	}
}

void destruir (tListaCorreos & correos){
	delete[] correos.correo;
}

void redimensionar (tListaCorreos & correos){
	tListaCorreos listaNueva;
	int i = 0;
	int capacidadNueva = (correos.capacidad * 3) / 2 + 1;
	inicializar (listaNueva, capacidadNueva);
	while (i < correos.contador){
		insertar(listaNueva, correos.correo[i++]);
	}
	correos = listaNueva;
}
