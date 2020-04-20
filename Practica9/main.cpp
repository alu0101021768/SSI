#include<iostream>

using namespace std;

// El exponente es xA o xB según se llame a la función y se modifica en la columna central
// la x es el número correspondiente a la columna derecha del algoritmo
// La y corresponde a la columna izquierda

int fastExponentiation(int exponente, int modulo_p, int base_alfa) {
    int b = exponente;
    int x = 1;
    int y = base_alfa % modulo_p;
    while ((exponente > 0) && (y > 1)) {
        if ((exponente % 2) != 0) {
            x = (x * y) % modulo_p;
            exponente = exponente - 1;
        }
        else {
            y = (y * y) % modulo_p;
            exponente = exponente / 2;
        }
    }
    return x;
}

ostream& showResults(ostream& os , int moduloP, int alfa , int xA, int xB , int yA , int yB , int k) {
    os << "\n";
    os << "p = " << moduloP;
    os << ", α = " << alfa;
    os << ", xA = " << xA;
    os << ", xB = " << xB;
    os << ", yA = " << yA;
    os << ", yB = " << yB;
    os << ", k  = " << k;
    os << "\n";
    return os;
}

void diffie(int p, int xa, int xb, int alpha) {
    int yA = fastExponentiation(xa , p , alpha);
    int yB = fastExponentiation(xb , p , alpha);
    // Calculamos las dos K , pero dan lo mismo
    int kA = fastExponentiation(xa , p , yB);
    int kB = fastExponentiation(xb , p , yA);
    showResults(cout,p,alpha,xa,xb,yA,yB,kA);
}

void ejemplosGuion() {
    // Ejemplo 1
   diffie(13,5,2,4);
   // Ejemplo 2 
   diffie(43,25,33,23);
   // Ejemplo 3
   diffie(113,54,71,43);
}

void read(int& p, int& xa, int& xb, int& alpha) {

    cout << "Introduzca número primo p: ";
    cin >> p;
    cout << "Introduzca número alfa (menor que p): ";
    cin >> alpha;
    cout << "Escoja secreto xA: ";
    cin >> xa;
    cout << "Escoja secreto xB: ";
    cin >> xb;
}


int main() {
    int p, xa, xb, alpha,opcion = 0;
    

    cout << "----------------------------------------------------\n";
    cout << "Práctica 9 - Intercambio de claves de Diffie-Hellman\n";
    cout << "----------------------------------------------------\n";
    cout << "1.Introducir datos por teclado\n";
    cout << "2.Usar ejemplos del guión\n";
    
    while (opcion < 1 || opcion > 2) {
        cout << "Elija una opción: ";
        cin >> opcion;
    }
    
    switch (opcion) {
        case 1: 
            read(p, xa, xb, alpha);
            diffie(p, xa, xb, alpha);
            break;
        case 2: 
            ejemplosGuion();
            break;
    }
    
    return 0;
}