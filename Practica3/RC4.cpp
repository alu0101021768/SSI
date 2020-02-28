#include "RC4.h"

RC4::RC4() : S(0), K(0), i_inx(0), j_inx(0) {}

RC4::RC4(vector<int> semilla_clave) : S(256) , K(256) , i_inx(0) , j_inx(0) {
    KSA(semilla_clave);
}

RC4::~RC4() {}

void RC4::KSA(vector<int>& semilla_clave) {
   
    for (int i = 0; i < 256; i++) {
        S[i] = i;
        K[i] = semilla_clave[i % semilla_clave.size()];
    }

    int j = 0;

    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + K[i]) % 256;
        swap(i, j);
    }
}

void RC4::swap( int i,  int j) {
   
    int aux = S[i];
    S[i] = S[j];
    S[j] = aux;
}

int RC4::PRGA() {
    
    i_inx = (i_inx + 1) % 256;
    j_inx = (j_inx + S[i_inx]) % 256;
    swap(i_inx , j_inx);
    int resultado = (S[i_inx] + S[j_inx]) % 256;
    return S[resultado];
}

 vector<int> RC4::Cifrado(vector<int> mensaje) {
    
    vector<int> s(mensaje.size());
    secuencia_cifrante.resize(mensaje.size());
    int byte;

    for (int i = 0; i < mensaje.size(); i++) {
        byte = PRGA();
        secuencia_cifrante[i] = byte;
        s[i] = mensaje[i] ^ byte;
    }
    return s;
}

vector<int> RC4::Descifrado(vector<int> mensaje) {

}