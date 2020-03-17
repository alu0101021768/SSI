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
    vector<int> binario0to3;
    vector<int> primeraXor2bits(2);
    vector<int> segundaXor2bits(2);
    vector<int> secuencia_cifrante;

    //cout << binaryToInteger(R1) << endl;

    int iteraciones;
    cout << "Introduzca el número de iteraciones: ";
    cin >> iteraciones;
    secuencia_cifrante.resize(iteraciones);

    for (int i = 0; i < iteraciones; i++)
    {
       // cout << v[i];
        // Swapeamos el contenido del registro R1 y el resultado de cambiar los bits , lo ponemos en R2
        R2 = swapNumber(R1);
        // Cogemos el segundo bit de R1 , al cual llamaremos c0t
        int c0t = R1[1];
        // Generamos un bit de secuencia cifrante
        secuencia_cifrante[i] = generarSecuenciaCifrante(getLast(LFSR1), getLast(LFSR2), getLast(LFSR3), getLast(LFSR4), c0t);
        // Convertimos los 2 bits de R1 a decimal 
        int R1toDecimal = binaryToInteger(R1);
        // Sumamos la salida de los registros LFSR obteniendo un entero del 0-4
        int suma0to4 = sumaSalidasLFSR(getLast(LFSR1), getLast(LFSR2), getLast(LFSR3), getLast(LFSR4));
        // Sumamos el entero de 0-4 obtenido con el decimal obtenido de pasar el registro R1 a decimal
        int suma0to7 = suma0to4 + R1toDecimal;
        // Dividimos el resultado entero de 0-7 entre 2 y luego lo pasamos a binario, quedándonos un entero de 0-3 , pero en binario , 2 bits
        binario0to3 = divToBinary(suma0to7);
        // Rellenamos T2 de manera que de la entrada , el primer bit permanece intacto , y el segundo es el primero de la entrada xor el segundo de la entrada
        T2[0] = R2[0]; 
        T2[1] = R2[0] ^ R2[1];
        // Realizamos una xor entre T2 y el binario de 2 bits que se corresponde con un entero de 0-3
        primeraXor2bits = suma2bits(T2 , binario0to3);
        // Al resultado de esta última xor , se le realiza una xor con T1 que básicamente tiene el mismo contenido que R1
        segundaXor2bits = suma2bits(primeraXor2bits , R1);
        // El resultado de esta segunda xor , va a pasar a ser el contenido de R1
        R1 = segundaXor2bits;
        // Pasamos a shiftear los registros LFSR y realimentarlos
        shiftLFSR1(LFSR1);
        shiftLFSR2(LFSR2);
        shiftLFSR3(LFSR3);
        shiftLFSR4(LFSR4);
    }
    cout << endl;

    return 0;

}