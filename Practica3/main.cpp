#include "RC4.h"

const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string reset("\033[0m");

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
	cout << red << "===========================================" << reset << endl;
	cout << "Introduzca tamaño de la semilla: ";
	cin >> tam_s; 
	semilla.resize(tam_s);
	cout << green << "Introduzca la semilla" << endl;
	for (int i = 0; i < semilla.size(); i++) {
		cout << green << "-> Semilla[" << i << "] = ";
		cin >> s;
		semilla[i] = s;
	}

	// Igual para el mensaje
	vector<int> mensaje;
	int tam_m , m;
	cout << red << "===========================================" << reset << endl;
	cout << reset <<  "Introduzca el tamaño del mensaje: ";
	cin >> tam_m;
	mensaje.resize(tam_m);
	cout << green << "Introduzca el mensaje" << endl;
	for (int i = 0; i < mensaje.size(); i++)
	{
		cout << green <<  "-> Mensaje[" << i << "] = ";
		cin >> m;
		mensaje[i] = m;
	}
	cout << reset << red << "===========================================" << reset << endl;

	// Ahora queda cifrar el mensaje
	RC4 objeto(semilla);

	vector<int> mensaje_cifrado = objeto.Cifrado(mensaje);
	vector<int> mensaje_descifrado = objeto.Descifrado(mensaje_cifrado);

	// Mostramos los datos recogidos , la secuencia cifrante generada asi como el mensaje cifrado
	cout << green <<  "-> Semilla: ";
	write(cout, semilla);

	cout << "-> Mensaje : ";
	write(cout, mensaje);

	cout << "-> Secuencia cifrante : ";
	write(cout, objeto.get_secuencia());

	cout << "-> Mensaje cifrado: ";
	write(cout, mensaje_cifrado);

	cout << "-> Mensaje descifrado: ";
	write(cout, mensaje_descifrado);
	cout << reset << red << "===========================================" << reset << endl;
	return 0;
}
