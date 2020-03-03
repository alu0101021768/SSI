#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RC4 {

private:
    vector<int> S;                                      // Vector de estado S : contiene una permutación de todos los números enteros del 0 a 255
    vector<int> K;                                      // Vector de clave K
    int i_inx, j_inx;                                   // Indices
    vector<int> secuencia_cifrante;                     // Secuencia cifrante
public:

    RC4();                                              // ructor por defecto
    RC4(vector<int> semilla_clave);                     // ructor parametrizado
    ~RC4();                                             // Destructor

    void KSA(vector<int>& semilla_clave);               // Inicializacion ( Key Scheduling Algorithm )
    int PRGA();                                         // Generación de secuencia cifrante
    vector<int> Cifrado(vector<int> mensaje);           // Cifrado
    vector<int> Descifrado(vector<int> mensaje);        // Descifrado
    void swap( int index_s,  int index_k);              // Swap
    inline vector<int> get_secuencia() { return secuencia_cifrante; };  // Retorna la secuencia cifrante
};


