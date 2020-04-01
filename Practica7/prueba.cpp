#include<iostream>
#include<string>
#include<vector>
using namespace std;

// Convierte un numero hexadecimal a decimal
int convert(string num) {
  int len = num.size();
  int base = 1;
  int temp = 0;
  for (int i = len - 1; i >= 0; i--) {
    if (num[i] >= '0' && num[i] <= '9') {
      temp += (num[i] - 48) * base;
      base = base * 16;
    } else if (num[i] >= 'A' && num[i] <= 'F') {
      temp += (num[i] - 55) * base;
      base = base * 16;
    }
  }
  return temp;
}

int main() {
    string byte;
    vector<string> s_key(16);
    cout << "Introduzca byte a byte la clave de 16 bytes\n";
    int i = 0;
    while(i != 16) {
        getline(cin,byte);
        s_key.push_back(byte);
        i++;
    } 
       
    vector<int> key(16);
    for (int i = 0; i < s_key.size (); i++) {
        key[i] = convert(s_key[i]);
        cout << "\ndec : " << key[i];
        cout << "\nhex : " << hex << key[i];
    }
    return 0;
}