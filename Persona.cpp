#include "Persona.h"
#include <stdlib.h>
#include <time.h>

Persona::Persona()
{

}

Persona::Persona(string nombre, string apellido, string clave)
{
	this->nombre = nombre;
	this->apellido = apellido;
	this->clave = clave;
	
	srand(time(0));
	
	this->llave = 1+rand()%15;
}

Persona::~Persona()
{
	
}
