#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Para ejecutar el programa , haga make , y luego ./cifrado

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



string randomizer(int n) {
    string aux;
    string clave;
    srand( time( NULL ) );  //  using the time seed from srand explanation 

    for (int i = 0; i < n ; i++) {
           aux.push_back(char(rand() % 2)+48);
    }
    return aux;
}

string to_ascii(string mensaje) {
    for (int i = 0; i < mensaje.size(); i++) {
        if (mensaje[i] < 32 || mensaje[i] > 126) {
            mensaje[i] %= (126-32) ;
            mensaje[i] += 32;
        }
    }
    return mensaje;
}

string bin_to_alpha(string mensaje_cifrado) {
    
    string result;
    istringstream palabra(mensaje_cifrado);
    bitset<8> letra;
    while (palabra >> letra)
    {
        result += char(letra.to_ulong());   // Pasamos cada letra en binario a ascii
    }

    return to_ascii(result);
}

void mostrar_crema(string cadena) {
    for (int i = 0; i < cadena.size(); i++)
    {
        /* code */
        cout << char(cadena[i]);
    }
    
}

int main()
{

    string mensaje, clave, result, mensaje_bin = "";
    int opcion;
    cout << "Cifrado de Vernam" << endl;
    cout << "1.Clave por teclado" << endl;
    cout << "2.Clave aleatoria" << endl;
    cout << "Selecciones una opcion : ";
    cin >> opcion;

    // Leemos por teclado el mensaje
    cout << "Introduzca el mensaje deseado : ";
    cin >> mensaje;
    
    // Pasamos el mensaje a binario
    mensaje_bin = to_bin(mensaje);
    cout << "Mensaje original en binario   : " << mensaje_bin << endl;

    if (opcion == 1) {
    // Leemos por teclado la clave
        cout << "Introduzca la clave aleatoria : ";
        cin >> clave;
    }
    else {
    // Generamos una clave aleatoriamente
        clave = randomizer(mensaje_bin.size());
        cout << "Clave aleatoria : " << clave << endl;
    } 
    // Se realiza una XOR entre el mensaje original y la clave , cifrándolo
    result = xor_add(mensaje_bin , clave);
    cout << "Mensaje cifrado en binario : " << result << endl;

    string aux = result;
    result.clear();
    // Se pasa el mensaje cifrado en binario a ascii
    result = bin_to_alpha(aux); 
    cout << "Mensaje cifrado : " << result << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << "Carácter : " << result[i] << "| Valor entero : " << int(result[i]) << endl; 
    }
    
    // Se vuelve a pasar a binario el mensaje cifrado
    //string cifrado = to_bin(result);

    // Se realiza una XOR entre el mensaje cifrado en binario y la clave 
    string resultado = xor_add(aux , clave);

    cout << "-------------------------------------------------" << endl;
    cout << "Mensaje " << result << " + " << "clave aleatoria  : " << clave << endl;
    result.clear();
    
    // Se pasa el resultado de la XOR a ascii , descifrándolo
    result = bin_to_alpha(resultado);  
    cout << "Mensaje final descifrado      : " << result << endl;

}

