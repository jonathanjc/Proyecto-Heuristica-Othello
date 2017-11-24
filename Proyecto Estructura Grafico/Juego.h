#ifndef JUEGO_H
#define JUEGO_H

#include <cmath>

#include "MenuPrincipal.h"
#include "MenuNuevaPartida.h"
#include "AcercaDe.h"
#include "Ayuda.h"

#include "Ficha.h"
#include "Tablero.h"
#include "Jugador.h"
#include "IA.h"
#include "PilaD.h"
#include "Lista.h"
#include "PJugada.h"
#include "JugadorVSIA.h"


class Juego
{
	private:
		sf::RenderWindow ventana;
		sf::Font fuente;
		bool cambioTurno;
		bool mostrarAyuda;
		bool dificultad;

		MenuPrincipal *menuPrincipal;
		MenuNuevaPartida *menuNuevaPartida;
		AcercaDe *acercaDe;
		Ayuda *ayuda;
		JVSIA *jVSIA;

		Tablero *tablero;
		Modo mJuego;

		Jugador *jugador1;
		Jugador *jugador2;
		IA *inteligenciaA;

		Ganador jGanador;

		PilaD<Ficha**> tableros;

		int nFilas;
		int nColum;

		void Start();
		void Update();
		void Mostrar();

		Ganador PVP();
		Ganador PVE();

		void IniciarTablero();

		//--------------------------------------------------------------
		template<class T>
		void Jugada(T*);
		void Horizontal(Ficha);
		void Vertical(Ficha);
		void DiagonalD(Ficha);
		void DiagonalI(Ficha);

		void Limpiar();

		void Cambiar(Ficha);
		void CambiarH(Ficha);
		void CambiarV(Ficha);
		void CambiarDD(Ficha);
		void CambiarDI(Ficha);

		int Min(Ficha**, int, int, int);
		int Max(Ficha**, int, int, int);
		//--------------------------------------------------------------

		void CambiarTurno();
		Estado VerificarTablero();
		Ganador VerificarGanador();
		void AgregarFicha(Ficha, int, int);

		template<class T>
		void MouseEntered(T&, sf::Event);
		template<class T>
		bool MouseClick(T&, sf::Event);

		void Events();

	public:
		Juego(const int, const int, sf::String, const int, const int);
		~Juego();
};

Juego::Juego(const int tamX, const int tamY, sf::String titulo, const int nFilas, const int nColum)
{
	this->nFilas = nFilas;
	this->nColum = nColum;

	sf::VideoMode pantalla = sf::VideoMode::getDesktopMode();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	ventana.create(sf::VideoMode(tamX, tamY), titulo, sf::Style::Close, settings);
	ventana.setVerticalSyncEnabled(true);
	ventana.setFramerateLimit(60);
	ventana.setPosition(sf::Vector2i(pantalla.width/4, pantalla.height/4));

	if(!fuente.loadFromFile("UbuntuMono-Bold.ttf"))
		std::cout << "Error al cargar la fuente" << std::endl;

	menuPrincipal = NULL;
	menuNuevaPartida = NULL;
	acercaDe = NULL;
	ayuda = NULL;
	jVSIA = NULL;

	tablero = NULL;
	mJuego = Nada;
	jugador1 = NULL;
	jugador2 = NULL;

	Start();
}

Juego::~Juego(){ }

void Juego::Start()
{
	menuPrincipal = new MenuPrincipal(fuente, ventana);
	Update();
}

void Juego::Update()
{
	while(ventana.isOpen())
	{
		Events();

		if(mJuego != Nada)
		{
			ventana.clear(sf::Color(sf::Color(192, 192, 192)));

			if(mJuego == PvP)
			{
			    if(cambioTurno)
                    jGanador = VerificarGanador();

				else if(jGanador == Nadie)
					jGanador = PVP();

				if(jGanador != Nadie)
					tablero->MostrarUIGanador(ventana, jGanador);

				if(jugador1->GetTurno())
					tablero->TrianguloAnim(75);
				else
					tablero->TrianguloAnim(145);
			}

			else if(mJuego == PvE)
			{
			    if(cambioTurno)
                    jGanador = VerificarGanador();

				else if(jGanador == Nadie)
					jGanador = PVE();

				if(jGanador != Nadie)
					tablero->MostrarUIGanador(ventana, jGanador);

				if(inteligenciaA->GetTurno())
					tablero->TrianguloAnim(145);
				else
					tablero->TrianguloAnim(75);
			}

			tablero->UpdateUI();
			tablero->MostrarUI(ventana);
			Mostrar();
		}

		else
		{
			ventana.clear(sf::Color(45, 176, 232));

			if(menuPrincipal)
			{
				menuPrincipal->Mostrar(ventana);
				menuPrincipal->Animacion(ventana);
			}

			else if(menuNuevaPartida)
			{
				menuNuevaPartida->Mostrar(ventana);
				menuNuevaPartida->Animacion(ventana);
			}

			else if(acercaDe)
			{
				acercaDe->Mostrar(ventana);
				acercaDe->Animacion(ventana);
			}

			else if(ayuda)
			{
				ayuda->Mostrar(ventana);
				ayuda->Animacion(ventana);
			}

			else if(jVSIA)
            {
                jVSIA->Mostrar(ventana);
                jVSIA->Animacion(ventana);
            }

			else
				ventana.close();
		}

		//Mostrar juego
		ventana.display();
	}
}

