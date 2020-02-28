#include "RC4.h"



int main() {

	// Recogemos la semilla
	vector<int> semilla;
	int tam_s , s;
	cout << endl << "Introduzca tamaño de la semilla" << endl;
	cin >> tam_s; 
	cout << endl << "Introduzca la semilla" << endl;
	while (semilla.size() != tam_s) {
		cin >> s;
		semilla.push_back(s);
	}

	// Igual para el mensaje
	vector<int> mensaje;
	int tam_m , m;
	cout << "Introduzca el tamaño del mensaje" << endl;
	cin >> tam_m;
	cout << "Introduzca el mensaje" << endl;
	while (mensaje.size() != tam_m)
	{
		cin >> m;
		mensaje.push_back(m);
	}

	// Ahora queda cifrar el mensaje
	RC4 objeto(semilla);
	//write(cout , semilla);
	//write(cout , mensaje);
	return 0;

}
