#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

#include"gestor.h"

void inicializar (tGestor & gestor, string dominio){
	gestor.dominio = dominio;
}

bool arrancar (tGestor & gestor, string dominio){
	inicializar (gestor, DOMINIO);
	return (cargar(gestor.usuarios, dominio) & cargar (gestor.correos, dominio));
}
 
void apagar(const tGestor & gestor){
	system("cls");
	cout << " Cerrando gestor de correo " << gestor.dominio << endl;
	guardar (gestor.usuarios, gestor.dominio);
	guardar (gestor.correos, gestor.dominio);
}

bool crearCuenta(tGestor & gestor){
	tUsuario usuario;
	bool ok = false;
	int posicion;
	string id, contrasenia;
	
	cout << "Selecciona tu id: ";
	cin >> id;
	cin.sync();
	id = id + "@" + gestor.dominio;
	while(buscarUsuario (gestor.usuarios,id, posicion)){
		cout << "Id de usuario no disponible" << endl;
		cout << "Escoja otra Id: ";
		cin >> id;
		cin.sync();
		id = id + "@" + gestor.dominio;
	}
	cout << "Selecciona una contrasenia: ";
	cin >> contrasenia;
	cin.sync();
	inicializar(usuario, id, contrasenia);
	if (aniadir(gestor.usuarios, usuario)){
		ok = true;
		cout << "Se creo correctamente su cuenta" << endl;
	    cout << "Iniciando sesion en " << gestor.dominio << endl;
	    buscarUsuario(gestor.usuarios, id, gestor.usuarioActivo);
	} 
	else cout << "No se puede aniadir nuevos usuarios" << endl;
	system("pause");
	return ok;
}

bool iniciarSesion (tGestor & gestor){
	system("cls");
	bool ok = false;
	int posicion;
	string id, contrasenia;
	
	cout << "Bienvenido a tu correo " << gestor.dominio << endl;
	cout << "Introduce tu direccion de correo: ";
	cin >> id;
	cin.sync();
	if (buscarUsuario(gestor.usuarios, id, posicion)){
		cout << "Introduce tu contrasenia: ";
		cin >> contrasenia;
		if (validarContrasenia(*gestor.usuarios.usuario[posicion], contrasenia)){
			gestor.usuarioActivo = posicion;
			cout << "Iniciando sesion de " << gestor.usuarios.usuario[posicion]->nombre << endl;;
			ok = true;
		}
		else cout << "contrasenia incorrecta" << endl;
	}
	else {
		cout << "Usuario no existe" << endl;
	}
	system("pause");
	return ok;
}

void leerCorreo(tGestor & gestor, tListaRegistros & listaReg){
	tCorreo respuestaMail;
	string fila, cabecera;
	int mail, opcion, posicion;
	
	cout << "Indique el nuemero del correo: ";
	cin >> mail;
	system("cls");
	if (mail > 0 && mail <= listaReg.contador){
		buscar (gestor.correos, listaReg.registro[mail-1].idcorreo, posicion);
		cout << aCadena(gestor.correos.correo[posicion]);
		correoLeido (listaReg, listaReg.registro[mail-1].idcorreo);
		lineaDeSeparacion ();
		cout << "Selecciona una opcion:" << endl;
		cout << "   " << "1.- Contestar correo" << endl;
		cout << "   " << "0.- Volver a la bandeja" << endl;
		lineaDeSeparacion ();
		cout << "Opcion: ";
		cin >> opcion;
		if (opcion == 1){
			correoContestacion (gestor.correos.correo[posicion], respuestaMail, gestor.correos.correo[posicion].destinatario);
			enviarCorreo (gestor, respuestaMail);
		}		
	}	
}

void enviarCorreo (tGestor & gestor, const tCorreo & correo){
	tRegistro registro;
	int posicion;
	if (buscarUsuario (gestor.usuarios, correo.destinatario, posicion)){
		insertar(gestor.correos, correo);
		registro.leido = true;
		registro.idcorreo = correo.identificador;
		insertar (gestor.usuarios.usuario[gestor.usuarioActivo]->enviados, registro);
		registro.leido = false;
		insertar (gestor.usuarios.usuario[posicion]->recibidos, registro);
		cout << "Correo enviado correctamente" << endl;
    }
	else {
		cout << "Destinatario no existe" << endl;
	}
}

void borrarCorreo(tGestor & gestor, tListaRegistros & listaReg){
	int opcion;
		
	cout << "Selecciona el numero del correo que deseas borrar: ";
	cin >> opcion;	
	if (opcion > 0 && opcion <= listaReg.contador){
		if (borrar (listaReg, listaReg.registro[opcion - 1].idcorreo)){
			cout << "El mensaje se ha eliminado correctamente" << endl;	
		}
		else{
			cout << "El correo seleccionado no existe" << endl;
		}
	}
	system("pause");
}

