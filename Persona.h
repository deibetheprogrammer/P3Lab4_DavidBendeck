#ifndef PERSONA_H
#define PERSONA_H
#include <vector>
#include <string>

using namespace std;

class Persona
{
	public:
		string nombre,apellido,clave;
		int llave;
		vector<string> mRecibidos;
		
		Persona();
		Persona(string,string,string);
		
		~Persona();
	protected:
};

#endif
