// Autor/a: Daniel Barroso Casado
// email: daniba02@ucm.es
// Visual Studio en Windows 10
// Rummy-PR04


#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

const int MAXNUMFICHAS = 13;
const int MAXJUGADORES = 4;
const int MAXFICHAS = 50;

int numFichas = 0;
int iniFichas;
int numJugadores;
int jugadorTurno = 1;
int cont = 0;


enum tColor { rojo, verde, azul, amarillo, blanco, libre };

struct tFicha {

	int numero;
	string color;
	tColor c;
};

typedef tFicha tArrayFichas[MAXFICHAS];

struct tSoporte {

	tArrayFichas fichas;
	int contador = 0;
};

typedef tSoporte tArraySoportes[MAXJUGADORES];

struct tSoportes {
	tArraySoportes soporte;
	int contador = 0;
};

typedef tFicha tArrayBolsa[8][MAXNUMFICHAS];

struct tBolsa {

	tArrayBolsa fichasB;
	int contador = 0;
};

typedef tFicha tJugada[MAXNUMFICHAS + 1];

typedef tJugada tArrayJugadas[MAXFICHAS * 2];

struct tTablero {

	tArrayJugadas jugadas;
	int contador = 0;
	int maxJugadas = contador * 2;
};


int buscar(const tJugada& jugada, const tFicha& ficha);


int menu(int op);
void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);
void repartir(tBolsa& bolsa, tSoportes& soportes);
void mostrar(const tBolsa& bolsa);
void mostrar(const tSoporte& soporte);
void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
bool operator>(tColor color1, tColor color2);
void mostrarSeries(const tSoporte& soporte);
void mostrarEscaleras(const tSoporte& soporte);
bool jugar(tTablero& tablero, tSoporte& soporte);
void mostrar(const tTablero& tablero);
void eliminaFichas(tSoporte& soporte, const tJugada& jugada);

int main() {


	tBolsa bolsa;
	tSoportes soportes;
	tTablero tablero;
	tColor color;


	int op = -1;
	bool ganado = false;

	
	cout << "Introduce el número de fichas: ";
	cin >> numFichas;
	cout << endl << "Introduce el número de fichas iniciales: ";
	cin >> iniFichas;
	cout << endl << "Introduce el número de jugadores: ";
	cin >> numJugadores;
	cout << endl << endl;

	inicializarBolsa(bolsa);
	mostrar(bolsa);
	repartir(bolsa, soportes);
	colorTexto(color);

	srand(time(NULL));

	jugadorTurno = rand() % numJugadores + 1;

	do {
		cout << "Turno para el jugador " << jugadorTurno << " ..." << endl;
		mostrar(soportes.soporte[jugadorTurno - 1]);

		do {
			bool jugado = false;
			cin >> op;

			if (op == -1)  // fin de la entrada
				return false;

			cout << endl;
			op = menu(op);

			if (op == 0) {

				if (!jugado) {
					soportes.soporte[jugadorTurno - 1].fichas[soportes.soporte[jugadorTurno - 1].contador] = robar(bolsa);
					soportes.soporte[jugadorTurno - 1].contador++;
					mostrar(soportes.soporte[jugadorTurno - 1]);
				}
			}
			else if (op == 1) {
				ordenarPorNum(soportes.soporte[jugadorTurno - 1]);
				mostrar(soportes.soporte[jugadorTurno - 1]);
			}
			else if (op == 2) {
				ordenarPorColor(soportes.soporte[jugadorTurno - 1]);
				mostrar(soportes.soporte[jugadorTurno - 1]);
			}
			else if (op == 3) {
				ordenarPorNum(soportes.soporte[jugadorTurno - 1]);
				mostrarSeries(soportes.soporte[jugadorTurno - 1]);
				ordenarPorColor(soportes.soporte[jugadorTurno - 1]);
				mostrarEscaleras(soportes.soporte[jugadorTurno - 1]);
				mostrar(soportes.soporte[jugadorTurno - 1]);
			}
			else if (op == 4) {
				if (jugar(tablero, soportes.soporte[jugadorTurno - 1])) {
					mostrar(tablero);
					jugado = true;
				}
				mostrar(soportes.soporte[jugadorTurno - 1]);
			}
			if (soportes.soporte[jugadorTurno - 1].contador == 0) {

				cout << endl << "El jugador " << jugadorTurno << " ha ganado!";
				ganado = true;
			}
		} while (op != 0);

		cout << endl;

		if (jugadorTurno < numJugadores) {
			jugadorTurno++;
		}
		else jugadorTurno = 1;

	} while (!ganado);

	

	// escribir sol

	return true;
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

int menu(int op) {
	//int op;

	cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>>  " << op << endl;


	//cin >> op;

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
				bolsa.fichasB[i][j].color = "rojo";
				bolsa.fichasB[i][j].c = rojo;
			}
			else if (i == 1 || i == 5) {
				bolsa.fichasB[i][j].color = "verd";
				bolsa.fichasB[i][j].c = verde;
			}
			else if (i == 2 || i == 6) {
				bolsa.fichasB[i][j].color = "azul";
				bolsa.fichasB[i][j].c = azul;
			}
			else if (i == 3 || i == 7) {
				bolsa.fichasB[i][j].color = "amar";
				bolsa.fichasB[i][j].c = amarillo;
			}

			bolsa.contador++;
		}
	}
}

