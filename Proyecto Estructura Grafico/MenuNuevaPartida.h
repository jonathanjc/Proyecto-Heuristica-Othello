#ifndef MENU_NUEVA_PARTIDA_H
#define MENU_NUEVA_PARTIDA_H

class MenuNuevaPartida
{
	private:
		sf::Text titulo;

		Boton pvp;
		Boton pve;
		Boton regresar;
	
	public:
		MenuNuevaPartida();
		MenuNuevaPartida(sf::Font&, sf::RenderWindow&);
		~MenuNuevaPartida();
		
		void Mostrar(sf::RenderWindow&);
		void Animacion(sf::RenderWindow&);

		Boton &GetPVP();
		Boton &GetPVE();
		Boton &GetRegresar();
};

MenuNuevaPartida::MenuNuevaPartida() { }

MenuNuevaPartida::MenuNuevaPartida(sf::Font &fuente, sf::RenderWindow &ventana)
{
	this->titulo.setString("Nueva Partida");
	this->titulo.setColor(sf::Color::White);
	this->titulo.setCharacterSize(100);
	this->titulo.setFont(fuente);
	this->titulo.setPosition(-800, 20);

	pvp = Boton("Jugador VS Jugador", fuente, 500, 50, ventana.getSize().x-(ventana.getSize().x/2+250), ventana.getSize().y+150, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	pve = Boton("Jugador VS IA", fuente, 500, 50, ventana.getSize().x-(ventana.getSize().x/2+250), ventana.getSize().y+250, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	regresar = Boton("Regresar", fuente, 500, 50, ventana.getSize().x-(ventana.getSize().x/2+250), ventana.getSize().y+450, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
}

MenuNuevaPartida::~MenuNuevaPartida() { }

void MenuNuevaPartida::Mostrar(sf::RenderWindow& ventana)
{
	ventana.draw(titulo);
	pvp.Mostrar(ventana);
	pve.Mostrar(ventana);
	regresar.Mostrar(ventana);
}

void MenuNuevaPartida::Animacion(sf::RenderWindow& ventana)
{
	if(titulo.getPosition().x < (ventana.getSize().x-(ventana.getSize().x/2+titulo.getLocalBounds().width/2)))
		titulo.move(8, 0);
		
	pvp.AnimacionV(ventana, 200);
	pve.AnimacionV(ventana, 300);
	regresar.AnimacionV(ventana, 500);
}

Boton& MenuNuevaPartida::GetPVP() { return pvp; }
Boton& MenuNuevaPartida::GetPVE() { return pve; }
Boton& MenuNuevaPartida::GetRegresar() { return regresar; }

#endif
