#ifndef ACERCADE_H
#define ACERCADE_H

class AcercaDe
{
	private:
		sf::Text titulo;
		sf::Text sTitulo;
		sf::Text texto;

		Boton regresar;

	public:
		AcercaDe();
		AcercaDe(sf::RenderWindow&, sf::Font&);
		~AcercaDe();

		void Mostrar(sf::RenderWindow&);
		void Animacion(sf::RenderWindow&);

		Boton& GetRegresar();
};

AcercaDe::AcercaDe() { }

AcercaDe::AcercaDe(sf::RenderWindow& ventana, sf::Font& fuente)
{
	this->titulo.setString("Acerca de");
	this->titulo.setColor(sf::Color::White);
	this->titulo.setCharacterSize(100);
	this->titulo.setFont(fuente);
	this->titulo.setPosition(ventana.getSize().x-(ventana.getSize().x/2+titulo.getLocalBounds().width/2), -240);

	this->sTitulo = titulo;
	this->sTitulo.setCharacterSize(50);
	this->sTitulo.setString("Othello! 1.0");
	this->sTitulo.setPosition(ventana.getSize().x-(ventana.getSize().x/2+sTitulo.getLocalBounds().width/2), 180);

	sf::String t = "Creado con: SFML\nCreado por: Jonathan J. Cantor G. 26.156.888 \n            Josue D. Depablos Q. 21.766.516\n \t\t\tSeccion: 2";

	this->texto.setString(t);

	this->texto.setFont(fuente);
	this->texto.setColor(sf::Color::White);
	this->texto.setCharacterSize(25);
	this->texto.setPosition(150, ventana.getSize().y/2);

	regresar = Boton("Regresar", fuente, 500, 50, ventana.getSize().x, 500, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
}

AcercaDe::~AcercaDe() { }

void AcercaDe::Mostrar(sf::RenderWindow& ventana)
{
	ventana.draw(titulo);
	ventana.draw(sTitulo);
	ventana.draw(texto);
	regresar.Mostrar(ventana);
}

void AcercaDe::Animacion(sf::RenderWindow& ventana)
{
	if(titulo.getPosition().y < 20)
		titulo.move(0, 2);

	regresar.AnimacionH(ventana, ventana.getSize().x/2 - regresar.GetShape().getSize().x/2);
}

Boton& AcercaDe::GetRegresar() { return regresar; }

#endif
