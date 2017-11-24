#ifndef BOTON_H
#define BOTON_H

class Boton
{
	private:
		sf::Text texto;
		sf::RectangleShape fondo;
		sf::Color cFondo;
		sf::Color cMouse;
		sf::Color cOutlineFondo;
		sf::Color cOutlineMouse;

	public:
		Boton();
		Boton(sf::String, sf::Font&, int, int, int, int, sf::Color, sf::Color, sf::Color, sf::Color);
		Boton(int, int);
		~Boton();

		void Mostrar(sf::RenderWindow&);
		void AnimacionH(sf::RenderWindow&, int);
		void AnimacionV(sf::RenderWindow&, int);

		sf::RectangleShape &GetShape();
		sf::Text &GetTexto();
		sf::Color GetCFondo();
		sf::Color GetCMouse();
		sf::Color GetCOutlineFondo();
		sf::Color GetCOutlineMouse();
};

Boton::Boton() { }
Boton::~Boton() { }

Boton::Boton(sf::String nombre, sf::Font &fuente, int tamX, int tamY, int posX, int posY, sf::Color cFondo, sf::Color cMouse, sf::Color cOutlineFondo, sf::Color cOutlineMouse)
{
	this->cFondo = cFondo;
	this->cMouse = cMouse;
	this->cOutlineFondo = cOutlineFondo;
	this->cOutlineMouse = cOutlineMouse;
	
	fondo.setSize(sf::Vector2f(tamX, tamY));
	fondo.setPosition(posX, posY);
	fondo.setFillColor(cFondo);
	fondo.setOutlineThickness(5);
	fondo.setOutlineColor(cOutlineFondo);

	texto.setString(nombre);
	texto.setFont(fuente);
	texto.setColor(sf::Color::White);
	texto.setCharacterSize(50);
	texto.setPosition((fondo.getPosition().x+fondo.getSize().x) - (fondo.getSize().x/2+texto.getLocalBounds().width/2),
						fondo.getPosition().y-texto.getLocalBounds().height/4);
}

Boton::Boton(int tamX, int tamY)
{
	fondo.setSize(sf::Vector2f(tamX, tamY));
}

void Boton::Mostrar(sf::RenderWindow &ventana)
{
	ventana.draw(fondo);
	ventana.draw(texto);
}

void Boton::AnimacionH(sf::RenderWindow& ventana, int posX)
{
	if(fondo.getPosition().x == posX)
		return;
	
	if(fondo.getPosition().x < posX)
	{
		fondo.move(5, 0);
		texto.move(5, 0);
	}

	else if(fondo.getPosition().x > posX)
	{
		fondo.move(-5, 0);
		texto.move(-5, 0);
	}
}

void Boton::AnimacionV(sf::RenderWindow& ventana, int posY)
{
	if(fondo.getPosition().y == posY)
		return;
	
	if(fondo.getPosition().y < posY)
	{
		fondo.move(0, 5);
		texto.move(0, 5);
	}

	else if(fondo.getPosition().y > posY)
	{
		fondo.move(0, -5);
		texto.move(0, -5);
	}
}

sf::RectangleShape& Boton::GetShape() { return fondo; }
sf::Text& Boton::GetTexto() { return texto; }
sf::Color Boton::GetCFondo() { return cFondo; }
sf::Color Boton::GetCMouse() { return cMouse; }
sf::Color Boton::GetCOutlineFondo() { return cOutlineFondo; }
sf::Color Boton::GetCOutlineMouse() { return cOutlineMouse; }

#endif