template<class T>
void Juego::MouseEntered(T &boton, sf::Event evento)
{
	if(sf::Mouse::getPosition(ventana).x >= boton.GetShape().getPosition().x &&
		sf::Mouse::getPosition(ventana).x <= boton.GetShape().getPosition().x+boton.GetShape().getSize().x &&
		sf::Mouse::getPosition(ventana).y >= boton.GetShape().getPosition().y &&
		sf::Mouse::getPosition(ventana).y <= boton.GetShape().getPosition().y+boton.GetShape().getSize().y)
	{

		boton.GetShape().setFillColor(boton.GetCMouse());
		boton.GetShape().setOutlineColor(boton.GetCOutlineMouse());
		boton.GetTexto().setColor(boton.GetShape().getOutlineColor());
	}

	else
	{
		boton.GetShape().setFillColor(boton.GetCFondo());
		boton.GetShape().setOutlineColor(boton.GetCOutlineFondo());
		boton.GetTexto().setColor(boton.GetShape().getOutlineColor());
	}
}

template<class T>
bool Juego::MouseClick(T &boton, sf::Event evento)
{
	if(sf::Mouse::getPosition(ventana).x >= boton.GetShape().getPosition().x &&
		sf::Mouse::getPosition(ventana).x <= boton.GetShape().getPosition().x+boton.GetShape().getSize().x &&
		sf::Mouse::getPosition(ventana).y >= boton.GetShape().getPosition().y &&
		sf::Mouse::getPosition(ventana).y <= boton.GetShape().getPosition().y+boton.GetShape().getSize().y)

		return true;

	else
		return false;
}