tFicha robar(tBolsa& bolsa) {
	int fila, colum, auxColum;

	srand(time(NULL));

	fila = rand() % 8;
	colum = rand() % numFichas;
	
	auxColum = colum;


	tFicha ficha = bolsa.fichasB[fila][colum];

	if (bolsa.fichasB[fila][colum].c == libre) {

		bool encontrado = false;

		for (int i = fila; i < 8 && !encontrado; i++) {
			for (int j = colum; j < numFichas && !encontrado; j++) {

				if (bolsa.fichasB[i][j].c != libre) {
					fila = i;
					colum = j;
					encontrado = true;
				}
			}
			if (!encontrado) {
				colum = 0;
			}
		}
		for (int i = 0; i < fila && !encontrado; i++) {
			for (int j = 0; j < auxColum && !encontrado; j++) {

				if (bolsa.fichasB[i][j].c != libre) {
					fila = i;
					colum = j;
					encontrado = true;
				}
			}
		}
		ficha = bolsa.fichasB[fila][colum];

		if (!encontrado) {
			tFicha aux;
			aux.c = libre;
			aux.numero = -1;
			aux.color = "";
			ficha = aux;
		}
	}
	bolsa.fichasB[fila][colum].numero = -1;
	bolsa.fichasB[fila][colum].color = "";
	bolsa.fichasB[fila][colum].c = libre;

	return ficha;
}

void repartir(tBolsa& bolsa, tSoportes& soportes) {

	tFicha ficha;

	for (int i = 0; i < numJugadores; i++) {

		for (int j = 0; j < iniFichas; j++) {

			ficha = robar(bolsa);
			soportes.soporte[i].fichas[j] = ficha;
			soportes.soporte[i].contador++;
		}
		soportes.contador++;
	}
	cout << "Fichas de la bolsa con todas las fichas repartidas" << endl;
	mostrar(bolsa);
}

