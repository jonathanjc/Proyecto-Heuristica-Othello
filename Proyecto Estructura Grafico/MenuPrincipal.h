#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "Boton.h"

class MenuPrincipal
{
	private:
		sf::Text titulo;
	
		Boton nuevaPartida;
		Boton ayuda;
		Boton acercaDe;
		Boton salir;

	public:
		MenuPrincipal();
		MenuPrincipal(sf::Font&, sf::RenderWindow&);
		~MenuPrincipal();

		void Mostrar(sf::RenderWindow&);
		void Animacion(sf::RenderWindow&);

		Boton &GetNuevaPartida();
		Boton &GetAyuda();
		Boton &GetAcercaDe();
		Boton &GetSalir();
};

MenuPrincipal::MenuPrincipal() { }

MenuPrincipal::MenuPrincipal(sf::Font& fuente, sf::RenderWindow &ventana)
{
	this->titulo.setString("Othello!");
	this->titulo.setColor(sf::Color::White);
	this->titulo.setCharacterSize(100);
	this->titulo.setFont(fuente);
	this->titulo.setPosition(ventana.getSize().x/4, -240);

	nuevaPartida = Boton("Nueva Partida", fuente,  500, 50, -500, 200, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	ayuda = Boton("Ayuda", fuente, 500, 50, ventana.getSize().x, 300, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	acercaDe = Boton("Acerda de", fuente, 500, 50, -500, 400, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	salir = Boton("Salir", fuente, 500, 50, ventana.getSize().x, 500, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
}

MenuPrincipal::~MenuPrincipal() { }

void MenuPrincipal::Mostrar(sf::RenderWindow &ventana)
{
	ventana.draw(titulo);
	nuevaPartida.Mostrar(ventana);
	ayuda.Mostrar(ventana);
	acercaDe.Mostrar(ventana);
	salir.Mostrar(ventana);
}

void MenuPrincipal::Animacion(sf::RenderWindow &ventana)
{
	if(titulo.getPosition().y < 20)
		titulo.move(0, 2);
	
	nuevaPartida.AnimacionH(ventana, ventana.getSize().x/2 - nuevaPartida.GetShape().getSize().x/2);
	ayuda.AnimacionH(ventana, ventana.getSize().x/2 - ayuda.GetShape().getSize().x/2);
	acercaDe.AnimacionH(ventana, ventana.getSize().x/2 - acercaDe.GetShape().getSize().x/2);
	salir.AnimacionH(ventana, ventana.getSize().x/2 - salir.GetShape().getSize().x/2);
}

Boton& MenuPrincipal::GetNuevaPartida() { return nuevaPartida; }
Boton& MenuPrincipal::GetAyuda() { return ayuda; }
Boton& MenuPrincipal::GetAcercaDe() { return acercaDe; }
Boton& MenuPrincipal::GetSalir() { return salir; }

#endif
