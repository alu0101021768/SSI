#pragma once
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// Write para vectores
ostream& write(ostream &os, vector<int> v)
{
    os << "[ ";
    for (int i = 0; i < v.size(); i++)
    {
        if (i != v.size() - 1)
            os << v[i] << " , ";
        else
            os << v[i] << " ]" << endl;
    }
    return os;
}
// Devuelve el último elemento de un vector
int getLast(vector<int> v) 
{ 
    return v[v.size()-1]; 
}

// Funciones shift haciendo uso de los polinomios de realimentación 
void shiftLFSR1(vector<int>& v) 
{
    int retroalimentacion = (v[7] ^ v[11] ^ v[19] ^ v[24]);
    for (int i = v.size() - 1; i > 0; i--) 
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}
void shiftLFSR2(vector<int>& v) 
{
    int retroalimentacion = (v[11] ^ v[15] ^ v[23] ^ v[30]);
    for (int i = v.size() - 1; i > 0; i--)
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}
void shiftLFSR3(vector<int>& v) 
{
    int retroalimentacion = (v[3] ^ v[23] ^ v[27] ^ v[32]);
    for (int i = v.size() - 1; i > 0; i--)
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}
void shiftLFSR4(vector<int>& v) 
{
    int retroalimentacion = (v[3] ^ v[27] ^ v[35] ^ v[38]);
    for (int i = v.size() - 1; i > 0; i--)
    {
        v[i] = v[i - 1];
    }
    v[0] = retroalimentacion;
}
// Funcion T2
vector<int> fillT2(vector<int> R2) 
{
    vector<int> resultado(R2.size());
    resultado[0] = R2[1];
    resultado[1] = R2[0] ^ R2[1];
    return resultado;
}

// Funciones suma de 2 bits : pos 0 con pos 0 y pos 1 con pos 1
vector<int> suma2bits(vector<int> a, vector<int> b) {
    vector<int> r(2);
    r[0] = a[0] ^ b[0];
    r[1] = a[1] ^ b[1];
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
int sumaR1masSalidaLFSR(int x, int y)
{
    return (x + y); 
}

// Divide 
vector<int> divToBinary(int x) 
{
    vector<int> binaryNumber(2);
    x = x/2;
    bitset<2> numeroBinario(x);
    binaryNumber[0] = numeroBinario[1];
    binaryNumber[1] = numeroBinario[0];

    return binaryNumber;
}

// Swap
vector<int> swapNumber(vector<int> v)
{
    vector<int> resultado(v);
    resultado[0] = v[1];
    resultado[1] = v[0];
    return resultado;
}

// Convierte el numero binario guardado en el vector a un numero entero
int binaryToInteger(vector<int> v) {
    string s;
    s.resize(v.size());
    for (int i = 0 ; i < v.size() ; i++) {
        s[i] = v[i] + 48;
    }
    bitset<2> r (s);
    return r.to_ulong();
}

