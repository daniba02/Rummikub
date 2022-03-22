#include <iostream>
#include <ctime>

using namespace std;

const int numFichas = 13;
const int numJugadores = 4;
const int iniFichas = 14;
const int maxFichas = 50;


typedef enum tColor { Rojo, Verde, Azul, Amarillo, Blanco, Libre };

struct tFicha {

	int numero;
	tColor color;
};

typedef tFicha tArrayFichas[maxFichas];

struct tSoporte {

	tArrayFichas fichas;
	int contador = 0;
};

typedef tSoporte tArraySoportes[numJugadores];

struct tSoportes {
	tArraySoportes soporte;
	int contador;
};

typedef tFicha tArrayBolsa[8][numFichas];

struct tBolsa {

	tArrayBolsa fichasB;
	int contador = 0;
};

typedef tFicha tJugada[numFichas + 1];

struct tTablero {

	tJugada jugada;
	int contador = 0;
	int maxJugadas = contador * 2;
};

int menu();
void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);
void repartir(tBolsa& bolsa, tSoportes& soportes);
void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
int buscar(const tJugada& jugada, const tFicha& ficha);


int main() {

}

int menu() {
	int op;

	cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";

	cin >> op;

	while (op < 0 || op > 5) {
		cin >> op;
	}
	return op;
}

void inicializarBolsa(tBolsa& bolsa) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < numFichas; j++) {

			bolsa.fichasB[i][j].numero = j + 1;

			if (i == 0 || i == 4) {
				bolsa.fichasB[i][j].color = Rojo;
			}
			else if (i == 1 || i == 5) {
				bolsa.fichasB[i][j].color = Verde;
			}
			else if (i == 2 || i == 6) {
				bolsa.fichasB[i][j].color = Azul;
			}
			else if (i == 3 || i == 7) {
				bolsa.fichasB[i][j].color = Amarillo;
			}
			
			bolsa.contador++;
		}
	}
}

tFicha robar(tBolsa& bolsa) {
	int fila, colum;

	srand(time(NULL));

	fila = rand() % 8;
	colum = rand() % numFichas;

	tFicha ficha = bolsa.fichasB[fila][colum];

	if (bolsa.fichasB[fila][colum].color == Libre) {

		bool encontrado = false;

		for (int i = fila; i < 8 && !encontrado; i++) {
			for (int j = colum; j < numFichas && !encontrado; j++) {

				if (bolsa.fichasB[i][j].color != Libre) {
					fila = i;
					colum = j;
					encontrado = true;
				}
			}
		}
		for (int i = 0; i < fila && !encontrado; i++) {
			for (int j = 0; j < colum && !encontrado; j++) {

				if (bolsa.fichasB[i][j].color != Libre) {
					fila = i;
					colum = j;
					encontrado = true;
				}
			}
		}
		ficha = bolsa.fichasB[fila][colum];

		if (!encontrado) {
			tFicha aux;
			aux.color = Libre;
			aux.numero = -1;
			ficha = aux;
		}
	}
	return ficha;
}

void repartir(tBolsa& bolsa, tSoportes& soportes) {

	tFicha ficha;

	for (int i = 0; i < numJugadores; i++) {

		for (int j = 0; j < iniFichas; j++) {
			
			ficha = robar(bolsa);
			soportes.soporte[i].fichas[j] = ficha;
		}
	}
}

void ordenarPorNum(tSoporte& soporte) {

	for (int i = 0; i < soporte.contador; i++) {

		int menor = i;

		for (int j = i+1; j < soporte.contador; j++) {

			if (soporte.fichas[menor].numero < soporte.fichas[j].numero) {
				menor = j;
			}
		}
		if (menor < i) {
			tFicha aux;
			aux = soporte.fichas[i];
			soporte.fichas[i] = soporte.fichas[menor];
			soporte.fichas[menor] = aux;
		}
	}
}

void ordenarPorColor(tSoporte& soporte) {

	tColor color;
	int pos = 0;

	for (int i = 0; i < 4; i++) {

		if (i == 0) {
			color = Rojo;
		}
		else if (i == 1) {
			color = Verde;
		}
		else if (i == 2) {
			color = Azul;
		}
		else if (i == 3) {
			color = Amarillo;
		}

		for (int x = 0; x < soporte.contador; x++) {
			
			if (soporte.fichas[x].color == color) {
				tFicha aux;
				aux = soporte.fichas[x];
				soporte.fichas[x] = soporte.fichas[pos];
				soporte.fichas[pos] = aux;
				pos++;
			}
		}
	}

	for (int j = 0; j < soporte.contador; j++) {

		int menor = j;

		for (int k = j + 1; k < soporte.contador; k++) {

			if (soporte.fichas[menor].numero < soporte.fichas[k].numero && soporte.fichas[menor].color == soporte.fichas[k].color) {
				menor = k;
			}
		}
		if (menor < j) {
			tFicha aux;
			aux = soporte.fichas[j];
			soporte.fichas[j] = soporte.fichas[menor];
			soporte.fichas[menor] = aux;
		}
	}
}

int buscar(const tJugada& jugada, const tFicha& ficha) {

	int pos;

	for (int i = 0; i < numFichas + 1; i++) {

		if (jugada[i].numero == ficha.numero && jugada[i].color == ficha.color) {
			pos = i;
		}
	}

	return pos;
}

void eliminaFichas(tSoporte& soporte, const tJugada& jugada) {

	for (int i = 0; i < soporte.contador; i++) {

		for (int j = 0; j < numFichas + 1; j++) {
			
			if (soporte.fichas[i].numero == jugada[i].numero && soporte.fichas[i].color == jugada[i].color) {
				soporte.fichas[i];
			}
		}
	}
}
