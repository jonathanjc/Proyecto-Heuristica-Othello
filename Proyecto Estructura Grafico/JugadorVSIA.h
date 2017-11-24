#ifndef JVSIA_H
#define JVSIA_H

class JVSIA
{
    private:
        Boton facil;
		Boton normal;
		Boton regresar;

    public:
		JVSIA();
		JVSIA(sf::Font&, sf::RenderWindow&);
		~JVSIA();

		void Mostrar(sf::RenderWindow&);
		void Animacion(sf::RenderWindow&);

		Boton &GetFacil();
		Boton &GetNormal();
		Boton &GetRegresar();
};

JVSIA::JVSIA() { }

JVSIA::JVSIA(sf::Font& fuente, sf::RenderWindow& ventana)
{
	facil = Boton("Facil", fuente, 500, 50, ventana.getSize().x-(ventana.getSize().x/2+250), ventana.getSize().y+150, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	normal = Boton("Normal", fuente, 500, 50, ventana.getSize().x-(ventana.getSize().x/2+250), ventana.getSize().y+250, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
	regresar = Boton("Regresar", fuente, 500, 50, ventana.getSize().x-(ventana.getSize().x/2+250), ventana.getSize().y+450, sf::Color(68, 255, 137), sf::Color(41, 232, 187), sf::Color::White, sf::Color(0, 157, 196));
}

JVSIA::~JVSIA() { }

void JVSIA::Mostrar(sf::RenderWindow& ventana)
{
	facil.Mostrar(ventana);
	normal.Mostrar(ventana);
	regresar.Mostrar(ventana);
}

void JVSIA::Animacion(sf::RenderWindow& ventana)
{
    facil.AnimacionV(ventana, 200);
	normal.AnimacionV(ventana, 300);
	regresar.AnimacionV(ventana, 500);
}

Boton& JVSIA::GetFacil() { return facil; }
Boton& JVSIA::GetNormal() { return normal; }
Boton& JVSIA::GetRegresar() { return regresar; }

#endif
