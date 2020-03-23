#include <iostream>
#include <bitset>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

ostream &write_registers(ostream &os , bitset<8> R1 , bitset<8> R2, bitset<8> R3)
{
    os << "Primer Byte: [";
    os << R1;
    os << "]\n";

    os << "Segundo Byte: [";
    os << R2;
    os << "]\n";

    os << "Multiplicación: [";
    os << R3;
    os << "]\n";
}

ostream& write(ostream&os , vector<int> v) {
    os << "Vector: [";
    for (int i = 0; i < v.size();i++) {
        os << v[i];
    }
    os << "]\n";
}

// Convierte un numero hexadecimal a decimal
int convert(string num)
{
    int len = num.size();
    int base = 1;
    int temp = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            temp += (num[i] - 48) * base;
            base = base * 16;
        }
        else if (num[i] >= 'A' && num[i] <= 'F')
        {
            temp += (num[i] - 55) * base;
            base = base * 16;
        }
    }
    return temp;
}

// Calcula el numero de unos de un numero binario
int numeroDeUnos(bitset<8> b) {
    int resultado = 0;
    for (int i = 0; i < b.size(); i++) 
        if (b[i] == 1)
            resultado++;
    return resultado;
}
// Calcula que numero tiene menor hamming , almacena las posiciones donde se encuentran sus unos y devuelve quien tiene mayor hamming
int menorHamming(bitset<8> byte1, bitset<8> byte2)
{
    int a = numeroDeUnos(byte1);
    int b = numeroDeUnos(byte2);
    if (a < b) 
        return 1;
    else 
        return 2;
    
}

// 
void shift(bitset<8> &v) {
    for (int i = v.size() - 1; i > 0; i--)
    {
        v[i] = v[i - 1];
    }
    v[0] = 0;
}

// Algoritmo AES
void multiplicacionAES(string primer_byte , string segundo_byte) {
    int A = convert(primer_byte);
    int B = convert(segundo_byte);
    bitset<8> byte1(A);
    bitset<8> original1 = byte1;
    bitset<8> byte2(B);
    bitset<8> original2 = byte2;
    bitset<8> byteAlgoritmo("00011011");
    int val = menorHamming(byte1 , byte2);
    bitset<8> resultado(0);
    if (val == 2) {
        for (int i = 0; i < resultado.size(); i++) {
            // Si el bit más significativo tiene un 1 antes del shifteo se le suma el byte del algoritmo
            if (byte1[byte1.size() - 1] == 1) {
                if (byte2[i] == 1)
                {
                    cout << "yeka1" << endl;
                    resultado = resultado ^ byte1;
                    cout << resultado << endl;
                }
                shift(byte1);
                byte1 = byte1 ^ byteAlgoritmo;
                //cout << byte1 << endl;

            }
            else {
                if (byte2[i] == 1)
                {
                    resultado = resultado ^ byte1;
                    cout << resultado << endl;
                }
                shift(byte1);
                //cout << byte1<<endl;

            }
        }
    }
    else
    {
        for (int i = 0; i < resultado.size(); i++) {
            // Si el bit más significativo tiene un 1 antes del shifteo se le suma el byte del algoritmo
            if (byte2[byte2.size() - 1] == 1) {
                if (byte1[i] == 1) {
                    cout << "yeka1" << endl;
                    resultado = resultado ^ byte2;
                    cout << resultado << endl;
                }
                shift(byte2);
                byte2 = byte2 ^ byteAlgoritmo;
            }
            else {
                if (byte1[i] == 1) {
                    resultado = resultado ^ byte2;
                    cout << resultado << endl;
                }
                shift(byte2);
            }
        }
    }
    write_registers(cout,original1,original2,resultado);
}

// Algoritmo Snow3g
// Algoritmo AES
void multiplicacionSNOW3G(string primer_byte, string segundo_byte)
{
    int A = convert(primer_byte);
    int B = convert(segundo_byte);
    bitset<8> byte1(A);
    bitset<8> original1 = byte1;
    bitset<8> byte2(B);
    bitset<8> original2 = byte2;
    bitset<8> byteAlgoritmo("10101001");
    int val = menorHamming(byte1, byte2);
    bitset<8> resultado(0);
    if (val == 2)
    {
        for (int i = 0; i < resultado.size(); i++)
        {
            // Si el bit más significativo tiene un 1 antes del shifteo se le suma el byte del algoritmo
            if (byte1[byte1.size() - 1] == 1)
            {
                if (byte2[i] == 1)
                {
                    cout << "yeka1" << endl;
                    resultado = resultado ^ byte1;
                    cout << resultado << endl;
                }
                shift(byte1);
                byte1 = byte1 ^ byteAlgoritmo;
                //cout << byte1 << endl;
            }
            else
            {
                if (byte2[i] == 1)
                {
                    resultado = resultado ^ byte1;
                    cout << resultado << endl;
                }
                shift(byte1);
            }
        }
    }
    else
    {
        for (int i = 0; i < resultado.size(); i++)
        {
            // Si el bit más significativo tiene un 1 antes del shifteo se le suma el byte del algoritmo
            if (byte2[byte2.size() - 1] == 1)
            {
                if (byte1[i] == 1)
                {
                    cout << "yeka1" << endl;
                    resultado = resultado ^ byte2;
                    cout << resultado << endl;
                }
                shift(byte2);
                byte2 = byte2 ^ byteAlgoritmo;
            }
            else
            {
                if (byte1[i] == 1)
                {
                    resultado = resultado ^ byte2;
                    cout << resultado << endl;
                }
                shift(byte2);
            }
        }
    }
    write_registers(cout, original1, original2, resultado);
}

int main() {

    int byte1, byte2 , menu;
    string opcion;
    string x , y;
    cout << "-------------------------------------------\n";
    cout << "Práctica 6 - Multiplicación en SNOW3G y AES\n";
    cout << "-------------------------------------------\n";
    cout << "1.Multiplicación en AES\n";
    cout << "2.Multiplicación en SNOW3G\n";
    cout << "3.Ambas multiplicaciones\n";
    cout << "0.Salir\n";
    cout << "\nElije una opción: ";
    cin >> menu;
    cout << "-------------------\n";
    if (menu == 0) {
        cout << "Saliendo del programa...";
        return 0;
    }
    cout << "Introduzca el primer byte: ";
    cin >> x;
    cout << "Introduzca el segundo byte: ";
    cin >> y;
    switch (menu) {
        // Multiplicación en AES
        case 1:
            multiplicacionAES(x ,y);
            break;

        // Multiplicación en SNOW3G
        case 2:
            multiplicacionSNOW3G(x,y);
            break;

        case 3: 
            
            break;
    }



    return 0;
}