void Juego::Events()
{
	sf::Event evento;

	while(ventana.pollEvent(evento))
	{
		if(evento.type == sf::Event::Closed)
			ventana.close();

		if(evento.type == sf::Event::MouseMoved)
		{
			if(menuPrincipal)
			{
				MouseEntered(menuPrincipal->GetNuevaPartida(), evento);
				MouseEntered(menuPrincipal->GetAyuda(), evento);
				MouseEntered(menuPrincipal->GetAcercaDe(), evento);
				MouseEntered(menuPrincipal->GetSalir(), evento);
			}

			else if(menuNuevaPartida)
			{
				MouseEntered(menuNuevaPartida->GetPVP(), evento);
				MouseEntered(menuNuevaPartida->GetPVE(), evento);
				MouseEntered(menuNuevaPartida->GetRegresar(), evento);
			}

			else if(acercaDe)
				MouseEntered(acercaDe->GetRegresar(), evento);

			else if(ayuda)
				MouseEntered(ayuda->GetRegresar(), evento);

			else if(mJuego != Nada)
			{
				MouseEntered(tablero->GetAtras(), evento);
				MouseEntered(tablero->GetAyuda(), evento);
				MouseEntered(tablero->GetMenu(), evento);
			}

			else if(jVSIA)
            {
                MouseEntered(jVSIA->GetFacil(), evento);
				MouseEntered(jVSIA->GetNormal(), evento);
				MouseEntered(jVSIA->GetRegresar(), evento);
            }
		}

		if(evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left)
		{
			if(menuPrincipal)
			{
				if(MouseClick(menuPrincipal->GetNuevaPartida(), evento))
				{
					std::cout << "Nueva Partida" << std::endl;
					menuPrincipal = NULL;
					menuNuevaPartida = new MenuNuevaPartida(fuente, ventana);
				}

				else if(MouseClick(menuPrincipal->GetAyuda(), evento))
				{
					std::cout << "Ayuda" << std::endl;
					menuPrincipal = NULL;
					ayuda = new Ayuda(ventana, fuente);
				}

				else if(MouseClick(menuPrincipal->GetAcercaDe(), evento))
				{
					std::cout << "AcercaDe" << std::endl;
					menuPrincipal = NULL;
					acercaDe = new AcercaDe(ventana, fuente);
				}

				else if(MouseClick(menuPrincipal->GetSalir(), evento))
				{
					std::cout << "Salir" << std::endl;
					menuPrincipal = NULL;
				}
			}

			else if(menuNuevaPartida)
			{
				if(MouseClick(menuNuevaPartida->GetPVP(), evento))
				{
					std::cout << "Jugador VS Jugador" << std::endl;
					IniciarTablero();
					jugador1 = new Jugador("Jugador 1", Ficha(Negro), true);
					jugador2 = new Jugador("Jugador 2", Ficha(Blanco), false);
					menuNuevaPartida = NULL;
					mJuego = PvP;
				}

				else if(MouseClick(menuNuevaPartida->GetPVE(), evento))
				{
					std::cout << "Jugador VS IA" << std::endl;
					IniciarTablero();
					jugador1 = new Jugador("Jugador 1", Ficha(Negro), true);
					inteligenciaA = new IA("IA", Ficha(Blanco), false);
					menuNuevaPartida = NULL;
					jVSIA = new JVSIA(fuente, ventana);
				}

				else if(MouseClick(menuNuevaPartida->GetRegresar(), evento))
				{
					std::cout << "Regresar" << std::endl;
					menuNuevaPartida = NULL;
					menuPrincipal = new MenuPrincipal(fuente, ventana);
				}
			}

			else if(acercaDe)
			{
				if(MouseClick(acercaDe->GetRegresar(), evento))
				{
					std::cout << "Regresar" << std::endl;
					acercaDe = NULL;
					menuPrincipal = new MenuPrincipal(fuente,ventana);
				}
			}

			else if(ayuda)
			{
				if(MouseClick(ayuda->GetRegresar(), evento))
				{
					std::cout << "Regresar" << std::endl;
					ayuda = NULL;
					menuPrincipal = new MenuPrincipal(fuente, ventana);
				}
			}

			else if(jVSIA)
            {
                if(MouseClick(jVSIA->GetFacil(), evento))
                {
                    std::cout << "Facil" << std::endl;
                    mJuego = PvE;
                    jVSIA = NULL;
                    dificultad = false;
                }

                else if(MouseClick(jVSIA->GetNormal(), evento))
                {
                    std::cout << "Normal" << std::endl;
                    mJuego = PvE;
                    jVSIA = NULL;
                    dificultad = true;
                }

                else if(MouseClick(jVSIA->GetRegresar(), evento))
                {
                    std::cout << "Regresar" << std::endl;
                    jVSIA = NULL;
                    menuPrincipal = new MenuPrincipal(fuente, ventana);
                }
            }

			else if(mJuego != Nada)
			{
				if(mJuego == PvP)
				{
					for(int i=0; i<nFilas; i++)
					{
						for(int j=0; j<nColum; j++)
						{
							if(MouseClick(tablero->GetTablero()[i][j].GetFicha(), evento))
							{
								if(tablero->GetTablero()[i][j] == Azul)
								{
									if(jugador1->GetTurno())
										Cambiar(jugador1->Jugar(tablero, j, i));

									else
										Cambiar(jugador2->Jugar(tablero, j, i));

									CambiarTurno();
								}
							}
						}
					}
				}

				else if(mJuego == PvE)
				{
					if(jugador1->GetTurno())
					{
						for(int i=0; i<nFilas; i++)
						{
							for(int j=0; j<nColum; j++)
							{
								if(MouseClick(tablero->GetTablero()[i][j].GetFicha(), evento))
								{
									if(tablero->GetTablero()[i][j] == Azul)
									{
										ventana.clear(sf::Color(sf::Color(192, 192, 192)));

										Cambiar(jugador1->Jugar(tablero, j, i));
										CambiarTurno();


										//---------------------------Por Ahora--------------------------
										VerificarGanador();
										tablero->UpdateUI();
										tablero->MostrarUI(ventana);
										Mostrar();
										ventana.display();
										sf::sleep(sf::seconds(1));
										//--------------------------------------------------------------
									}
								}
							}
						}
					}
				}

				if(MouseClick(tablero->GetAtras(), evento) && jGanador == Nadie)
				{
					std::cout << "Movimiento anterior..." << std::endl;

					Ficha **tabAux = NULL;

					if(tableros.Eliminar(tabAux) != -1)
					{
						for(int i=0; i<nFilas; i++)
						{
							for(int j=0; j<nColum; j++)
								tablero->GetTablero()[i][j] = tabAux[i][j];
						}

						if(jGanador != Nadie)
							jGanador = Nadie;

						if(cambioTurno)
						{
							cambioTurno = false;
							CambiarTurno();
						}

						CambiarTurno();
					}
				}

				else if(MouseClick(tablero->GetAyuda(), evento) && jGanador == Nadie)
				{
					std::cout << "Ayuda del jugador..." << std::endl;
					mostrarAyuda = true;
				}

				else if(MouseClick(tablero->GetMenu(), evento))
				{
					std::cout << "Menu" << std::endl;
					tablero = NULL;
					mJuego = Nada;
					menuNuevaPartida = NULL;
					jVSIA = NULL;
					menuPrincipal = new MenuPrincipal(fuente, ventana);
				}
			}
		}
	}
}

void Juego::IniciarTablero()
{
	tablero = new Tablero(nFilas, nColum, Verde, fuente);
	jGanador = Nadie;
	cambioTurno = false;
	mostrarAyuda = false;

	Ficha f1(Blanco);
	Ficha f2(Negro);
	Ficha f3(Blanco);
	Ficha f4(Negro);

	AgregarFicha(f1, 3, 3);
	AgregarFicha(f2, 4, 3);
	AgregarFicha(f3, 4, 4);
	AgregarFicha(f4, 3, 4);

	Ficha **aux = NULL;
	while(tableros.Eliminar(aux) != -1){}

	delete aux;
}

void Juego::AgregarFicha(Ficha ficha, int posX, int posY)
{
	ficha.SetPosX(posX);
	ficha.SetPosY(posY);
	tablero->GetTablero()[posY][posX] = ficha;
}

