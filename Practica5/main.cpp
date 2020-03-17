#include "funcionesE0.h"


int main() {
    // Semillas de los registros
    vector<int> LFSR1{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // Tamaño 25
    vector<int> LFSR2{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // Tamaño 31
    vector<int> LFSR3{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // Tamaño 33
    vector<int> LFSR4{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0}; // Tamaño 39
    vector<int> R1 {0 , 1};
    vector<int> R2;
    vector<int> T2;
    vector<int> aux1;
    vector<int> secuencia_cifrante;
    int c0t;

    //cout << binaryToInteger(R1) << endl;

    int iteraciones;
    cout << "Introduzca el número de iteraciones: ";
    cin >> iteraciones;
    secuencia_cifrante.resize(iteraciones);

   // vector<int> v = divToBinary(5);
    for (int i = 0; i < iteraciones; i++)
    {
       // cout << v[i];
        // Swapeamos el contenido del registro R1 y el resultado de cambiar los bits , lo ponemos en R2
        R2 = swapNumber(R1);
        // Cogemos el segundo bit de R1 , al cual llamaremos c0t
        c0t = R1[1];
        // Generamos un bit de secuencia cifrante
        secuencia_cifrante[i] = generarSecuenciaCifrante(getLast(LFSR1), getLast(LFSR2), getLast(LFSR3), getLast(LFSR4), c0t);
        // Convertimos los 2 bits de R1 a decimal 
        int R1toDecimal = binaryToInteger(R1);
        // Sumamos la salida de los registros LFSR obteniendo un entero del 0-4
        int suma0to4 = sumaSalidasLFSR(getLast(LFSR1), getLast(LFSR2), getLast(LFSR3), getLast(LFSR4));
        // Sumamos el entero de 0-4 obtenido con el decimal obtenido de pasar el registro R1 a decimal
        int suma0to7 = suma0to4 + R1toDecimal;
        // Dividimos el resultado entero de 0-7 entre 2 
        aux1 = divToBinary(suma0to7);
       // T2[0] = 
    }
    cout << endl;

    return 0;

}