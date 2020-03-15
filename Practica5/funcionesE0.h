#pragma once
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// Funciones shift haciendo uso de los polinomios de realimentación 
void shiftLFSR1(vector<int> v) 
{
    int retroalimentacion = v[7] ^ v[11] ^ v[19] ^ v[24];
    for (int i = v.size() - 1; i > 0; i++) 
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}

void shiftLFSR2(vector<int> v) 
{
    int retroalimentacion = v[11] ^ v[15] ^ v[23] ^ v[30];
    for (int i = v.size() - 1; i > 0; i++)
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}

void shiftLFSR3(vector<int> v) 
{
    int retroalimentacion = v[3] ^ v[23] ^ v[27] ^ v[32];
    for (int i = v.size() - 1; i > 0; i++)
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}

void shiftLFSR4(vector<int> v) 
{
    int retroalimentacion = v[3] ^ v[27] ^ v[35] ^ v[38];
    for (int i = v.size() - 1; i > 0; i++)
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}
// Funciones T : 
//T1 ( C1#t , C0#t) = (C1#t , C0#t)  
//T2 (C1#t+1 , C0#t+1) = (C0#t+1, C1#t+1 ^ C0#t+1)


// Funciones suma de 2 bits : pos 0 con pos 0 y pos 1 con pos 1
vector<int> suma2bits(vector<int> a, vector<int> b) {
    vector<int> r(2);
    r[0] = a[0] + b[0];
    r[1] = a[1] + b[1];
    return r;
}

// Generador de bits de secuencia cifrante , XOR entre salida de los LFSR
int generarSecuenciaCifrante(int x1, int x2, int x3, int x4, int c0) {
    return (x1 ^ x2 ^ x3 ^ x4 ^ c0);
}

// Suma normal de las salidas de los LFSR , genera un entero del 0-4
int sumaSalidasLFSR(int x1, int x2, int x3, int x4)
{
    return (x1 + x2 + x3 + x4);
}

// Suma entre el resultado de "sumaSalidasLFSR" + lo que viene de R1 ,  genera un entero del 0-7
int sumaR1masSalidaLFSR()
