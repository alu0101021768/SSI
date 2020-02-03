#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
using namespace std;

int main () {

    string mensaje, clave , result , mensaje_bin = "";

    cout << "Introduzca el mensaje: ";
    cin >> mensaje;
    

    for (int i = 0; i < mensaje.size(); ++i) {
        mensaje_bin += bitset<8>(mensaje[i]).to_string();
    }

    cout << "Mensaje original en binario : " << mensaje_bin << endl;
    cout << "Introduzca clave de " << mensaje_bin.size() << " bits : ";
    cin >> clave;
  
    for (int i = 0; i < mensaje_bin.size(); i++)
    {
        if (mensaje_bin[i] == clave[i])
            result += '0';
        else
            result += '1';
    }
    cout << "Mensaje cifrado de " << result.size() << " bits : " << result << endl;
    istringstream in(result);
    bitset<8> fin;
    result.clear();
    while (in >> fin ) {
        result += char(fin.to_ulong());
    }
    cout << "Pim pam descifrado : " << result << endl; 
}

// Otra opcion 
//for (int i = 0; i < mensaje_bin.size(); i++)
//     result[i] += (mensaje_bin[i] ^ clave[i]);