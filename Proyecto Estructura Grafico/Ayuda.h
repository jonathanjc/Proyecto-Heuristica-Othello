#ifndef AYUDA_H
#define AYUDA_H

class Ayuda
{
	private:
		sf::Text titulo;
		sf::Text texto;

		Boton regresar;
		
	public:
		Ayuda();
		Ayuda(sf::RenderWindow&, sf::Font&);
		~Ayuda();

		void Mostrar(sf::RenderWindow&);
		void Animacion(sf::RenderWindow&);

		Boton& GetRegresar();
};

Ayuda::Ayuda() { }

Ayuda::Ayuda(sf::RenderWindow& ventana, sf::Font& fuente)
{
	this->titulo.setString("Ayuda");
	this->titulo.setColor(sf::Color::White);
	this->titulo.setCharacterSize(60);
	this->titulo.setFont(fuente);
	this->titulo.setPosition(ventana.getSize().x-(ventana.getSize().x/2+titulo.getLocalBounds().width/2), -240);

	this->texto = titulo;
	this->texto.setCharacterSize(18);
	this->texto.setPosition(80, 95);

	sf::String t = "Othello un juego por turnos alternados. En cada turno, el jugador\n";
				t+="debe poner una ficha en una posicion del tablero en la que se \"coma\"\n";
				t+="al menos una ficha del jugador contrario.\n";
				t+="\nVeamos cuando un jugador come una ficha y cuando no.\n";
				t+="\nSupongamos que ponemos una ficha negra. Recorreremos el tablero por\n";
				t+="ejemplo hacia la derecha a partir de su posicion, hasta encontrar otra\n";
				t+="ficha negra. Si entre estas dos fichas TODAS las casillas tienen una\n";
				t+="ficha blanca, se las da la vuelta, pasando a ser negras. Esto es lo que\n";
				t+="nosotros llamamos \"comer\" fichas blancas. La accion se repite en las\n";
				t+="ocho posibles direcciones: arriba, abajo, izquierda, derecha, y las \n";
				t+="cuatro diagonales.\n";
				t+="\nAlgunas veces, el jugador que posee el turno no puede poner en ninguna\n";
				t+="casilla, y debe ceder el turno al otro jugador. En caso de que ninguno\n";
				t+="de los dos jugadores pueda poner ficha, se da la partida por finalizada,\n";
				t+="y ganara el que mas fichas de su color tenga en el tablero en ese momento.";

	this->texto.setString(t);

	regresar = Boton("Regresar", fuente, 500, 50, -500, 500, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
}

Ayuda::~Ayuda() { }

void Ayuda::Mostrar(sf::RenderWindow& ventana)
{
	ventana.draw(titulo);
	ventana.draw(texto);
	regresar.Mostrar(ventana);
}

void Ayuda::Animacion(sf::RenderWindow& ventana)
{
	if(titulo.getPosition().y < 16)
		titulo.move(0, 2);
	
	regresar.AnimacionH(ventana, ventana.getSize().x/2 - regresar.GetShape().getSize().x/2);
}

Boton& Ayuda::GetRegresar() { return regresar; }

#endif