Ganador Juego::PVP()
{
	if(jugador1->GetTurno())
		Jugada(jugador1);

	else
		Jugada(jugador2);

	Estado eTablero = VerificarTablero();
	Ganador ganador = VerificarGanador();

	if(eTablero == Completo)
		return ganador;

	else if(eTablero == Incompleto && tablero->GetNFichasA() == 0)
	{
		if(!cambioTurno)
		{
			CambiarTurno();
			cambioTurno = true;
			return Nadie;
		}

		else
			return ganador;
	}

	else
    {
        cambioTurno = false;
		return Nadie;
    }
}

Ganador Juego::PVE()
{

    int finalFichas;
	if(jugador1->GetTurno())
		Jugada(jugador1);

	else if(!cambioTurno)
	{
	    std::cout << "Juega IA" << std::endl;
	    for(int i=0; i<nFilas; i++)
		{
			for(int j=0; j<nColum; j++){
                 std::cout << tablero->GetTablero()[i][j].GetColor() << " ";
			}
            std::cout<< std::endl;
		}
		VerificarGanador();
		Jugada(inteligenciaA);
		Max(tablero->GetTablero(), tablero->GetNFichasN(), tablero->GetNFichasB(), 0);
        CambiarTurno();
		Jugada(jugador1);
	}

	Estado eTablero = VerificarTablero();
	Ganador ganador = VerificarGanador();

	if(eTablero == Completo)
		return ganador;

	else if(eTablero == Incompleto && tablero->GetNFichasA() == 0)
	{
		if(!cambioTurno)
		{
			CambiarTurno();
			cambioTurno = true;
			return Nadie;
		}

		else
			return ganador;
	}

	else
		return Nadie;
}

void Juego::Mostrar()
{
	sf::RectangleShape casilla(sf::Vector2f(70, 70));
	casilla.setOutlineThickness(1);
	casilla.setFillColor(sf::Color(119, 255, 147));
	casilla.setOutlineColor(sf::Color::Black);

	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			casilla.setPosition(j*71 + 15, i*71 + 15);
			ventana.draw(casilla);

			if(tablero->GetTablero()[i][j] != Ninguno)
			{
				sf::CircleShape ficha(25);
				ficha.setOutlineThickness(1);
				ficha.setOutlineColor(sf::Color::Black);

				if(tablero->GetTablero()[i][j] == Azul)
					ficha.setFillColor(sf::Color(112, 184, 255));

				else if(tablero->GetTablero()[i][j] == Negro)
					ficha.setFillColor(sf::Color(64, 64, 64));

				else if(tablero->GetTablero()[i][j] == Blanco)
					ficha.setFillColor(sf::Color::White);

				else if(tablero->GetTablero()[i][j] == Rojo)
					ficha.setFillColor(sf::Color(255, 101, 101));

				ficha.setPosition(casilla.getPosition().x + ficha.getRadius()/2, casilla.getPosition().y + ficha.getRadius()/2);

				if(tablero->GetTablero()[i][j] == Azul && mostrarAyuda)
					ventana.draw(ficha);

				else if(tablero->GetTablero()[i][j] != Azul)
					ventana.draw(ficha);
			}

			tablero->GetTablero()[i][j].GetFicha().GetShape().setPosition(casilla.getPosition());
		}
	}
}

template<class T>
void Juego::Jugada(T* jugador)
{
	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			if(tablero->GetTablero()[i][j] == jugador->GetFicha().GetColor())
			{
				Horizontal(tablero->GetTablero()[i][j]);
				Vertical(tablero->GetTablero()[i][j]);
				DiagonalD(tablero->GetTablero()[i][j]);
				DiagonalI(tablero->GetTablero()[i][j]);
			}
		}
	}
}

void Juego::Horizontal(Ficha ficha)
{
	int i=ficha.GetPosX()+1;

	for(; i<nColum; i++)
	{
		if(tablero->GetTablero()[ficha.GetPosY()][i] == Ninguno)
			break;

		if(tablero->GetTablero()[ficha.GetPosY()][i] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[ficha.GetPosY()][i] == Azul)
			break;
	}

	if(i<nColum)
	{
		if((i-1) != ficha.GetPosX() && tablero->GetTablero()[ficha.GetPosY()][i] == Ninguno)
		{
			tablero->GetTablero()[ficha.GetPosY()][i].SetColor(Azul);
			tablero->GetTablero()[ficha.GetPosY()][i].SetPosX(i);
			tablero->GetTablero()[ficha.GetPosY()][i].SetPosY(ficha.GetPosY());
		}
	}

	i=ficha.GetPosX()-1;

	for(; i>=0; i--)
	{
		if(tablero->GetTablero()[ficha.GetPosY()][i] == Ninguno)
			break;

		if(tablero->GetTablero()[ficha.GetPosY()][i] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[ficha.GetPosY()][i] == Azul)
			break;
	}

	if(i>=0)
	{
		if((i+1) != ficha.GetPosX() && tablero->GetTablero()[ficha.GetPosY()][i] == Ninguno)
		{
			tablero->GetTablero()[ficha.GetPosY()][i].SetColor(Azul);
			tablero->GetTablero()[ficha.GetPosY()][i].SetPosX(i);
			tablero->GetTablero()[ficha.GetPosY()][i].SetPosY(ficha.GetPosY());
		}
	}
}

