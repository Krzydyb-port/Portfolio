#pragma once
#include "define.h"
#include <string>
#include "Menu.h"
#include "Control.h"
/**Klasa bêd¹ca interfejsem gry*/
class Interface {
private:
	sf::RenderWindow window; /**Okno w którym rysowany jest program (1280x720) natywnie*/
	Menu *menu; /**Wska¿nik na aktualne menu*/
	Control control; /**Obiekt klasy obs³uguj¹cej input u¿ytkownika*/
	sf::Texture background; /**Tekstura t³a*/
	sf::Font letters; /**Font napisów na przyciskach*/
	std::string gameFlag = ""; /**Flaga czy input przyjmuje menu czy gra*/
public:
	/**Kontruktro Interfacu*/
	Interface()
		: window(sf::VideoMode(1280, 720), "sfml works!", sf::Style::Titlebar ) {
		letters.loadFromFile("Fonts/myfont.ttf");
		background.loadFromFile("Textures/background.png");
		menu = new MainMenu(window,background,letters);
	};
	~Interface() {};
	/**G³ówna pêtla programu*/
	const void mainLoop()
	{
		sf::Clock clock;

		while (window.isOpen())
		{
			if (gameFlag == "GAME") 
			{
				((GameMenu*)menu)->checkBombs();
			}
			sf::Event event;
			while (window.pollEvent(event))
			{
					if (gameFlag == "GAME")
					{
						triggerGame();
						if (((GameMenu*)menu)->win() == true)
						{
							gameFlag = "";
							delete menu;
							background.loadFromFile(PATH_WIN);
							menu = new WinMenu(window, background, letters);
						}

					}
					else
					{
						if (clock.getElapsedTime().asMilliseconds() > ACTION_TIME)
						{
							triggerMenu();
						}
					}
					clock.restart();
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(*menu);
			window.display();
		}

	};
	/**Funkcja przekazuj¹ca input z obiektu control do menu i reaguj¹ca na odpowiedzi przycisków z menu*/
	std::string triggerMenu()
	{
		Control::KEYBOARD key = control.input();
		std::string request = menu->triggerButton(key);
		if (request == "END")
		{
			window.close();
		}
		else if (request == "HOW")
		{
			background.loadFromFile("Textures/backgroundHow.png");
			delete	menu;
			menu = new HelpMenu(window,background,letters);
		}
		else if (request == "RETURN")
		{
			background.loadFromFile("Textures/background.png");
			delete	menu;
			menu = new MainMenu(window, background, letters);
		}
		else if (request == "GAME_MENU")
		{
			background.loadFromFile("Textures/background.png");
			delete	menu;
			menu = new GameMenu(window, background, letters);
		}
		else if (request == "LEVEL1")
		{
			gameFlag = "GAME";
		}
		return "";
	}
	/**Funkcja przekazuj¹ca input z obiektu control do gry*/
	void triggerGame()
	{
		Control::KEYBOARD key = control.input();
		((GameMenu*)menu)->sendToGame(key);
		if (key == Control::KEYBOARD::ESC)
		{
			gameFlag = "";
		}
		
	}
};
