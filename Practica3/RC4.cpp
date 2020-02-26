#include "RC4.h"

RC4::RC4(vector<int> semilla_clave) {
    S.resize(0);
    K.resize(0);
    i_inx = 0;
    j_inx = 0;
}

RC4::RC4(vector<int> semilla_clave) {
    S.resize(256);
    K.resize(256);
    i_inx = 0;
    j_inx = 0;
    KSA(semilla_clave);
}

RC4::~RC4() {}

void RC4::KSA(vector<int> semilla_clave) {
   
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

void RC4::swap(const int i, const int j) {
   
    int aux = S[i];
    S[i] = S[j];
    S[j] = aux;
}

int RC4::PRGA() {
    
}