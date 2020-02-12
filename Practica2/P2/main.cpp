#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Definimos el alfabeto sin Ñ y con W
const std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Definimos el modulo
const int modulo = 26;

// Busca en el alfabeto el valor de la letra
int find_value(char caracter) 
{
    int val = alfabeto.find(caracter);
    if (val == std::string::npos) {
        std::cout << "Carácter " << caracter << " no encontrado" << std::endl;   
    }
    return val;
}

// Lee por teclado el mensaje
void read_mensaje(std::string& mensaje) 
{
    std::cout << "Introduzca el mensaje : ";
    getline(std::cin, mensaje);

}

// Lee por teclado la clave
void read_clave(std::string& clave)
{
    std::cout << "Introduzca la clave : ";
    std::cin >> clave;
   
}

// Suma el mensaje con la clave 
std::string add_key_cifrado(std::string mensaje , std::string clave) 
{
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

// Resta al mensaje la clave
std::string subtraction_key_descifrado(std::string mensaje, std::string clave) 
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
        resultado[i] = alfabeto[((find_value(mensaje[i]) - find_value(clave[i])) + 26) % 26];
    }
    return resultado;
}


// Borra los espacios
void delete_spaces(std::string& mensaje) {
    mensaje.erase(remove_if(mensaje.begin(), mensaje.end(), isspace), mensaje.end());
    std::cout << "Mensaje sin espacios : " << mensaje << std::endl;
}

// llama a la función add key para cifrar
void cifrado(std::string& resultado , std::string mensaje , std::string clave) {
    resultado = add_key_cifrado(mensaje, clave);
    std::cout << "Mensaje cifrado : " << resultado << std::endl;
}

// llama a la función SUBSTRACT key para descifrar
void descifrado(std::string& resultado , std::string mensaje , std::string clave) {
    resultado = subtraction_key_descifrado(mensaje, clave);
    std::cout << "Mensaje descifrado : " << resultado << std::endl;
}

int main () {

    std::string mensaje;
    std::string clave;
    std::string mensaje_cifrado;
    std::string resultado;

    std::cout << "------------------------------------" << std::endl;
    std::cout << "| Práctica 2 - Cifrado de Vigenere |" << std::endl;
    std::cout << "------------------------------------" << std::endl;
  
    read_mensaje(mensaje);
    read_clave(clave);

    delete_spaces(mensaje);

    cifrado(mensaje_cifrado, mensaje, clave);

    descifrado(resultado, mensaje_cifrado, clave);

    std::cout << "-----------------------------------" << std::endl;
}
    