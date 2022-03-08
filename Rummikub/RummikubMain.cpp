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
[[[ [[[]] ] ] ] ]
typedef tFicha tArrayBolsa[8][numFichas];

struct tBolsa {

	tArrayBolsa fichasB;
	int contador = 0;
};

typedef tFicha tJugada[numFichas * 2][numFichas + 1];

struct tTablero {

	tJugada jugada;
	int contador = 0;
	int maxJugadas = contador * 2;
};

int menu();
void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);


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

	if (bolsa.fichasB[fila][colum].color == Libre) {

		bool encontrado = false;

		for (int i = fila; i < 8; i++) {
			for (int j = colum; j < numFichas; j++) {

				if (bolsa.fichasB[i][j].color != Libre) {

					
				}
			}
		}
	}
}