void Juego::Vertical(Ficha ficha)
{
	int i=ficha.GetPosY()+1;

	for(; i<nFilas; i++)
	{
		if(tablero->GetTablero()[i][ficha.GetPosX()] == Ninguno)
			break;

		if(tablero->GetTablero()[i][ficha.GetPosX()] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[i][ficha.GetPosX()] == Azul)
			break;
	}

	if(i<nFilas)
	{
		if((i-1) != ficha.GetPosY() && tablero->GetTablero()[i][ficha.GetPosX()] == Ninguno)
		{
			tablero->GetTablero()[i][ficha.GetPosX()].SetColor(Azul);
			tablero->GetTablero()[i][ficha.GetPosX()].SetPosX(ficha.GetPosX());
			tablero->GetTablero()[i][ficha.GetPosX()].SetPosY(i);
		}
	}

	i=ficha.GetPosY()-1;

	for(; i>=0; i--)
	{
		if(tablero->GetTablero()[i][ficha.GetPosX()] == Ninguno)
			break;

		if(tablero->GetTablero()[i][ficha.GetPosX()] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[i][ficha.GetPosX()] == Azul)
			break;
	}

	if(i>=0)
	{
		if((i+1) != ficha.GetPosY() && tablero->GetTablero()[i][ficha.GetPosX()] == Ninguno)
		{
			tablero->GetTablero()[i][ficha.GetPosX()].SetColor(Azul);
			tablero->GetTablero()[i][ficha.GetPosX()].SetPosX(ficha.GetPosX());
			tablero->GetTablero()[i][ficha.GetPosX()].SetPosY(i);
		}
	}
}

void Juego::DiagonalD(Ficha ficha)
{
	int posX = ficha.GetPosX()+1;
	int posY = ficha.GetPosY()-1;

	for(; posX<nColum && posY>=0; posX++, posY--)
	{
		if(tablero->GetTablero()[posY][posX] == Ninguno)
			break;

		if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[posY][posX] == Azul)
			break;
	}

	if(posX<nColum && posY>=0)
	{
		if((posX-1) != ficha.GetPosX() && (posY+1) != ficha.GetPosY() && tablero->GetTablero()[posY][posX] == Ninguno)
		{
			tablero->GetTablero()[posY][posX].SetColor(Azul);
			tablero->GetTablero()[posY][posX].SetPosX(posX);
			tablero->GetTablero()[posY][posX].SetPosY(posY);
		}
	}

	posX = ficha.GetPosX()-1;
	posY = ficha.GetPosY()+1;

	for(; posX>=0 && posY<nFilas; posX--, posY++)
	{
		if(tablero->GetTablero()[posY][posX] == Ninguno)
			break;

		if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[posY][posX] == Azul)
			break;
	}

	if(posX>=0 && posY<nFilas)
	{
		if((posX+1) != ficha.GetPosX() && (posY-1) != ficha.GetPosY() && tablero->GetTablero()[posY][posX] == Ninguno)
		{
			tablero->GetTablero()[posY][posX].SetColor(Azul);
			tablero->GetTablero()[posY][posX].SetPosX(posX);
			tablero->GetTablero()[posY][posX].SetPosY(posY);
		}
	}
}

void Juego::DiagonalI(Ficha ficha)
{
	int posX = ficha.GetPosX()-1;
	int posY = ficha.GetPosY()-1;

	for(; posX>=0 && posY>=0; posX--, posY--)
	{
		if(tablero->GetTablero()[posY][posX] == Ninguno)
			break;

		if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[posY][posX] == Azul)
			break;
	}

	if(posX>=0 && posY>=0)
	{
		if((posX+1) != ficha.GetPosX() && (posY+1) != ficha.GetPosY() && tablero->GetTablero()[posY][posX] == Ninguno)
		{
			tablero->GetTablero()[posY][posX].SetColor(Azul);
			tablero->GetTablero()[posY][posX].SetPosX(posX);
			tablero->GetTablero()[posY][posX].SetPosY(posY);
		}
	}

	posX = ficha.GetPosX()+1;
	posY = ficha.GetPosY()+1;

	for(; posX<nColum && posY<nFilas; posX++, posY++)
	{
		if(tablero->GetTablero()[posY][posX] == Ninguno)
			break;

		if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			break;

		if(tablero->GetTablero()[posY][posX] == Azul)
			break;
	}

	if(posX<nColum && posY<nFilas)
	{
		if((posX-1) != ficha.GetPosX() && (posY-1) != ficha.GetPosY() && tablero->GetTablero()[posY][posX] == Ninguno)
		{
			tablero->GetTablero()[posY][posX].SetColor(Azul);
			tablero->GetTablero()[posY][posX].SetPosX(posX);
			tablero->GetTablero()[posY][posX].SetPosY(posY);
		}
	}
}

void Juego::Limpiar()
{
	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			if(tablero->GetTablero()[i][j] == Azul)
				tablero->GetTablero()[i][j].SetColor(Ninguno);
		}
	}
}

