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

std::string add_key(std::string mensaje , std::string clave) {

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

int main () {

    
    // leemos el mensaje por teclado
    std::string mensaje;
    std::cout << "Introduzca el mensaje : ";
    getline (std::cin , mensaje);

    // Mensaje sin espacios
    mensaje.erase(remove_if(mensaje.begin() , mensaje.end() , isspace) , mensaje.end());
    std::cout << "Mensaje sin espacios : " << mensaje << std::endl;
    

    // Leemos la clave por teclado
    std::string clave;
    std::cout << "Introduzca la clave : ";
    std::cin >> clave;
    

    // Sumamos el mensaje con la clave , de manera que dividimos el mensaje original en trozos 
    // del mismo tamaño que la clave , y sumamos las posiciones 0 de cada trozo con la 0 de la clave ,
    // luego la 1 con la 1 y asi sucesivamente
    
    std::string resultado = add_key(mensaje , clave);
    //std::cout << "valor de msg : " << find_value(mensaje[1]) << std::endl;
    //std::cout << "valor de clave : " << find_value(clave[1]) << std::endl;
    //std::cout << "MODULO DE SUMA : " << alfabeto[26 % modulo] << std::endl;
    

    // Mensaje cifrado
    std::cout << "Mensaje cifrado : " << resultado << std::endl;
}
    