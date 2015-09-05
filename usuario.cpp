#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

#include"usuario.h"

bool cargar(tUsuario & usuario, ifstream & archivo){
	bool ok = true;
	archivo >> usuario.nombre;
	if (usuario.nombre != CENTINELA){
		archivo >> usuario.contrasenia;
		cargar(usuario.recibidos, archivo);
		cargar(usuario.enviados, archivo);
	}
	else{
		ok = false;
	}
	return ok;
}

void guardar(const tUsuario & usuario, ofstream & archivo){
	archivo << usuario.nombre << endl;
	archivo << usuario.contrasenia << endl;
	archivo << usuario.recibidos.contador << endl;
	if (usuario.recibidos.contador != 0){
		for (int i = 0; i < usuario.recibidos.contador; i++){
			archivo << usuario.recibidos.registro[i].idcorreo << " " << usuario.recibidos.registro[i].leido << endl;
		}
	}
	archivo << usuario.enviados.contador << endl;
	if (usuario.enviados.contador != 0){
		for (int i = 0; i < usuario.enviados.contador; i++){
			archivo << usuario.enviados.registro[i].idcorreo << " " << usuario.enviados.registro[i].leido << endl;
		}
	}
}

void inicializar(tUsuario & usuario, string id, string contrasenia){
	usuario.nombre = id;
	usuario.contrasenia = contrasenia;
	inicializar (usuario.recibidos, REG_INICIAL);
	inicializar (usuario.enviados, REG_INICIAL);
}

bool validarContrasenia(const tUsuario & usuario, string contrasenia){
	bool ok = false;
	if (contrasenia == usuario.contrasenia){
		ok = true;
	}
	return ok;
}