void Juego::CambiarH(Ficha ficha)
{
	int posX = ficha.GetPosX()+1;
	bool cambiar = false;

	if(posX < nColum)
	{
		while(tablero->GetTablero()[ficha.GetPosY()][posX] != ficha.GetColor())
		{
			if(tablero->GetTablero()[ficha.GetPosY()][posX] == Ninguno)
				break;

			if(tablero->GetTablero()[ficha.GetPosY()][posX] == Azul)
				break;

			if(posX < nColum-1)
				posX++;

            else
                break;

			if(tablero->GetTablero()[ficha.GetPosY()][posX] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosX()+1; i<posX; i++)
			{
				ficha.SetPosX(i);
				tablero->GetTablero()[ficha.GetPosY()][i].SetColor(ficha.GetColor());
				tablero->GetTablero()[ficha.GetPosY()][i].SetPosX(ficha.GetPosX());
			}
		}
	}

	posX = ficha.GetPosX()-1;
	cambiar = false;

	if(posX >= 0)
	{
		while(tablero->GetTablero()[ficha.GetPosY()][posX] != ficha.GetColor())
		{
			if(tablero->GetTablero()[ficha.GetPosY()][posX] == Ninguno)
				break;

			if(tablero->GetTablero()[ficha.GetPosY()][posX] == Azul)
				break;

			if(posX > 1)
				posX--;

            else
                break;

			if(tablero->GetTablero()[ficha.GetPosY()][posX] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosX()-1; i>posX; i--)
			{
				ficha.SetPosX(i);
				tablero->GetTablero()[ficha.GetPosY()][i].SetColor(ficha.GetColor());
				tablero->GetTablero()[ficha.GetPosY()][i].SetPosX(ficha.GetPosX());
			}
		}
	}
}

void Juego::CambiarV(Ficha ficha)
{
	int posY = ficha.GetPosY()+1;
	bool cambiar = false;

	if(posY < nFilas)
	{
		while(tablero->GetTablero()[posY][ficha.GetPosX()] != ficha.GetColor())
		{
			if(tablero->GetTablero()[posY][ficha.GetPosX()] == Ninguno)
				break;

			if(tablero->GetTablero()[posY][ficha.GetPosX()] == Azul)
				break;

			if(posY < nFilas-1)
				posY++;

            else
                break;

			if(tablero->GetTablero()[posY][ficha.GetPosX()] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosY()+1; i<posY; i++)
			{
				ficha.SetPosY(i);
				tablero->GetTablero()[i][ficha.GetPosX()].SetColor(ficha.GetColor());
				tablero->GetTablero()[i][ficha.GetPosX()].SetPosY(ficha.GetPosY());
			}
		}
	}

	posY = ficha.GetPosY()-1;
	cambiar = false;

	if(posY >= 0)
	{
		while(tablero->GetTablero()[posY][ficha.GetPosX()] != ficha.GetColor())
		{
			if(tablero->GetTablero()[posY][ficha.GetPosX()] == Ninguno)
				break;

			if(tablero->GetTablero()[posY][ficha.GetPosX()] == Azul)
				break;

			if(posY > 1)
				posY--;

            else
                break;

			if(tablero->GetTablero()[posY][ficha.GetPosX()] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosY()-1; i>posY; i--)
			{
				ficha.SetPosY(i);
				tablero->GetTablero()[i][ficha.GetPosX()].SetColor(ficha.GetColor());
				tablero->GetTablero()[i][ficha.GetPosX()].SetPosY(ficha.GetPosY());
			}
		}
	}
}

void Juego::CambiarDD(Ficha ficha)
{
	int posY = ficha.GetPosY()-1;
	int posX = ficha.GetPosX()+1;
	bool cambiar = false;

	if(posY>=0 && posX<nColum)
	{
		while(tablero->GetTablero()[posY][posX] != ficha.GetColor())
		{
			if(tablero->GetTablero()[posY][posX] == Ninguno)
				break;

			if(tablero->GetTablero()[posY][posX] == Azul)
				break;

			if(posY>0 && posX<nColum-1)
			{
				posX++;
				posY--;
			}

			else
                break;

			if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosX()+1, j=ficha.GetPosY()-1; i<posX && j>posY; i++, j--)
			{
				ficha.SetPosX(i);
				ficha.SetPosY(j);
				tablero->GetTablero()[j][i].SetColor(ficha.GetColor());
				tablero->GetTablero()[j][i].SetPosX(ficha.GetPosX());
				tablero->GetTablero()[j][i].SetPosY(ficha.GetPosY());
			}
		}
	}

	posX = ficha.GetPosX()-1;
	posY = ficha.GetPosY()+1;
	cambiar = false;

	if(posX >=0 && posY<nFilas)
	{
		while(tablero->GetTablero()[posY][posX] != ficha.GetColor())
		{
			if(tablero->GetTablero()[posY][posX] == Ninguno)
				break;

			if(tablero->GetTablero()[posY][posX] == Azul)
				break;

			if(posX>0 && posY<nFilas-1)
			{
				posX--;
				posY++;
			}

			else
                break;

			if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosX()-1, j=ficha.GetPosY()+1; i>posX && j<posY; i--, j++)
			{
				ficha.SetPosX(i);
				ficha.SetPosY(j);
				tablero->GetTablero()[j][i].SetColor(ficha.GetColor());
				tablero->GetTablero()[j][i].SetPosX(ficha.GetPosX());
				tablero->GetTablero()[j][i].SetPosY(ficha.GetPosY());
			}
		}
	}
}

