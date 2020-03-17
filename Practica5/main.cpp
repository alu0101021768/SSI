#include "funcionesE0.h"


int main() {
    // Semillas de los registros
    vector<int> LFSR1{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // Tamaño 25
    vector<int> LFSR2{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // Tamaño 31
    vector<int> LFSR3{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // Tamaño 33
    vector<int> LFSR4{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0}; // Tamaño 39
    vector<int> R1 {1 , 0};
    vector<int> R2;
    vector<int> T2;
    vector<int> binario0to3;
    vector<int> primeraXor2bits(2);
    vector<int> segundaXor2bits(2);
    vector<int> secuencia_cifrante;

    cout << "\n--------------------------\n";
    cout << "Generador E0 de Blueetooth";
    cout << "\n--------------------------\n";
    
    int iteraciones;
    cout << "Introduzca el número de iteraciones: ";
    cin >> iteraciones;
    secuencia_cifrante.resize(iteraciones);

    for (int i = 0; i < iteraciones; i++)
    {
        // Swapeamos el contenido del registro R1 y el resultado de cambiar los bits , lo ponemos en R2
        R2 = swapNumber(R1);
        // Cogemos el segundo bit de R1 , al cual llamaremos c0t
        int c0t = R1[1];
        int c1t = R1[0];
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
        T2 = fillT2(R2);
        // Realizamos una xor entre T2 y el binario de 2 bits que se corresponde con un entero de 0-3
        primeraXor2bits = suma2bits(T2 , binario0to3);
        // Al resultado de esta última xor , se le realiza una xor con T1 que básicamente tiene el mismo contenido que R1
        segundaXor2bits = suma2bits(primeraXor2bits , R1);
        // El resultado de esta segunda xor , va a pasar a ser el contenido de R1 , pero antes de asignárselo , mostraremos los valores de los registros
        cout << "\n--------------------------\n";
        cout << "Iteración " << i;
        cout << "\n--------------------------\n";
        cout << "Salida LFSR1: " << getLast(LFSR1) << endl;
        cout << "Salida LFSR2: " << getLast(LFSR2) << endl;
        cout << "Salida LFSR3: " << getLast(LFSR3) << endl;
        cout << "Salida LFSR4: " << getLast(LFSR4) << endl;
        cout << "Valor R1: "; write(cout , R1);
        cout << "Valor R2: "; write(cout, R2);
        cout << "Valor C0t (bit derecho R1): " << c0t << endl;
        cout << "Valor C1t (bit izquierdo R1): " << c1t << endl;
        cout << "Valor T1: "; write(cout, R1);
        cout << "Valor T2: "; write(cout, T2);
        cout << "Valor entero 0-4: " << suma0to4 << endl; 
        cout << "Valor entero 0-7: " << suma0to7 << endl;
        cout << "Valor entero 0-3 en binario 2 bits: "; write(cout , binario0to3);
        cout << "Valor primera XOR: "; write(cout , primeraXor2bits);
        cout << "Valor segunda XOR: "; write(cout , segundaXor2bits);
        cout << "Bit secuencia cifrante: " << secuencia_cifrante[i] << endl;
        // Actualizamos el contenido de R1 , con el contenido de segundaxor2bits
        R1 = swapNumber(segundaXor2bits);
        // Pasamos a shiftear los registros LFSR y realimentarlos
        shiftLFSR1(LFSR1);
        shiftLFSR2(LFSR2);
        shiftLFSR3(LFSR3);
        shiftLFSR4(LFSR4);
    }
    cout << endl;

    return 0;

}