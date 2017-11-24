#ifndef PJUGADA_H
#define PJUGADA_H

class PJugada
{
	private:
		int posX;
		int posY;
		int nFichas;
		int valor;
	
	public:
		PJugada();
		PJugada(int, int, int, int);
		~PJugada();

		void SetPosX(int);
		void SetPosY(int);
		void SetNFichas(int);
		void SetValor(int);
		
		int GetPosX();
		int GetPosY();
		int GetNFichas();
		int GetValor();
};

PJugada::PJugada()
{
	posX = 0;
	posY = 0;
	nFichas = 0;
}

PJugada::PJugada(int posX, int posY, int nFichas, int valor)
{
	this->posX = posX;
	this->posY = posY;
	this->nFichas = nFichas;
	this->valor = valor;
}

PJugada::~PJugada() { }

void PJugada::SetNFichas(int nFichas) { this->nFichas = nFichas; }
void PJugada::SetPosX(int posX) { this->posX = posX; }
void PJugada::SetPosY(int posY) { this->posY = posY; }
void PJugada::SetValor(int valor) { this->valor = valor; }

int PJugada::GetNFichas() { return nFichas; }
int PJugada::GetPosX() { return posX; }
int PJugada::GetPosY() { return posY; }
int PJugada::GetValor() { return valor; }

#endif