void Juego::CambiarDI(Ficha ficha)
{
	int posY = ficha.GetPosY()-1;
	int posX = ficha.GetPosX()-1;
	bool cambiar = false;

	if(posY>=0 && posX>=0)
	{
		while(tablero->GetTablero()[posY][posX] != ficha.GetColor())
		{
			if(tablero->GetTablero()[posY][posX] == Ninguno)
				break;

			if(tablero->GetTablero()[posY][posX] == Azul)
				break;

			if(posY>0 && posX>0)
			{
				posX--;
				posY--;
			}

			else
                break;

			if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosX()-1, j=ficha.GetPosY()-1; i>posX && j>posY; i--, j--)
			{
				ficha.SetPosX(i);
				ficha.SetPosY(j);
				tablero->GetTablero()[j][i].SetColor(ficha.GetColor());
				tablero->GetTablero()[j][i].SetPosX(ficha.GetPosX());
				tablero->GetTablero()[j][i].SetPosY(ficha.GetPosY());
			}
		}
	}

	posX = ficha.GetPosX()+1;
	posY = ficha.GetPosY()+1;
	cambiar = false;

	if(posY<nFilas && posX<nColum)
	{
		while(tablero->GetTablero()[posY][posX] != ficha.GetColor())
		{
			if(tablero->GetTablero()[posY][posX] == Ninguno)
				break;

			if(tablero->GetTablero()[posY][posX] == Azul)
				break;

			if(posY<nFilas-1 && posX<nColum-1)
			{
				posX++;
				posY++;
			}

			else
                break;

			if(tablero->GetTablero()[posY][posX] == ficha.GetColor())
			{
				cambiar = true;
				break;
			}
		}

		if(cambiar)
		{
			for(int i=ficha.GetPosX()+1, j=ficha.GetPosY()+1; i<posX && j<posY; i++, j++)
			{
				ficha.SetPosX(i);
				ficha.SetPosY(j);
				tablero->GetTablero()[j][i].SetColor(ficha.GetColor());
				tablero->GetTablero()[j][i].SetPosX(ficha.GetPosX());
				tablero->GetTablero()[j][i].SetPosY(ficha.GetPosY());
			}
		}
	}
}

void Juego::Cambiar(Ficha ficha)
{
	//------------------------------------------------------
	Ficha **tabAux = new Ficha*[nFilas];

	for(int i=0; i<nFilas; i++)
		tabAux[i] = new Ficha[nColum];

	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			tabAux[i][j] = tablero->GetTablero()[i][j];

			if(tablero->GetTablero()[i][j].GetPosX() == ficha.GetPosX() && tablero->GetTablero()[i][j].GetPosY() == ficha.GetPosY())
				tabAux[i][j].SetColor(Ninguno);
		}
	}

	tableros.Agregar(tabAux);
	//------------------------------------------------------

	CambiarH(ficha);
	CambiarV(ficha);
	CambiarDD(ficha);
	CambiarDI(ficha);
}

Estado Juego::VerificarTablero()
{
	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			if(tablero->GetTablero()[i][j].GetColor() == Ninguno || tablero->GetTablero()[i][j] == Azul)
				return Incompleto;
		}
	}

	return Completo;
}

Ganador Juego::VerificarGanador()
{
	tablero->SetNFichasA(0);
	tablero->SetNFichasB(0);
	tablero->SetNFichasN(0);

	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			if(tablero->GetTablero()[i][j] == Azul)
				tablero->SetNFichasA(tablero->GetNFichasA()+1);
			else if(tablero->GetTablero()[i][j] == Blanco)
				tablero->SetNFichasB(tablero->GetNFichasB()+1);
			else if(tablero->GetTablero()[i][j] == Negro)
				tablero->SetNFichasN(tablero->GetNFichasN()+1);
		}
	}

	if(tablero->GetNFichasN() > tablero->GetNFichasB())
		return FichaN;

	if(tablero->GetNFichasB() > tablero->GetNFichasN())
		return FichaB;

	return Empate;
}

void Juego::CambiarTurno()
{
	mostrarAyuda = false;

	jugador1->SetTurno(!jugador1->GetTurno());

	if(jugador2)
		jugador2->SetTurno(!jugador2->GetTurno());

	else
		inteligenciaA->SetTurno(!inteligenciaA->GetTurno());

	Limpiar();
}

