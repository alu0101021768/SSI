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

vector<int> head(vector<int> data, int a) {
    vector<int> aux(a);
    for (int i = 0; i < a; i++) 
        aux[i] = data[i];
    return aux;
}

vector<int> tail(vector<int> data, int a) {
    vector<int> aux(a);
    int j = aux.size() - 1;
    for (int i = data.size() - 1; i >= data.size() - a; i--) 
        aux[j--] = data[i];
    return aux;
}

vector<int> concatenate(vector<int> a, vector<int> b) {
    vector<int> r(a.size() + b.size());
    int x = (a.size() + b.size()) / 2;
    for (int i = 0; i < a.size(); i++) {
        r[i] = a[i];
        r[i + x] = b[i];
    }
    return r;
}

void zeroes(vector<int>& v, int wanted_size) {
    int actual_size = v.size();
    vector<int> resultado(wanted_size);
    // Copiamos lo que habia en el vector y lo rellenamos con ceros hasta el tamaño deseado
    for (int i = 0; i < wanted_size; i++) {
        if (i != actual_size)
            resultado[i] = v[i];
        else 
            resultado[i] = 0x00;
    }
    v = resultado;
}

void ECBoperation(vector<int> clave , vector<int> vInit, vector<int> bloque1, vector<int> bloque2) {
    vector<int> xorResult(clave.size());         // Variable auxiliar
    vector<int> lastText(clave.size());          // Lo llamamos last aunque sea el primer bloque porque será nuestro ultimo bloque cifrado
    vector<int> prevOfLastText(clave.size());    // En este caso es al revés que el anterior
    int firstBlockLength = bloque1.size();       // Tamaño del penultimo bloque de texto ()
    int secondBlockLength = bloque2.size();      // Tamalo del ultimo bloque de texto (M bits)

    // Ciframos el penultimo bloque de texto , realizando xor con la clave y encriptando con aes
    for (int i = 0; i < xorResult.size(); i++) {
        xorResult[i] = vInit[i] ^ bloque1[i];
    }
    lastText = cifradoAES_Rijndael(clave,xorResult);
    
    // De el resultado de esto , cogeremos los primeros M bits y esto será nuestro último bloque de texto cifrado
    vector<int> lastCipherTextBlock = head(lastText, secondBlockLength);

    // De el segundo bloque de texto cogemos los primeros M bits , y luego rellenamos con 0
    vector<int> firstTextHead = head(prevOfLastText,secondBlockLength);
    zeroes(firstTextHead, xorResult.size());

    // Lo ciframos obteniendo nuestro penultimo bloque de texto cifrado 
    for (int i = 0; i < xorResult.size(); i++) {
        xorResult[i] = lastText[i] ^ firstTextHead[i];
    }
    vector<int> firstCipherTextBlock = cifradoAES_Rijndael(clave , xorResult);

    cout << "\nBloque 1 cifrado: " << firstCipherTextBlock;
    cout << "Bloque 2 cifrado: " << lastCipherTextBlock;
}

int main(void)  {
    vector<int> clave = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    vector<int> vInit = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    vector<int> bloque1 = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
    vector<int> bloque2 = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    vector<int> bloque2_distinct = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    CBCoperation(clave,vInit,bloque1,bloque2);
    ECBoperation(clave,vInit,bloque1,bloque2_distinct);
    //cout << head(clave,5) << endl;
    //cout << tail(clave,5) << endl;
    //cout << concatenate(clave,bloque) << endl;
    return 0;
}