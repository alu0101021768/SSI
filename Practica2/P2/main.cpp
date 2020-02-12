#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Definimos el alfabeto sin Ñ y con W
const std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int modulo = 26;

int find_value(char caracter) {
    int val = alfabeto.find(caracter);
    if (val == std::string::npos) {
        std::cout << "Carácter " << caracter << " no encontrado" << std::endl;   
    }
    return val;
}

void read_mensaje(std::string& mensaje) {
    std::cout << "Introduzca el mensaje : ";
    getline(std::cin, mensaje);

}

void read_clave(std::string& clave)
{
    std::cout << "Introduzca la clave : ";
    std::cin >> clave;
   
}

std::string add_key_cifrado(std::string mensaje , std::string clave) {

    std::string resultado;
    resultado.resize(mensaje.size());
    int tam_msg = mensaje.size();
    int tam_clave = clave.size();

    int cont = 0;
    while (tam_clave != tam_msg) {
        clave += clave[cont];
        cont++ , tam_clave++;
        if (cont == tam_clave)
            cont = 0;
    }
    for (int i = 0; i < tam_msg; i++) {
        resultado[i] = alfabeto[(find_value(mensaje[i]) + find_value(clave[i])) % 26];
    }
    return resultado;

}

std::string add_key_descifrado(std::string mensaje, std::string clave)
{

    std::string resultado;
    resultado.resize(mensaje.size());
    int tam_msg = mensaje.size();
    int tam_clave = clave.size();

    int cont = 0;
    while (tam_clave != tam_msg)
    {
        clave += clave[cont];
        cont++, tam_clave++;
        if (cont == tam_clave)
            cont = 0;
    }
    for (int i = 0; i < tam_msg; i++)
    {
        resultado[i] = alfabeto[((find_value(mensaje[i]) + find_value(clave[i])) + 26) % 26];
    }
    return resultado;
}

void delete_spaces(std::string& mensaje) {
    mensaje.erase(remove_if(mensaje.begin(), mensaje.end(), isspace), mensaje.end());
    std::cout << "Mensaje sin espacios : " << mensaje << std::endl;
}

void cifrado(std::string& resultado , std::string mensaje , std::string clave) {
    resultado = add_key_cifrado(mensaje, clave);
    std::cout << "Mensaje cifrado : " << resultado << std::endl;
}

void descifrado(std::string& resultado , std::string mensaje , std::string clave) {
    resultado = add_key_descifrado(mensaje, clave);
    std::cout << "Mensaje cifrado : " << resultado << std::endl;
}

int main () {

    std::string mensaje;
    std::string clave;
    std::string resultado;
    
    bool salir = false;
    int opcion;

    std::cout << "Práctica 2 - Cifrado de Vigenere" << std::endl;
    read_mensaje(mensaje);
    read_clave(clave);
    std::cout << "1.Cifrado" << std::endl;
    std::cout << "2.Descifrado" << std::endl;
    std::cout << "3.Salir" << std::endl;
    std::cout << "Seleccione una opción : ";
    std::cin >> opcion;
    switch (opcion)
    {
    case 1:
        delete_spaces(mensaje);
        cifrado(resultado, mensaje, clave);
        break;
    case 2:
        delete_spaces(mensaje);
        descifrado(resultado, mensaje, clave);
        break;
    case 3:
        salir = true;
        break;
    default:
        std::cout << "Opción no válida" << std::endl;
        break;
    }
    std::cout << "---------------------------------------------" << std::endl;
}
    