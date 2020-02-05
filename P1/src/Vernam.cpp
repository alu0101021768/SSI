#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
using namespace std;

int main()
{

    string mensaje, clave, result, mensaje_bin = "";

    cout << "Introduzca el mensaje deseado : ";
    cin >> mensaje;

    for (int i = 0; i < mensaje.size(); ++i)
    {
        mensaje_bin += bitset<8>(mensaje[i]).to_string();
    }

    cout << "Mensaje original en binario   : " << mensaje_bin << endl;
    cout << "Introduzca la clave aleatoria : ";
    cin >> clave;

    for (int i = 0; i < mensaje_bin.size(); i++)
    {
        if (mensaje_bin[i] == clave[i])
            result += '0';
        else
            result += '1';
    }
    cout << "Mensaje original ya cifrado   : " << result << endl;
    istringstream in(result);
    bitset<8> fin;
    result.clear();
    while (in >> fin)
    {
        result += char(fin.to_ulong());
    }
    cout << "Mensaje cifrado descifrado    : " << result << endl;
    string aux = result;
    mensaje_bin.clear();
    for (int i = 0; i < result.size(); ++i)
    {
        mensaje_bin += bitset<8>(result[i]).to_string();
    }

    result.clear();
    for (int i = 0; i < mensaje_bin.size(); i++)
    {
        if (mensaje_bin[i] == clave[i])
            result += '0';
        else
            result += '1';
    }
    cout << "-------------------------------------------------" << endl;
    cout << "Mensaje " << aux << " + " << "clave aleatoria  : " << mensaje_bin << endl;
    istringstream last(result);
    bitset<8> fin2;
    result.clear();
    while (last >> fin2)
    {
        result += char(fin2.to_ulong());
    }
    cout << "Mensaje final descifrado      : " << result << endl;
}

// Otra opcion
//for (int i = 0; i < mensaje_bin.size(); i++)
//     result[i] += (mensaje_bin[i] ^ clave[i]);