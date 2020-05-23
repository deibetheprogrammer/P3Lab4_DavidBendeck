#include <iostream>
#include <vector>
#include <string>
#include "Persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using std::cout;
using std::cin;
using std::endl;

//Funcion para cifrar/decifrar el cifrado Cesar
string cesar(string, int, int);

int main(int argc, char** argv) {
	
	vector<Persona> personas;
	
	bool loop = true;
	while(loop) {
	
		cout<<"********MENU********" << "\n\n"
			<<"1) Registrarse " << endl
			<<"2) Ingresar " << endl
			<<"3) Salida " << endl
			<<"Su eleccion: ";
	
		int opcion;
		cin >> opcion;
	
		while (!cin || (opcion < 1 || opcion > 3)) {
			cin.clear ();    // Restore input stream to working state
    		cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
   		 	cout << "Por favor, ingrese una opcion valida: ";
    		cin >> opcion; 
		}
		
		switch(opcion) {
			case 1: {
				
				string nombre,apellido,clave;
				
				cout << "\n\n"
					 << "***REGISTRO***" << "\n\n"
					 << "Su nombre: ";
				
				cin >> nombre;
				
				cout << "Apellido: ";
				
				cin >> apellido;
				
				cout << "Clave: ";
				
				cin >> clave;
				
				Persona *p = new Persona(nombre,apellido,clave);
				
				personas.push_back(*p);
				
				break;
			}
			case 2: {
				
				Persona* actual = nullptr;
				
				bool acceso = false;
				string nombre,clave;
				
				cout << "\n\n"
					 << "*** LOG IN ***" <<"\n\n"
					 << "Ingrese su nombre: ";
				cin >> nombre;
					 
				cout << "Ingrese su clave: ";
				cin >> clave;
				
				for(int i = 0; i < personas.size(); i++) {
					Persona p = personas[i];
					if(p.nombre == nombre && p.clave == clave){
						acceso = true;
						actual = &personas[i];
						break;
					}
				}	 
				
				if(acceso) {
					
					bool logged = true;
					
					while(logged) {

						cout << "\n\n"
							 << "***Menu de usuario***" << "\n\n"
							 << "1) Enviar mensajes " << endl
							 << "2) Recibir mensajes " << endl
							 << "3) Ver mi llave " << endl
							 << "4) Sign out" << endl
							 << "Ingrese su opcion: ";
						 
						int choice;
						cin >> choice;
					
						while (!cin || (choice < 1 || choice > 4)) {
							cin.clear ();    // Restore input stream to working state
    						cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
   		 					cout << "Por favor, ingrese una opcion valida: ";
    						cin >> choice; 
						}
					
						switch(choice) {
							case 1: {
								
								cout << "\n\n"
									 << "ENVIAR MENSAJE" << "\n\n"
									 << "Lista de usuarios: " << "\n";
									 
								int indice = 1;
								for (Persona p : personas) {
									cout << indice << " : " << p.nombre << endl;
									indice++;
								}
								
								int indiceD;
								cout << "Escoja el indice de su destinatario: ";
								cin	 >> indiceD;
								
								while (!cin || (indiceD < 1 || indiceD > personas.size())) {
									cin.clear ();    // Restore input stream to working state
    								cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
   		 							cout << "Por favor, ingrese un indice valido: ";
    								cin >> indiceD; 
								}
								
								Persona* destinatario = nullptr;
								destinatario = &personas[indiceD-1];
								
								string mensaje;
								cout << endl
									 << "Ingrese su mensaje: " << endl;
								cin >> mensaje;
								
								//encriptar
								mensaje = cesar(mensaje,destinatario->llave,1);
								//cout << "Longitud: " << mensaje.size() << endl;
								//cout << "Mensaje: "<< mensaje << endl;
								//cout << "Destinatario: " << destinatario->nombre << endl;
								
								//enviar
								destinatario->mRecibidos.push_back(actual->nombre);
								destinatario->mRecibidos.push_back(mensaje);
								cout << endl
									 << "Mensaje enviado con exito"
									 << "\n\n";
								
								//cout << "Mensaje: " << destinatario->mRecibidos[1] << endl;
							
								break;
							}
							
							case 2: {
								
								cout << "\n\n"
									 << "VER MENSAJES" << "\n\n"
									 << "Lista de mensajes: " << endl;
									 //<< "Actual: " << actual->nombre << endl
									 //<< "Size: " << actual->mRecibidos.size() << endl;
								
								for (int i = 0; i < actual->mRecibidos.size(); i+= 2) {
									
									cout << i/2 << " -> "
										 << "De: " << actual->mRecibidos[i] << " | "
										 << "Mensaje: " << actual->mRecibidos[i+1] << endl;
								}
								cout << endl
									 << "Elija su mensaje: ";
								int index;
								cin >> index;
								
								while (!cin || (index < 0 || index >= actual->mRecibidos.size()/2)) {
									cin.clear ();    // Restore input stream to working state
    								cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
   		 							cout << "Por favor, ingrese un indice valido: ";
    								cin >> index; 
								}
								
								//desencriptar
								string respuesta;
								respuesta = cesar(actual->mRecibidos[index*2+1],actual->llave,-1);
								
								//mostrar
								cout << endl
									 << "El mensaje es: " << endl
									 << respuesta << "\n\n";
								
								break;
							}
						
							case 3: {
								
								cout << "\n"
									 << "Su llave es: "
									 << actual->llave
									 << "\n\n";
							
								break;
							}
							
							case 4: {
								cout << "\n\n"
									 << "Signing out..."
									 << "\n\n";
								logged = false;
								break;
							}
							
						}
					}
					
				} else {
					cout << "Acceso denegado";
				}
				
				break;
			}
			case 3: {
				cout << "Saliendo ...";
				loop = false;
				break;
			}
		}
	}
	
	personas.clear();
	return 0;
	
}

//Funcion para cifrar/decifrar el cifrado Cesar
string cesar(string mensaje, int llave, int modo) {
	
	if (llave == 0) {
		return mensaje;
	}
	
	string respuesta = "";
	int modo2 = modo * llave;
	
	for (int i = 0; i < mensaje.size(); i += llave) {
		for(int j = i; j < i + llave && j < mensaje.size(); j++) {
			respuesta += mensaje[j] + modo2;
		}
		modo2 = -modo2;
	}
	
	return cesar(respuesta,llave-1,modo);
}







