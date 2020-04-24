#include<iostream>
#include<random>

using namespace std;

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

int main() {

	int p , q , N , s = 0 , v , x = 0, it, a,  e , y;
	vector<pair<int,int>> valoresXyE;
	cout << "-----------------\n";
	cout << "ENTRADA\n";
	cout << "-----------------\n";
	// Recogemos número primos secretos
	cout << "p = ";
	cin >> p;
	cout << "q = ";
	cin >> q;
	// Calculamos N
	N = p * q; // Mostrar en salida 
	// Escoger numero secreto s tal que 0 < s < N ,  y es primo con N
	cout << "s = ";
	cin >> s;
	// Calculamos v = s^2 (mod N)
	v = fastExponentiation(2 , N , s); // Mostrar en salida 
	// Recogemos iteraciones
	cout << "Iteraciones = ";
	cin >> it;
	srand(time(NULL));
	// Dentro de cada iteracion 
	for (int i = 0;i < it; i++) {
		pair<int,int> valores;
		cout << "Datos " << (i + 1) << "º iteración:\n";
		cout <<  "x = ";
		cin >> x;
		valores.first = x;
		// Calculamos un bit aleatorio (0 o 1)
		e = rand() % 2;
		cout << "e = " ;
		cin >> e;  
		valores.second = e;
		valoresXyE.push_back(valores);
	}
	cout << "-----------------\n";
	cout << "SALIDA\n";
	cout << "-----------------\n";
	cout << "N=" << N << "\n";
	cout << "v=" << v << "\n";
	for (int i = 0;i < it; i++) {
		// Como los valores de x y e los he guardado en un vector de pares , los cogeremos del mismo , osea que cuando haya 
		// .first se refiere a la x de esa iteracion y cuando haya un .second se refiere a la e de esa iteración

		// Calculos por iteracion
		a = fastExponentiation(2, N,valoresXyE[i].first);
		cout << "Datos " << (i + 1) << "º iteración: \n";
		cout << "a = " << a;
		if (valoresXyE[i].second == 0) {
			y = fastExponentiation(1 , N , valoresXyE[i].first);
			cout << ", y = " << y;
			cout << ", comprobar que " << y << "\u00B2 \u2261 " << a << " (mod " << N << ") y dar por válida la iteración\n";  
		} 
		else {
			y = fastExponentiation(1 , N , (valoresXyE[i].first * s));
			cout << ", y = " << y;
			cout << ", comprobar que " << y << "\u00B2 \u2261 " << a << "*" << v << " (mod " << N << ") y dar por válida la iteración\n";
		}
	}

	return 0;
}
