#include "RC4.h"

// Write para escribir vectores de enteros
ostream& write(ostream &os, vector<int> v)
{
	os << "[ ";
	for (int i = 0; i < v.size(); i++)
	{
		if (i != v.size() - 1)
			os << v[i] << " , ";
		else
			os << v[i] << " ]" << endl;
	}
	return os;
}

int main() {

	// Recogemos la semilla
	vector<int> semilla;
	int tam_s , s;
	cout << "===========================================" << endl;
	cout << "Introduzca tamaño de la semilla: ";
	cin >> tam_s; 
	semilla.resize(tam_s);
	cout << "Introduzca la semilla" << endl;
	for (int i = 0; i < semilla.size(); i++) {
		cout << "\t-> Semilla[" << i << "] = ";
		cin >> s;
		semilla[i] = s;
	}

	// Igual para el mensaje
	vector<int> mensaje;
	int tam_m , m;
	cout << "===========================================" << endl;
	cout << "Introduzca el tamaño del mensaje: ";
	cin >> tam_m;
	mensaje.resize(tam_m);
	cout << "Introduzca el mensaje" << endl;
	for (int i = 0; i < mensaje.size(); i++)
	{
		cout << "\t-> Mensaje[" << i << "] = ";
		cin >> m;
		mensaje[i] = m;
	}
	cout << "===========================================" << endl;
	// Ahora queda cifrar el mensaje
	RC4 objeto(semilla);

	vector<int> mensaje_cifrado = objeto.Cifrado(mensaje);

	cout << "-> Semilla: ";
	write(cout, semilla);

	cout << "-> Mensaje : ";
	write(cout, mensaje);

	cout << "-> Secuencia cifrante : ";
	write(cout, objeto.get_secuencia());

	cout << "-> Mensaje cifrado: ";
	write(cout, mensaje_cifrado);
	cout << "===========================================" << endl;
	return 0;
}
