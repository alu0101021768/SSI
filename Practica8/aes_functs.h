#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// xtime es una macro que encuentra el producto de {02} y el argumento para xtime modulo {1b}
#define xtime(x) ((x << 1) ^ (((x >> 7) & 1) * 0x1b))
// Vector de valores hexadecimales que representan la matriz de estado (en este caso unidimensional)
vector<int> estado;
// Vector que contendrá todas las subclaves generadas
vector<vector<int>> subkeys;
// Variable donde almaceno la clave de entrada o input key
vector<int> clave = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
// Variable donde almaceno el bloque de texto original o plaintext
vector<int> bloque = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
// Vector que contiene los valores necesarios por los que multiplicaremos en la expansión de claves
vector<int> Rcon = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10,
                    0x20, 0x40, 0x80, 0x1b, 0x36};
// Caja S o S-BOX
int get_SBox_Value(int num) {
  vector<int> sbox = {
      0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
      0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
      0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
      0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
      0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
      0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
      0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
      0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
      0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
      0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
      0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
      0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
      0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
      0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
      0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
      0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
      0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
      0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
      0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
      0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
      0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
      0xb0, 0x54, 0xbb, 0x16};
  return sbox[num];
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// FUNCIONES PRINCIPALES CIFRADO AES/RJINDAEL
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

//  Multiplicando una matriz por los cuatro bytes de cada columna, operando con
//  bytes
void mixSingleColumn(vector<int> &r) {
  vector<int> a(4), b(4);
  int c, h;
  /* The array 'a' is simply a copy of the input array 'r'
   * The array 'b' is each element of the array 'a' multiplied by 2
   * in Rijndael's Galois field
   * a[n] ^ b[n] is element n multiplied by 3 in Rijndael's Galois field */
  for (c = 0; c < 4; c++) {
    a[c] = r[c];
    /* h is 0xff if the high bit of r[c] is set, 0 otherwise */
    h = r[c] & 0x80; /* arithmetic right shift, thus shifting in
                               either zeros or ones */
    b[c] = r[c] << 1;
    if (h == 0x80) b[c] ^= 0x11b; /* Rijndael's Galois field */
  }
  r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
  r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
  r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
  r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
}

void MixColumn(vector<int> &estado) {
  vector<int> temp(4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      temp[j] = estado[i * 4 + j];  // Coloca la columna actual del estado en temp
    }
    mixSingleColumn(temp);          // La mezclamos haciendo uso de mixSingleColumn
    for (int j = 0; j < 4; ++j) {
      estado[i * 4 + j] = temp[j];  // Cuando la columna está mezclada se coloca en su sitio
    }
  }
}
// Realizamos una xor entre la clave y el bloque originales
void addRoundKey(vector<int> key, vector<int> bloque) {
  vector<int> resultado(16);
  for (int i = 0; i < 16; i++) {
    resultado[i] = key[i] ^ bloque[i];
  }
  estado = resultado;
}

// Sustituye cada elemento del estado por su correspondiente de la SBOX
void SubBytes(vector<int> &estado) {
  for (int i = 0; i < estado.size(); i++) 
    estado[i] = get_SBox_Value(estado[i]);
}

// Shiftea las filas tanttos bytes como su valor de fila del 0-3
void ShiftRow(vector<int> &estado) {
  int aux;
  // Primera fila
  aux = estado[1];
  estado[1] = estado[5];
  estado[5] = estado[9];
  estado[9] = estado[13];
  estado[13] = aux;
  // Segunda fila
  aux = estado[2];
  estado[2] = estado[10];
  estado[10] = aux;
  aux = estado[6];
  estado[6] = estado[14];
  estado[14] = aux;
  // Tercera fila
  aux = estado[3];
  estado[3] = estado[15];
  estado[15] = estado[11];
  estado[11] = estado[7];
  estado[7] = aux;
}
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// FUNCIONES USADAS EN LA KEY EXPANSION
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

// Cambia la columna subiendo todos los elementos una posición
vector<int> RotWord(vector<int> &key) {
  vector<int> resultado(4);
  resultado[0] = key[13];
  resultado[1] = key[14];
  resultado[2] = key[15];
  resultado[3] = key[12];
  return resultado;
}

// Sustituye cada elemento de la columna por su correspondiente de la SBOX
void SubWord(vector<int> &resultado) {
  resultado[0] = get_SBox_Value(resultado[0]);
  resultado[1] = get_SBox_Value(resultado[1]);
  resultado[2] = get_SBox_Value(resultado[2]);
  resultado[3] = get_SBox_Value(resultado[3]);
}

void keyExpansion(vector<int> key) {
  subkeys.resize(11);
  subkeys[0] = key;     // Añadimos la primera subclave
  vector<int> aux(16);  
  for (int i = 1; i <= 10; i++) {
    vector<int> lastkey = subkeys[i - 1];
    vector<int> primera_col = RotWord(lastkey);
    SubWord(primera_col);
    // Primera columna de subkey nueva
    aux[0] = lastkey[0] ^ primera_col[0] ^ Rcon[i];
    aux[1] = lastkey[1] ^ primera_col[1];
    aux[2] = lastkey[2] ^ primera_col[2];
    aux[3] = lastkey[3] ^ primera_col[3];
    // Segunda columna de subkey nueva
    aux[4] = aux[0] ^ lastkey[4];
    aux[5] = aux[1] ^ lastkey[5];
    aux[6] = aux[2] ^ lastkey[6];
    aux[7] = aux[3] ^ lastkey[7];
    // Tercera columna de subkey nueva
    aux[8] = aux[4] ^ lastkey[8];
    aux[9] = aux[5] ^ lastkey[9];
    aux[10] = aux[6] ^ lastkey[10];
    aux[11] = aux[7] ^ lastkey[11];
    // Cuarta columna de subkey nueva
    aux[12] = aux[8] ^ lastkey[12];
    aux[13] = aux[9] ^ lastkey[13];
    aux[14] = aux[10] ^ lastkey[14];
    aux[15] = aux[11] ^ lastkey[15];
    subkeys[i] = aux;
  }
}
////////////////////////////////////////////////////////////////////

vector<int> cifradoAES_Rijndael(vector<int> clave , vector<int> bloque) {
  //////////////////////
  //  ETAPA INICIAL   //
  //////////////////////
  keyExpansion(clave);                                      // Generamos todas las subclaves
  addRoundKey(clave,bloque);                                // AddRoundKey entre clave y bloque de texto original
  //cout << "\nR0(SubClave = " << subkeys[0] << " ) = " << estado << "\n";  

  /////////////////////////////////////////
  //  ETAPA INTERMEDIA : 9 ITERACIONES   //
  /////////////////////////////////////////
  for (int i = 1; i <= 9; i++) {
    SubBytes(estado);
    ShiftRow(estado);
    MixColumn(estado);
    addRoundKey(estado, subkeys[i]);
    //cout << "\nR" << i << "(SubClave = " << subkeys[i] << " ) = " << estado << "\n";
  }

  //////////////////////
  //  ETAPA FINAL     //
  //////////////////////
  SubBytes(estado);
  ShiftRow(estado);
  addRoundKey(subkeys[10], estado);
  //cout << "\nR10(SubClave = " << subkeys[10] << " ) = " << estado << "\n";
  //cout << "\nBloque de texto cifrado : " << estado << "\n";
  return estado;
}

