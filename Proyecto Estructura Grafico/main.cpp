#include <SFML/Graphics.hpp>
#include <iostream>

enum Estado{ Completo, Incompleto };
enum Ganador{ Empate, FichaN, FichaB, Nadie };
enum Color{ Ninguno, Blanco, Negro, Verde, Azul, Rojo };
enum Modo{ Nada, PvP, PvE };

#include "Juego.h"

const int nFilas = 8;
const int nColum = 8;

int main()
{
	Juego j(800, 600, "Othello", nFilas, nColum);

    return 0;
}
