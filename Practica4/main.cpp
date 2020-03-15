#include<iostream>
#include<bitset>
#include<string>
#include<vector>

using namespace std;
							   //*
bitset<19> R1 (string("1001000100011010001"));
							    //*
bitset<22> R2 (string("0101100111100010011010"));
								//*
bitset<23> R3 (string("10111100110111100001111"));

int mayoria(bitset<19> R1 , bitset<22> R2 , bitset<23> R3) {
	return ((R1[8] * R2[10]) ^ (R1[8] * R3[10]) ^ (R2[10] * R3[10]));
}

ostream& write_registers(ostream& os) {
	os << "R1: [";
	for (int i = R1.size() - 1; i >= 0; i--) {
		os << R1[i];
	}
	os << "]\n";
	
	os << "R2: [";
	for (int i = R2.size() - 1; i >= 0; i--) {
		os << R2[i];
	}
	os << "]\n";
	
	os << "R1: [";
	for (int i = R3.size() - 1; i >= 0; i--) {
		os << R3[i];
	}
	os << "]\n";
} 

// Devuelve el valor a(t)
int xor_a_R1() {
	return (R1[18] ^ R1[17] ^ R1[16] ^ R1[13]);
}

// Devuelve el valor b(t)
int xor_b_R2() {
	return (R2[21] ^ R2[20]);
}

// Devuelve el valor c(t)
int xor_c_R3() {
	return (R3[22] ^ R3[21] ^ R3[20] ^ R3[7]);
}

void actualizarR1() {
	int retro = xor_a_R1();
	for (int i = R1.size(); i > 0; i--) {
		R1[i] = R1[i-1];
	}
	R1[0] = retro;
}

void actualizarR2() {
	int retro = xor_b_R2();
	for (int i = R2.size() - 1; i > 0; i--) {
		R2[i] = R2[i-1];
	}
	R2[0] = retro;
}

void actualizarR3() {
	int retro = xor_c_R3();
	for (int i = R3.size() - 1; i > 0; i--) {
		R3[i] = R3[i-1];
	}
	R3[0] = retro;
}


int main() {
	int iteraciones;
	cout << "Introduzca el número de iteraciones deseadas: ";
	cin >> iteraciones;

	vector<int> secuencia_cifrante;
	secuencia_cifrante.resize(iteraciones);
	for (int i = 0; i < iteraciones; i++) {
		cout << "Iteración: " << i << "\n";
		
		int most_rep = mayoria(R1,R2,R3);
		write_registers(cout);
		cout << "Función mayoría: " << most_rep << "\n";

		secuencia_cifrante[i] = (R1[R1.size()-1] ^ R2[R2.size()-1] ^ R3[R3.size()-1]);
		cout << "Bit secuencia cifrante: " << secuencia_cifrante[i] << "\n";
		
		
		if (R1[8] == most_rep) {
			actualizarR1(); cout << "R1 actualiza" << endl;}
		if (R2[10] == most_rep) {
			actualizarR2(); cout << "R2 actualiza" << endl;}
		if (R3[10] == most_rep) {
			actualizarR3(); cout << "R3 actualiza" << endl;}
		
		cout << "\n";
	}
	return 0;
}
