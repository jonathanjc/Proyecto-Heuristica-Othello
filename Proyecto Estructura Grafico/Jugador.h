#ifndef JUGADOR_H
#define JUGADOR_H

using namespace std;

class Jugador
{
	private:
		Ficha ficha;
		string nombre;
		bool turno;
	
	public:
		Jugador();
		Jugador(string, Ficha, bool);
		~Jugador();

		Ficha Jugar(Tablero*, int posX, int posY);

		void SetFicha(Ficha);
		void SetNombre(string);
		void SetTurno(bool);

		Ficha GetFicha();
		string GetNombre();
		bool GetTurno();
};

Jugador::Jugador()
{
	nombre = "";
	turno = false;
}

Jugador::~Jugador(){ }

Jugador::Jugador(string nombre, Ficha ficha, bool turno)
{
	this->nombre = nombre;
	this->ficha = ficha;
	this->turno = turno;
}

Ficha Jugador::Jugar(Tablero* tablero, int posX, int posY)
{
	ficha.SetPosX(posX);
	ficha.SetPosY(posY);
	tablero->GetTablero()[posY][posX] = ficha;
	return ficha;
}

void Jugador::SetFicha(Ficha ficha){ this->ficha = ficha; }
void Jugador::SetNombre(string nombre){ this->nombre = nombre; }
void Jugador::SetTurno(bool turno){ this->turno = turno; }

Ficha Jugador::GetFicha(){ return ficha; }
string Jugador::GetNombre(){ return nombre; }
bool Jugador::GetTurno(){ return turno; }

#endif
