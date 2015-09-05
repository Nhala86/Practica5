#ifndef LISTACORREOS_H
#define LISTACORREOS_H

using namespace std;

#include"correo.h"

// Declaro las constantes del maximo de correos que puede tener la lista de correos y el nombre del .txt

const int MAIL_INICIAL = 1;
const string mailCorreo = "ListaCorreo.txt";

/**
** Creo la estructura que tiene la lista de correos, con tantas posiciones como indica la constante
** LLama a tCorreo, ya que cada posicion tiene un tipo correo
** Ademas tiene un contador
**/
typedef struct{
	tCorreo* correo; // apunto a tCorreo como puntero
	int contador;
	int capacidad;
}tListaCorreos;

/**
** Inicializo la lista
**/

void inicializar(tListaCorreos & correos, int capacidad);

/**
** Implementa la carga de la lista de correos desde el fichero de correos de nombre <NombreDominio>_correos.txt
**/

bool cargar(tListaCorreos & correos, string dominio);

/**
** Implementa el guardado de la lista de correos en el fichero de correos de nombre <NombreDominio>_ correos.txt
** Guarda en fichero la lista de correos
**/

void guardar (const tListaCorreos & correos, string dominio);

/**
** Dado un correo, si hay espacio en la lista, lo coloca en la posición correspondiente de acuerdo con su identificador y devuelve true
** Si no lo ha podido colocar devuelve false
**/

void insertar(tListaCorreos & correos, const tCorreo & correo);

/**
** Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true
** Si no existe en la lista, la posición que le correspondería y el valor false
**/

bool borrar(tListaCorreos &correos, string id);

bool buscar (const tListaCorreos & correos, string id, int & pos);

/**
** Dada una lista de correos la devuelve ordenada por asunto y fecha
** Como es una clave de ordenación doble, habrá que redefinir el operador de comparación en el módulo que corresponda
**/

void ordenar_AF(tListaCorreos & correos);

/**
** Elimina de la memoria la lista de correos
**/

void destruir (tListaCorreos & correos);

/**
** Genera una lista de correos con una dimension (que puede ser mayor, igual o menor a la antigua) y en ella inserta todos los correos de la lista antigua
** Y al finalizar pisa la antigua lista con la nueva
**/

void redimensionar (tListaCorreos & correos);



#endif