int Juego::Min(Ficha** tab, int nFichasN, int nFichasB, int cont)
{
	cont++;
	Ficha** tabInicial = new Ficha*[nFilas];
	for(int i=0; i<nFilas; i++)
		tabInicial[i] = new Ficha[nColum];

	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
			tabInicial[i][j] = tab[i][j];
	}

	Lista<PJugada> pJugadas;

	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			if(tab[i][j] == Azul)
			{
				//----------------------------Cambio ficha------------------------------
				Cambiar(jugador1->Jugar(tablero, j, i));
				VerificarGanador();
				pJugadas.AgregarU(PJugada(j, i, abs(nFichasN - tablero->GetNFichasN()), 0));

				//----------------------------Reinicio tablero original-----------------
				for(int i=0; i<nFilas; i++)
				{
					for(int j=0; j<nColum; j++)
						tablero->GetTablero()[i][j] = tabInicial[i][j];
				}
			}
		}
	}

	Nodo<PJugada> *nLista = pJugadas.GetNodoLista();

	while(nLista)
	{
		Cambiar(jugador1->Jugar(tablero, nLista->GetElemento().GetPosX(), nLista->GetElemento().GetPosY()));
		VerificarGanador();
		//----------------------------Reinicio tablero original-----------------
		for(int i=0; i<nFilas; i++)
		{
			for(int j=0; j<nColum; j++)
				tablero->GetTablero()[i][j] = tabInicial[i][j];
		}

		delete tabInicial;

		if(nFichasB > nFichasN)
			nLista->GetElemento().SetValor(1);

		else if(nFichasB < nFichasN)
			nLista->GetElemento().SetValor(-1);

		else
			nLista->GetElemento().SetValor(0);

		nLista = nLista->GetSiguiente();
	}

    delete nLista;

    if(cont < 4 && !cambioTurno)
        Max(tablero->GetTablero(), nFichasN, nFichasB, cont);
}

int Juego::Max(Ficha** tab, int nFichasN, int nFichasB, int cont)
{
	cont++;
	Ficha** tabInicial = new Ficha*[nFilas];
	for(int i=0; i<nFilas; i++)
		tabInicial[i] = new Ficha[nColum];

	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
			tabInicial[i][j] = tab[i][j];
	}


	Lista<PJugada> pJugadas;
    int nPJugadas = 0;
	for(int i=0; i<nFilas; i++)
	{
		for(int j=0; j<nColum; j++)
		{
			if(tab[i][j] == Azul)
			{
				//----------------------------Cambio ficha------------------------------
				Cambiar(inteligenciaA->Jugar(tablero, j, i));
				VerificarGanador();
				if(nPJugadas < 25)
                {
                    nPJugadas++;
                    pJugadas.AgregarU(PJugada(j, i, abs(nFichasB - tablero->GetNFichasB()), 0));
                }
				//----------------------------Reinicio tablero original-----------------
				for(int i=0; i<nFilas; i++)
				{
					for(int j=0; j<nColum; j++)
						tablero->GetTablero()[i][j] = tabInicial[i][j];
				}
			}
		}
	}

	Nodo<PJugada> *nLista = pJugadas.GetNodoLista();

	while(nLista)
	{
		Cambiar(inteligenciaA->Jugar(tablero, nLista->GetElemento().GetPosX(), nLista->GetElemento().GetPosY()));
		VerificarGanador();

		if(cont < 4 && !cambioTurno)
			Min(tablero->GetTablero(), nFichasN, nFichasB, cont);

		//----------------------------Reinicio tablero original-----------------
		for(int i=0; i<nFilas; i++)
		{
			for(int j=0; j<nColum; j++)
				tablero->GetTablero()[i][j] = tabInicial[i][j];
		}

		if(nFichasB > nFichasN)
			nLista->GetElemento().SetValor(1);

		if(nFichasB < nFichasN)
			nLista->GetElemento().SetValor(-1);

		if(nFichasB == nFichasN)
			nLista->GetElemento().SetValor(0);

		nLista = nLista->GetSiguiente();
	}

    delete tabInicial;

	nLista = pJugadas.GetNodoLista();
	int nMayor = 0;

    if(dificultad)
    {
        while(nLista)
        {
            if(nLista->GetElemento().GetValor() >= 0)
            {
                if(nLista->GetElemento().GetNFichas() > nMayor)
                    nMayor = nLista->GetElemento().GetNFichas();
            }

            nLista = nLista->GetSiguiente();
        }

        nLista = pJugadas.GetNodoLista();

        while(nLista && nLista->GetElemento().GetNFichas() != nMayor)
            nLista = nLista->GetSiguiente();

        if(!nLista)
        {
            nLista = pJugadas.GetNodoLista();
            while(nLista)
            {
                if(nLista->GetElemento().GetValor() == -1)
                    break;

                nLista = nLista->GetSiguiente();
            }
        }
    }

    else
    {
        while(nLista)
        {
            nMayor = 64;
            if(nLista->GetElemento().GetNFichas() < nMayor)
                nMayor = nLista->GetElemento().GetNFichas();

            nLista = nLista->GetSiguiente();
        }

        nLista = pJugadas.GetNodoLista();

        while(nLista && nLista->GetElemento().GetNFichas() != nMayor)
            nLista = nLista->GetSiguiente();

        if(!nLista)
        {
            nLista = pJugadas.GetNodoLista();
            while(nLista)
            {
                if(nLista->GetElemento().GetValor() == 1)
                    break;

                nLista = nLista->GetSiguiente();
            }

        }
    }

	if(nLista)
		Cambiar(inteligenciaA->Jugar(tablero, nLista->GetElemento().GetPosX(), nLista->GetElemento().GetPosY()));

    std::cout << "IA Jugo en X: " << nLista->GetElemento().GetPosX() << " Y: " << nLista->GetElemento().GetPosY() << std::endl;


    delete nLista;
}

#endif
