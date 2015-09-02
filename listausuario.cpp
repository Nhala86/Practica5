#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#include"ListaUsuario.h"

void inicializar (tListaUsuarios & usuarios){
	usuarios.contador = 0;
	for (int i = 0; i < MAX_USUARIOS; i++){
		usuarios.usuario[i] = nullptr;
	}
}

bool cargar (tListaUsuarios & usuarios, string dominio){
	bool ok;
	ifstream archivo;
	inicializar(usuarios);
	string nombreFichero = dominio + "_" + listaUsuarios;
	archivo.open(nombreFichero);
	if (archivo.is_open()){
		tUsuario usuario;
		while (cargar(usuario, archivo)){ 
			aniadir (usuarios, usuario); 
		}
		archivo.close();
		ok = true;
	}
	else{
		ok = false;
	}
	return ok;
}

void guardar (const tListaUsuarios & usuarios, string dominio){
	ofstream archivo;
	string nombreFichero = dominio + "_" + listaUsuarios;
	archivo.open(nombreFichero);
	if (archivo.is_open()){
		for(int i = 0; i < usuarios.contador; i++){
			guardar(*usuarios.usuario[i], archivo);			
		}
		archivo << "XXX";
		archivo.close();		
	}
	else{
		cout << " No se puede guardar el archivo";
	}	
}

bool aniadir (tListaUsuarios & usuarios, const tUsuario & usuario){
	bool esAniadir = false;
	int posicion;
	if(usuarios.contador < MAX_USUARIOS){
		usuarios.usuario[usuarios.contador] = new tUsuario(usuario);
		usuarios.contador++;
		ordenar (usuarios);
		esAniadir = true;
	}
	return esAniadir;
}

bool buscarUsuario (const tListaUsuarios & usuarios, string id, int & posicion){ // busqueda binaria
	int ini = 0, fin = usuarios.contador - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado){
		mitad = (ini + fin) / 2;
		if(id < usuarios.usuario[mitad]->nombre){
			fin = mitad - 1;
		}
		else if(usuarios.usuario[mitad]->nombre < id){
			ini = mitad + 1;
		}
		else{
			encontrado = true;
		}			
	}
	if (encontrado) posicion = mitad;
	else posicion = ini;
	return encontrado;
}

void ordenar (tListaUsuarios & usuarios){
	tUsuarioPtr nuevo;
	int posicion = 0;
	nuevo = usuarios.usuario[usuarios.contador - 1];	
	while ((posicion < usuarios.contador -1) && !(usuarios.usuario[posicion]->nombre > nuevo->nombre)){
		posicion ++;
	}
	for (int j = usuarios.contador - 1; j > posicion; j--){
		usuarios.usuario[j] = usuarios.usuario[j - 1];
	}
	usuarios.usuario[posicion] = nuevo;
}

void destruir (tListaUsuarios & usuarios){
	for (int i = 0; i < usuarios.contador; i++){
		destruir (usuarios.usuario[i]->recibidos);
		destruir (usuarios.usuario[i]->enviados);
		delete usuarios.usuario[i];
	}
}

