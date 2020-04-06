#include "aes_functs.h"
#include <bitset>

ostream &write(ostream &os, vector<int> v) {
  os << "[ ";
  for (int i = 0; i < v.size(); i++) {
    os << hex << v[i] << " ";
  }
  os << "]\n";
}

ostream& operator<<(ostream&os , vector<int> v) {
    write(os,v);
    return os;
}

void CBCoperation(vector<int> clave , vector<int> vInit, vector<int> bloque1, vector<int> bloque2) {
    vector<int> xorResult(clave.size()); 
    vector<int> encryptedText1(clave.size());
    vector<int> encryptedText2(clave.size()); 
    // Ciframos el primer bloque de texto
    for (int i = 0; i < xorResult.size(); i++) {
        xorResult[i] = vInit[i] ^ bloque1[i];
    }
    encryptedText1 = cifradoAES_Rijndael(clave,xorResult);

    // Ciframos el segundo bloque de texto
    for (int i = 0; i < xorResult.size(); i++) {
        xorResult[i] = encryptedText1[i] ^ bloque2[i];
    }
    encryptedText2 = cifradoAES_Rijndael(clave,xorResult);
    cout << "\nBloque 1 cifrado: " << encryptedText1;
    cout << "Bloque 2 cifrado: " << encryptedText2;
}

int main(void)  {
    vector<int> clave = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    vector<int> vInit = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    vector<int> bloque1 = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
    vector<int> bloque2 = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    CBCoperation(clave,vInit,bloque1,bloque2);
    
    return 0;
}