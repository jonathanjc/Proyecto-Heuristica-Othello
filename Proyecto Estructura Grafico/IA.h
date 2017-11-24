#ifndef IA_H
#define IA_H

using namespace std;

class IA
{
	private:
		Ficha ficha;
		string nombre;
		bool turno;
		
	public:
		IA();
		IA(string, Ficha, bool);
		~IA();

		Ficha Jugar(Tablero*, int posX, int posY);

		void SetFicha(Ficha);
		void SetNombre(string);
		void SetTurno(bool);

		Ficha GetFicha();
		string GetNombre();
		bool GetTurno();
};

IA::IA()
{
	nombre = "";
	turno = false;
}

IA::~IA(){ }

IA::IA(string nombre, Ficha ficha, bool turno)
{
	this->nombre = nombre;
	this->ficha = ficha;
	this->turno = turno;
}

Ficha IA::Jugar(Tablero* tablero, int posX, int posY)
{
	ficha.SetPosX(posX);
	ficha.SetPosY(posY);
	tablero->GetTablero()[posY][posX] = ficha;
	return ficha;
}


void IA::SetFicha(Ficha ficha) { this->ficha = ficha; }
void IA::SetNombre(string nombre) { this->nombre = nombre; }
void IA::SetTurno(bool turno) { this->turno = turno; }

Ficha IA::GetFicha() { return ficha; }
string IA::GetNombre() { return nombre; }
bool IA::GetTurno() { return turno; }

#endif
