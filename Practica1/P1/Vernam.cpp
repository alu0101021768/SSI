#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
using namespace std;

string to_bin(string mensaje) {
    string aux;
      for (int i = 0; i < mensaje.size(); ++i)
    {
        aux += bitset<8>(mensaje[i]).to_string();
    }
    return aux;
}

string xor_add(string mensaje_bin , string clave) {
    string result;
    for (int i = 0; i < mensaje_bin.size(); i++)
    {
        if (mensaje_bin[i] == clave[i])
            result += '0';
        else
            result += '1';
    }
    return result;
}

string bin_to_alpha(string mensaje_cifrado) {
    string result;
    istringstream palabra(mensaje_cifrado);
    bitset<8> letra;
    while (palabra >> letra)
    {
        result += char(letra.to_ulong());   // Pasamos cada letra en binario a ascii
    }
    return result;
}

int main()
{

    string mensaje, clave, result, mensaje_bin = "";
    
    // Leemos por teclado el mensaje
    cout << "Introduzca el mensaje deseado : ";
    cin >> mensaje;
    
    // Pasamos el mensaje a binario
    mensaje_bin = to_bin(mensaje);
    cout << "Mensaje original en binario   : " << mensaje_bin << endl;

    // Leemos por teclado la clave
    cout << "Introduzca la clave aleatoria : ";
    cin >> clave;

    // Se realiza una XOR entre el mensaje original y la clave , cifrándolo
    result = xor_add(mensaje_bin , clave);
    cout << "Mensaje cifrado en binario : " << result << endl;

    string aux = result;
    result.clear();
    // Se pasa el mensaje cifrado en binario a ascii
    result = bin_to_alpha(aux); 
    cout << "Mensaje cifrado : " << result << endl;
    
    // Se vuelve a pasar a binario el mensaje cifrado
    string cifrado = to_bin(result);

    // Se realiza una XOR entre el mensaje cifrado en binario y la clave 
    string resultado = xor_add(cifrado , clave);

    cout << "-------------------------------------------------" << endl;
    cout << "Mensaje " << result << " + " << "clave aleatoria  : " << clave << endl;
    result.clear();
    
    // Se pasa el resultado de la XOR a ascii , descifrándolo
    result = bin_to_alpha(resultado);  
    cout << "Mensaje final descifrado      : " << result << endl;
}

