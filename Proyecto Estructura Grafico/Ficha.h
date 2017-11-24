#ifndef FICHA_H
#define FICHA_H

class Ficha
{
	private:
		Color color;
		Boton ficha;
		int posX;
		int posY;
		
	public:
		Ficha();
		Ficha(Color);
		Ficha(Color, int, int);
		~Ficha();
		
		void SetColor(Color);
		void SetPosX(int);
		void SetPosY(int);
		
		Color GetColor();
		int GetPosX();
		int GetPosY();

		bool operator==(Color);
		bool operator==(Ficha);
		bool operator!=(Color);
		bool operator!=(Ficha);

		Boton& GetFicha();
};

Ficha::Ficha()
{
	color = Ninguno;
	ficha = Boton(70, 70);
}

Ficha::Ficha(Color color)
{
	this->color = color;
	ficha = Boton(70, 70);
}

Ficha::Ficha(Color color, int posX, int posY)
{
	this->color = color;
	this->posX = posX;
	this->posY = posY;
}

Ficha::~Ficha(){ }

bool Ficha::operator == (Color color)
{
	return this->color == color;
}

bool Ficha::operator == (Ficha ficha)
{
	return this->color == ficha.GetColor();
}

bool Ficha::operator != (Color color)
{
	return this->color != color;
}

bool Ficha::operator != (Ficha ficha)
{
	return this->color != ficha.GetColor();
}


void Ficha::SetColor(Color color){ this->color = color; }
void Ficha::SetPosX(int posX){ this->posX = posX; }
void Ficha::SetPosY(int posY){ this->posY = posY; }

Color Ficha::GetColor(){ return color; }
int Ficha::GetPosX(){ return posX; }
int Ficha::GetPosY(){ return posY; }
Boton& Ficha::GetFicha() { return ficha; }

#endif
