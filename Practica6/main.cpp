#include <iostream>
#include <bitset>
using namespace std;

ostream &write_registers(ostream &os , bitset<8> R1 , bitset<8> R2)
{
    os << "Primer Byte: [";
    for (int i = R1.size() - 1; i >= 0; i--)
    {
        os << R1[i];
    }
    os << "]\n";

    os << "Segundo Byte: [";
    for (int i = R2.size() - 1; i >= 0; i--)
    {
        os << R2[i];
    }
    os << "]\n";
}

// Algoritmo SNOW3G

// Algoritmo AES
bitset<8> unir(bitset<4> A , bitset<4> B) {
    bitset<8> R;

    for (int i = 0; i < R.size();i++) {
        int val = B[i];
        if (i >= 4) 
            val = A[i - 4];
        R[i] = val;
    }
    return R;
}
bitset<8> multiplicacionAES(string primer_byte , string segundo_byte) {
    // Convertimos el primer byte a binario
    bitset<4> m1(primer_byte[0]);
    bitset<4> m2(primer_byte[1]);
    bitset<8> byte1;
    byte1 = unir(m1,m2);
    // Convertimos el segundo byte a binario
    bitset<4> m3(segundo_byte[0]);
    bitset<4> m4(segundo_byte[1]);
    bitset<8> byte2;
    byte2 = unir(m3, m4);
    bitset<8> result;
    /*
    for (int i = 0; i < result.size();i++) {
        result[i] = byte1[i] * byte2[i];
    }
    */
    write_registers(cout,byte1,byte2);
    //byte1 + shift(byte1)

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
    cout << "3.Salir\n";
    cout << "\nElije una opción: ";
    cin >> menu;
    cout << "-------------------\n";

    switch (menu) {
        case 0:
            cout << "Saliendo del programa..."; 
            return 0;
        break;
        // Multiplicación en AES
        case 1:
            cout << "Introduzca el primer byte: ";
            cin >> x;
            cout << "Introduzca el segundo byte: ";
            cin >> y;
            multiplicacionAES(x ,y);
            break;
        // Multiplicación en SNOW3G
        case 2:
            cout << "Introduzca el primer byte: ";
            cin >> byte1;
            cout << "Introduzca el segundo byte: ";
            cin >> byte2;
            break;
    }



    return 0;
}