void mostrar(const tBolsa& bolsa) {

	cout << endl;
	cout << "Bolsa..." << endl;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < numFichas; j++) {
			cout << setw(4) << right << bolsa.fichasB[i][j].color << setw(2) << right << bolsa.fichasB[i][j].numero << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void mostrar(const tSoporte& soporte) {

	cout << "Soporte: ";

	for (int i = 0; i < soporte.contador; i++) {

		cout << soporte.fichas[i].color << " " << soporte.fichas[i].numero << "  ";

	}
	cout << endl;
}

void ordenarPorNum(tSoporte& soporte) {

	for (int i = 0; i < soporte.contador; i++) {

		int menor = i;

		for (int j = i + 1; j < soporte.contador; j++) {

			if (soporte.fichas[menor].numero > soporte.fichas[j].numero) {
				menor = j;
			}
			else if (soporte.fichas[menor].numero == soporte.fichas[j].numero && soporte.fichas[j].c > soporte.fichas[menor].c) {
				menor = j;
			}
		}
		if (menor != i) {
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
			color = rojo;
		}
		else if (i == 1) {
			color = verde;
		}
		else if (i == 2) {
			color = azul;
		}
		else if (i == 3) {
			color = amarillo;
		}

		for (int x = 0; x < soporte.contador; x++) {

			if (soporte.fichas[x].c == color) {
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

			if (soporte.fichas[menor].numero > soporte.fichas[k].numero && soporte.fichas[menor].color == soporte.fichas[k].color) {
				menor = k;
			}
		}
		if (menor != j) {
			tFicha aux;
			aux = soporte.fichas[j];
			soporte.fichas[j] = soporte.fichas[menor];
			soporte.fichas[menor] = aux;
		}
	}
}

bool operator>(tColor color1, tColor color2) {

	if (color1 == rojo) {
		return true;
	}
	if (color1 == verde && color2 != rojo) {
		return true;
	}
	if (color1 == azul && color2 != rojo && color2 != verde) {
		return true;
	}
	else return false;
}

void mostrarSeries(const tSoporte& soporte) {

	tSoporte aux;
	bool encontrada = false;
	bool terminada = false;

	int cont = 0;

	for (int i = 0; i < soporte.contador; i++) {

		if (cont != 0 && aux.fichas[cont - 1].numero == soporte.fichas[i].numero && aux.fichas[cont - 1].color != soporte.fichas[i].color) {

			aux.fichas[cont] = soporte.fichas[i];
			cont++;

			if (cont > 2) {
				encontrada = true;
			}
			if (encontrada && soporte.fichas[i].numero != soporte.fichas[i + 1].numero) terminada = true;

			if (terminada) {
				for (int i = 0; i < cont; i++) {
					cout << aux.fichas[i].color << " " << aux.fichas[i].numero << "  ";
				}
				cout << endl;
				cont = 0;
				encontrada = false;
				terminada = false;
			}
		}
		else if (cont != 0 && (aux.fichas[cont - 1].numero != soporte.fichas[i].numero || aux.fichas[cont - 1].color != soporte.fichas[i].color)) {
			encontrada = false;
			terminada = false;
			cont = 0;
		}
		if (cont == 0) {
			aux.fichas[cont] = soporte.fichas[i];
			cont++;
		}

	}

}

void mostrarEscaleras(const tSoporte& soporte) {

	tSoporte aux;
	bool encontrada = false;
	bool terminada = false;

	int cont = 0;

	for (int i = 0; i < soporte.contador; i++) {

		if (cont != 0 && aux.fichas[cont - 1].numero + 1 == soporte.fichas[i].numero && aux.fichas[cont - 1].color == soporte.fichas[i].color) {

			aux.fichas[cont] = soporte.fichas[i];
			cont++;

			if (cont > 2) {
				encontrada = true;
			}
			if (encontrada && (soporte.fichas[i].numero + 1 != soporte.fichas[i + 1].numero || soporte.fichas[i].color != soporte.fichas[i + 1].color)) terminada = true;

			if (terminada) {
				for (int i = 0; i < cont; i++) {
					cout << aux.fichas[i].color << " " << aux.fichas[i].numero << "  ";
				}
				encontrada = false;
				terminada = false;
				cout << endl;
				cont = 0;
			}
		}
		else if (cont != 0 && (aux.fichas[cont - 1].numero != soporte.fichas[i].numero || aux.fichas[cont - 1].color != soporte.fichas[i].color)) {
			encontrada = false;
			terminada = false;
			cont = 0;
		}
		if (cont == 0) {
			aux.fichas[cont] = soporte.fichas[i];
			cont++;
		}

	}
}

bool ponerFicha(tJugada& jugada, tFicha& ficha) {

	bool colocada = false;

	/*int trio = 0;
	int escalera = 0;
	bool threesome = false;
	bool stair = false;

	for (int i = 0; jugada[i].numero != -1; i++) {

		if (jugada[i].numero == jugada[i + 1].numero && jugada[i].color == jugada[i + 1].color) {
			trio++;
		}
		else if (jugada[i].numero + 1 == jugada[i + 1].numero && jugada[i].color == jugada[i + 1].color) {      // Usar luego para ver si la jugada es válida
			escalera++;
		}
		contador++;
	}

	if (contador == trio) {
		threesome = true;
	}
	else if (contador == escalera) {
		stair = true;
	}*/
	int contador = 0;

	for (int i = 0; jugada[i].numero != -1; i++) {
		contador++;
	}

	if (jugada[0].numero != jugada[1].numero && ficha.color == jugada[0].color) {

		if (ficha.numero == jugada[0].numero - 1) {

			int num;
			for (int i = contador; i >= 0; i--) {
				jugada[i + 1] = jugada[i];
			}
			jugada[0] = ficha;
			colocada = true;
		}

		else if (jugada[contador - 1].numero + 1 == ficha.numero) {

			jugada[contador + 1] = jugada[contador];
			jugada[contador] = ficha;
			colocada = true;
		}
	}
	else if (contador < 4) {

		bool color = false;
		bool serie = true;;

		for (int i = 0; i < contador; i++) {

			if (jugada[i].color == ficha.color) {
				color = true;
			}
			if (jugada[i].numero != ficha.numero) {
				serie = false;
			}
		}

		if (!color && serie) {
			jugada[contador + 1] = jugada[contador];
			jugada[contador] = ficha;
			colocada = true;
		}
	}

	return colocada;
}

bool jugar(tTablero& tablero, tSoporte& soporte) {

	int op;
	int cont = 0;
	int trio = 0;
	int fichas[MAXNUMFICHAS];
	bool serie = false;
	bool escalera = false;
	bool jugado = false;
	bool colocada = false;
	tJugada jugada;

	mostrar(soporte);
	cout << "       ";

	for (int i = 0; i < soporte.contador; i++) {

		cout << setw(8) << right << i + 1;
	}
	cout << endl << endl;
	cout << "    Fichas (0 al final):";

	cin >> op;
	cout << " " << op;

	while (op != 0) {
		fichas[cont] = op - 1;
		cont++;
		cin >> op;
		cout << " " << op;
	}

	cout << endl << "Jugada: ";

	for (int i = 0; i < cont; i++) {
		jugada[i] = soporte.fichas[fichas[i]];
		cout << jugada[i].color << " " << jugada[i].numero << "  ";
	}

	if (cont >= 3) {

		for (int i = 0; i < cont - 1; i++) {
			if (soporte.fichas[fichas[i]].numero == soporte.fichas[fichas[i + 1]].numero) {
				trio++;
			}
		}
		if (trio == cont - 1) {

			trio = 0;

			for (int i = 0; i < cont - 1; i++) {
				for (int j = i + 1; j < cont; j++) {
					if (soporte.fichas[fichas[i]].color == soporte.fichas[fichas[i + 1]].color) {
						trio++;
					}
				}
			}
			if (trio == 0) {
				serie = true;
				int pos;
				for (int i = 0; i < cont; i++) {
					pos = i;
					tablero.jugadas[tablero.contador][pos] = soporte.fichas[fichas[i]];
				}
				tablero.jugadas[tablero.contador][pos + 1].numero = -1;
				tablero.jugadas[tablero.contador][pos + 1].c = libre;
				tablero.contador++;
			}
		}
		else {
			trio = 0;
			for (int i = 0; i < cont - 1; i++) {
				for (int j = i + 1; j < cont; j++) {
					if (soporte.fichas[fichas[i]].numero + 1 == soporte.fichas[fichas[i + 1]].numero && soporte.fichas[fichas[i]].color == soporte.fichas[fichas[i + 1]].color) {
					}
					else trio++;
				}
			}
			if (trio == 0) {
				escalera = true;
				int pos;
				for (int i = 0; i < cont; i++) {
					pos = i;
					tablero.jugadas[tablero.contador][pos] = soporte.fichas[fichas[i]];
				}
				tablero.jugadas[tablero.contador][pos + 1].numero = -1;
				tablero.jugadas[tablero.contador][pos + 1].c = libre;
				tablero.contador++;
			}
		}
	}
	else if (cont == 1) {

		for (int i = 0; i < tablero.contador && !colocada; i++) {
			colocada = ponerFicha(tablero.jugadas[i], jugada[0]);
		}
	}

	if (serie) {

		cout << " - Serie correcta!" << endl << endl;
		eliminaFichas(soporte, jugada);
		jugado = true;
	}
	else if (escalera) {
		cout << " - Escalera correcta!" << endl << endl;
		eliminaFichas(soporte, jugada);
		jugado = true;
	}
	else if (colocada) {
		cout << endl;
		cout << "Jugadas del tablero donde poner la ficha: " << tablero.contador << "  -> Colocada!" << endl << endl;
		eliminaFichas(soporte, jugada);
		jugado = true;
	}
	else if (!serie && !escalera && !colocada) {
		cout << " - No es una jugada correcta! Prueba de nuevo..." << endl;
	}

	return jugado;
}

void mostrar(const tTablero& tablero) {

	cout << "Tablero: " << endl;
	int cont = 1;
	bool siguiente = true;

	for (int i = 0; i < tablero.contador; i++) {
		cout << " " << i + 1 << ": ";
		for (int j = 0; tablero.jugadas[i][j].numero != -1; j++) {
			cout << tablero.jugadas[i][j].color << " " << tablero.jugadas[i][j].numero << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;

	/*for (int i = 0; i < tablero.contador; i++) {

		if (siguiente == true) {
			cout << cont << ": ";
			cont++;
			siguiente = false;
		}
		if (tablero.jugada[i].numero != -1) {
			cout << tablero.jugada[i].color << " " << tablero.jugada[i].numero << "  ";
		}
		else {
			cout << endl;
			siguiente = true;
		}
	}*/
}

void eliminaFichas(tSoporte& soporte, const tJugada& jugada) {

	for (int i = 0; i < numFichas + 1; i++) {

		for (int j = 0; j < soporte.contador; j++) {

			if (soporte.fichas[j].numero == jugada[i].numero && soporte.fichas[j].color == jugada[i].color) {

				for (int x = j; x < soporte.contador - 1; x++) {
					soporte.fichas[x] = soporte.fichas[x + 1];
				}
				j--;
				soporte.contador--;
			}
		}
	}
}

void colorTexto(tColor color) {
	switch (color) {
	case amarillo:
		cout << "\033[1;40;33m";
		break;
	case azul:
		cout << "\033[40;34m";
		break;
	case rojo:
		cout << "\033[40;31m";
		break;
	case verde:
		cout << "\033[40;32m";
		break;
	case blanco:
		cout << "\033[40;37m";
		break;
	}
}