void lecturaRapida(tGestor & gestor, tListaRegistros & listaReg){
	system ("cls");
	int posicion;
	tListaCorreos aux;
	aux = gestor.correos;
	ordenar_AF (aux);
	for (int i = 0; i < listaReg.contador; i++){
		if (!listaReg.registro[i].leido){
			buscar (aux, listaReg.registro[i].idcorreo, posicion);
			cout << aCadena(aux.correo[posicion]);
			lineaDeSeparacion();
			correoLeido(gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos, listaReg.registro[i].idcorreo);
		}
	}
	system("pause");
}

void gestionarSesion(tGestor & gestor){
	tCorreo nuevoCorreo;
	bool esEntrada = true;
	int opcion;
	do{	
		system("cls");
		mostrarInterFazUsuario(gestor,esEntrada);
		cin >> opcion;
		if (opcion == 1){
			if (esEntrada){
				leerCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos);
			}
			else{
				leerCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->enviados);
			}
		}
		else if (opcion == 2){
			system("cls");
			correoNuevo (nuevoCorreo, gestor.usuarios.usuario[gestor.usuarioActivo]->nombre);
			enviarCorreo(gestor, nuevoCorreo);
		}
		else if (opcion == 3){
			if(esEntrada){
				borrarCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos);
			}
			else{
				borrarCorreo (gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->enviados);
			}			
		}
		else if (opcion == 4){
			esEntrada = !esEntrada;
		}
		else if (opcion == 5){
			lecturaRapida (gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos);
		}
	} while (opcion != 0);
	system ("cls");
}

void mostrarInterFazUsuario (tGestor & gestor, bool esEntrada){
	system ("cls");
	cout << "Sesion de " << gestor.usuarios.usuario[gestor.usuarioActivo]->nombre << endl;
	for(int i = 0; i < 30; i++){
		cout << "-";
	}
	cout << "Bandeja de ";
	if (esEntrada){
		cout << "entrada";
		lineasDeCabecera ();
	} 
	else{
		cout << "salida-";
		lineasDeCabecera ();
	} 
	lineaDeSeparacion ();
	if (!esEntrada){
		cout << "L" << setw(2) << "N" << setw(15) << "DESTINATARIO" << setw(25) << "ASUNTO" << setw(35) << "FECHA" << endl;
	}
	else cout << "L" << setw(2) << "N" << setw(10) << "EMISOR" << setw(30) << "ASUNTO" << setw(35) << "FECHA" << endl;
	lineaDeSeparacion ();
	verBandeja (gestor,esEntrada);
	lineaDeSeparacion ();
	mostrarMenu(esEntrada);	
}

void verBandeja (const tGestor & gestor, bool esEntrada){
	int posicion;
	tUsuarioPtr usuario = gestor.usuarios.usuario[gestor.usuarioActivo];
	
	if (!esEntrada){
		for (int i = 0; i < usuario->enviados.contador; i++){
			if (buscar (gestor.correos, usuario->enviados.registro[i].idcorreo, posicion)){
				cout << setw(2) << i + 1 << " " << gestor.correos.correo[posicion].destinatario << setw(25) << gestor.correos.correo[posicion].asunto << setw(30) << mostrarSoloDia (gestor.correos.correo[posicion].fecha) << endl;
			}
		}
	}
	else{
		for (int i = 0; i < usuario->recibidos.contador; i++){
			if (usuario->recibidos.registro[i].leido){
				cout << " ";
			}
			else {
				cout << "*";
			}
			if (buscar (gestor.correos, usuario->recibidos.registro[i].idcorreo, posicion)){
				cout << setw(2) << i + 1 << " " << gestor.correos.correo[posicion].emisor << setw(25) << gestor.correos.correo[posicion].asunto << setw(30)<< mostrarSoloDia (gestor.correos.correo[posicion].fecha) << endl;
			}
		}
	}
}

void mostrarMenu (bool esEntrada){
	cout << endl;
	cout << "Selecciona una opcion: " << endl;
	cout << "" << endl;
	cout << "1.- Leer correo" << endl;
	cout << "2.- Enviar correo" << endl;
	cout << "3.- Eliminar correo" << endl;
	cout << "4.- Ver bandeja de ";
	if (esEntrada) cout << "salida" << endl;
	else cout << "entrada" << endl;
	cout << "5.- Lectura rapida de correos no leidos" << endl;
	cout << "0.- Cerrar Sesion Activa" << endl;
	lineaDeSeparacion ();
	cout << "Opcion: ";
}

void lineaDeSeparacion (){
	for (int i = 0; i < 80; i++){
		cout << "-";
	}
}

void lineasDeCabecera (){
	for(int i = 0; i < 32; i++){
		cout << "-";
	}
}
