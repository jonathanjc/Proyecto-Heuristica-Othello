#ifndef TABLERO_H
#define TABLERO_H

#include <sstream>

class Tablero
{
	private:
		int nFilas;
		int nColum;
		Color color;
		Ficha **tablero;

		Boton atras;
		Boton menu;
		Boton ayuda;

		int nFichasN;
		int nFichasB;
		int nFichasA;

		sf::Text tFichasN;
		sf::Text tFichasB;
		sf::CircleShape fichaN;
		sf::CircleShape fichaB;
		sf::CircleShape triangulo;
		sf::CircleShape cuadro;
		
	public:
		Tablero();
		Tablero(int, int, Color, sf::Font&);
		~Tablero();
		
		void SetNFilas(int);
		void SetNColum(int);
		void SetColor(Color);
		void SetTablero(Ficha**);
		void MostrarUI(sf::RenderWindow&);
		void MostrarUIGanador(sf::RenderWindow&, Ganador);
		void TrianguloAnim(int);
		
		int GetNFilas();
		int GetNColum();
		Color GetColor();
		Ficha** GetTablero();

		Boton& GetAtras();
		Boton& GetMenu();
		Boton& GetAyuda();

		int GetNFichasN();
		int GetNFichasB();
		int GetNFichasA();

		void SetNFichasN(int);
		void SetNFichasB(int);
		void SetNFichasA(int);

		void UpdateUI();
};

Tablero::Tablero()
{
	nFilas = 0;
	nColum = 0;
	color = Ninguno;
	tablero = NULL;
}

Tablero::Tablero(int nFilas, int nColum, Color color, sf::Font& fuente)
{
	tablero = new Ficha*[nFilas];
	for(int i=0; i<nFilas; i++)
		tablero[i] = new Ficha[nColum];
		
	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
			tablero[i][j] = Ficha(Ninguno);
	}
	
	this->color = color;

	atras = Boton("Atras", fuente,  150, 50, 615, 374, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	ayuda = Boton("Ayuda", fuente,  150, 50, 615, 450, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	menu = Boton("Menu", fuente,  150, 50, 615, 526, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));

	tFichasB.setFont(fuente);
	tFichasN.setFont(fuente);
	tFichasN.setPosition(sf::Vector2f(600, 25));
	tFichasB.setPosition(sf::Vector2f(600, 95));
	tFichasB.setCharacterSize(40);
	tFichasN.setCharacterSize(40);

	fichaB.setRadius(25);
	fichaB.setOutlineThickness(1);
	fichaB.setFillColor(sf::Color::White);
	fichaB.setOutlineColor(sf::Color::Black);
	fichaB.setPosition(sf::Vector2f(650, 95));
	
	fichaN.setRadius(25);
	fichaN.setOutlineThickness(1);
	fichaN.setFillColor(sf::Color(64, 64, 64));
	fichaN.setOutlineColor(sf::Color::Black);
	fichaN.setPosition(sf::Vector2f(650, 25));

	triangulo.setPointCount(3);
	triangulo.setRadius(25);
	triangulo.setOutlineThickness(1);
	triangulo.setFillColor(sf::Color(59, 117, 161));
	triangulo.setOutlineColor(sf::Color::Black);
	triangulo.rotate(-90);
	triangulo.setPosition(sf::Vector2f(725, 75));

	cuadro.setPointCount(4);
	cuadro.setRadius(25);
	cuadro.setOutlineThickness(1);
	cuadro.setFillColor(sf::Color(255, 226, 77));
	cuadro.setOutlineColor(sf::Color::Black);
	

	nFichasB = 0;
	nFichasN = 0;
	nFichasA = 0;

	UpdateUI();
}

void Tablero::MostrarUI(sf::RenderWindow& ventana)
{
	atras.Mostrar(ventana);
	ayuda.Mostrar(ventana);
	menu.Mostrar(ventana);
	ventana.draw(tFichasN);
	ventana.draw(tFichasB);
	ventana.draw(fichaN);
	ventana.draw(fichaB);
	ventana.draw(triangulo);
}

void Tablero::UpdateUI()
{
	std::stringstream fN;
	std::stringstream fB;
	std::string s;
	
	fN << nFichasN;
	fB << nFichasB;

	s = fN.str();
	tFichasN.setString(s);
	
	s = fB.str();
	tFichasB.setString(s);
}

void Tablero::MostrarUIGanador(sf::RenderWindow& ventana, Ganador ganador)
{
	if(ganador == FichaN)
	{
		sf::CircleShape c = fichaN;
		c.setPosition(sf::Vector2f(620, 230));
		cuadro.setPosition(sf::Vector2f(710, 230));
		ventana.draw(c);
		ventana.draw(cuadro);
	}

	else if(ganador == FichaB)
	{
		sf::CircleShape c = fichaB;
		c.setPosition(sf::Vector2f(620, 230));
		cuadro.setPosition(sf::Vector2f(710, 230));
		ventana.draw(c);
		ventana.draw(cuadro);
	}

	else if(ganador == Empate)
	{
		sf::CircleShape c = fichaN;
		sf::CircleShape c1 = fichaB;
		sf::CircleShape c2 = cuadro;

		c.setPosition(sf::Vector2f(620, 180));
		c1.setPosition(sf::Vector2f(620, 270));
		c2.setPosition(sf::Vector2f(710, 270));
		cuadro.setPosition(sf::Vector2f(710, 180));

		ventana.draw(c);
		ventana.draw(c1);
		ventana.draw(c2);
		ventana.draw(cuadro);
	}
}

void Tablero::TrianguloAnim(int posY)
{
	if(triangulo.getPosition().y > posY)
		triangulo.move(0, -5);

	else if(triangulo.getPosition().y < posY)
		triangulo.move(0, 5);
}

Tablero::~Tablero(){ }

void Tablero::SetNFilas(int nFilas){ this->nFilas = nFilas; }
void Tablero::SetNColum(int nColum){ this->nColum = nColum; }
void Tablero::SetColor(Color color){ this->color = color; }
void Tablero::SetTablero(Ficha** tablero){ this->tablero = tablero; }

int Tablero::GetNFilas(){ return nFilas; }
int Tablero::GetNColum(){ return nColum; }
Color Tablero::GetColor(){ return color; }
Ficha** Tablero::GetTablero(){ return tablero; }

Boton& Tablero::GetAtras() { return atras; }
Boton& Tablero::GetAyuda() { return ayuda; }
Boton& Tablero::GetMenu() { return menu; }

void Tablero::SetNFichasB(int nFichasB) { this->nFichasB = nFichasB; }
void Tablero::SetNFichasN(int nFichasN) { this->nFichasN = nFichasN; }
void Tablero::SetNFichasA(int nFichasA) { this->nFichasA = nFichasA; }

int Tablero::GetNFichasB() { return nFichasB; }
int Tablero::GetNFichasN() { return nFichasN; }
int Tablero::GetNFichasA() { return nFichasA; }

#endif
