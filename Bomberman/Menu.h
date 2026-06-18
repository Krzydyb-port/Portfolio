#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Game.h"
#include <SFML/Window/Keyboard.hpp>

/**
* Klasa abstrakcji reprezentuj¹ca menu, aspekt graficzny na podstawie zestawu bibliotek SFML
*/
class Menu : public sf::Drawable {
protected:
	sf::Sprite background; /*!< Sprite t³a menu*/
	std::vector<Button*> buttons; /*!< Vector wskaŸnków na przyciski, które zawiera menu*/
	int current;	/*!< numer akutalnie zaznaczonego przycisku*/
public:
	/** Funkcja czysto virtualna, odpowiada za ³adowanie */
	virtual void loadTextures() = 0; 
	/** Funkcja czysto virtualna, obs³uga ¿¹dañ od interfejsu, wysy³anie ¿¹dañ do buttonów*/
	virtual std::string triggerButton(Control::KEYBOARD key /**< Nazwa klawisza */) = 0; 
	/** Czysto wirtualna funkcja rysuj¹ca, implementacjia z biblioteki SFML*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
/**
* Klasa reprezentuj¹ca Menu g³ówne gry
*/
class MainMenu : public Menu  {
private:
	sf::Texture basicButtonTex; /*!< Tekstóra wszystkich przycisków menu*/
public:
	/** Konstruktor MainMenu tworz¹cy przyciski i ustawiajacy ich pozycje w menu, akutalnie wybranym przyciskiem jest pierwszy przycisk w liœcie */
	MainMenu(const sf::RenderWindow& window/**Okno wed³ug którego, skalowane jest ustawienie przycisków*/, const sf::Texture& parse/** Tekstura, t³a menu*/, const sf::Font& font/**G³ówny font menu*/)
	{
		background.setTexture(parse); 
		loadTextures();
		buttons.push_back(new ButtonGameMenu(basicButtonTex,font));
		buttons.push_back(new ButtonHowToPlay(basicButtonTex,font));
		buttons.push_back(new ButtonEnd(basicButtonTex,font));
		sf::Vector2f pos(0, 0);
		for (int i = 0; i < buttons.size(); i++)
		{

			pos.x = (window.getSize().x - buttons[i]->getSpriteRect().width) / 2;
			pos.y = (1+i*(window.getSize().y - buttons[i]->getSpriteRect().height / 2) / buttons.size())+100;
			buttons[i]->upadatePosition(pos);

		}
		current = 0;
		buttons[current]->hint(1);
	};
	/** Funkcja obs³uguj¹ca ¿¹dania od interfejsu i przekazujaca odpowiedzi od przycisków oraz, implementuj¹ca poruszanie siê po menu */
	std::string triggerButton(Control::KEYBOARD key/**< Nazwa klawisza */)
	{
		switch(key)
		{
		case Control::KEYBOARD::Up:
			buttons[current]->hint(0);
			if (current == 0)
			{
				current = buttons.size()-1;
			}
			else
			{
				current--;
			}
			buttons[current]->hint(1);
			break;
		case Control::KEYBOARD::Down:
			buttons[current]->hint(0);
			if (current == buttons.size() - 1)
			{
				current = 0;
			}
			else
			{
				current++;
			}
			buttons[current]->hint(1);
			break;
			case Control::KEYBOARD::Enter:
				return buttons[current]->buttonRequest(key);
				break;
		default:
			break;
		}

		return "";
	}
	/**Funkcja wczytuj¹ca do pola basicButtonTex, tekstury przycisku */
	void loadTextures()
	{
		basicButtonTex.loadFromFile(PATH_BUTTON);
	};
	/** Funkcja rysuj¹ca wszystkie przyciski i t³o menu */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(background, states);
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->draw(target, states);
		}
	};
};


/**
* Klasa reprezentuj¹ca Menu gry, zawiera wybór iloœci graczy, mape oraz w³aœciwa gre
*/
class GameMenu : public Menu {
private:
	sf::Texture basicButtonTex; /*!< Tekstóra wszystkich przycisków obs³ugi menu*/
	sf::Texture mapTex[MAP_COUNT]; /*!< Mapa tekstur gdzie kluczem jest nazwa obiektu, a wartoœci¹ tekstura*/
	sf::Texture specialButtonTex; /*!< Tekstóra wszystkich przycisków ustawiajacych gre*/
	Game* game = nullptr; /*!< wska¿nik na obiekt tymu game, rezprezentujacy w³aœciw¹ gre*/
	int numberOfPlayers = 0;
public:
	/**Konstruktor GameMenu tworz¹cy przyciski i ustawiajacy ich pozycje w menu, akutalnie wybranym przyciskiem jest pierwszy przycisk w liœcie */
	GameMenu(const sf::RenderWindow& window/**Okno wed³ug którego, skalowane jest ustawienie przycisków*/, const sf::Texture& parse/** Tekstura, t³a menu*/, const sf::Font& font/**G³ówny font menu*/)
	{
		background.setTexture(parse);
		loadTextures();
		buttons.push_back(new ButtonReturn(specialButtonTex, font));
		sf::Vector2f pos(0, 0);
		pos.y = (window.getSize().y - buttons[0]->getSpriteRect().height);
		buttons[0]->upadatePosition(pos);
		buttons.push_back(new ButtonSetPlayers(basicButtonTex, font));
		pos.x = pos.x + 200;
		pos.y = pos.y - 100;
		buttons[1]->upadatePosition(pos);
		buttons.push_back(new ButtonPlayes1(specialButtonTex, font));
		buttons.push_back(new ButtonPlayes2(specialButtonTex, font));
		buttons.push_back(new ButtonPlayes3(specialButtonTex, font));
		buttons.push_back(new ButtonPlayes4(specialButtonTex, font));
		pos.y = pos.y + 20;
		buttons[2]->upadatePosition(pos);
		pos.y = buttons[2]->getSpriteRect().top;
		for (int i = 3; i < 6; i++)
		{
			pos.x = pos.x + buttons[2]->getSpriteRect().width ;
			buttons[i]->upadatePosition(pos);
	
		}
		buttons.push_back(new ButtonLeveL1(mapTex[0], font));
		pos.x = 100;
		pos.y = 100;
		buttons[6]->upadatePosition(pos);
		current = 0;
		buttons[current]->hint(1);
	}
	void loadTextures()
	{
		basicButtonTex.loadFromFile(PATH_BUTTON);
		mapTex[0].loadFromFile(PATH_MAP1); // zaktualizowaæ pozycje rusznika
		specialButtonTex.loadFromFile(PATH_BUTTON2);
	}/** Funkcja ³aduje tekstury wszystkich przycisków jak i miniaturki wszystkich map*/
	/**Funkcja obs³uguj¹ca ¿¹dania od interfejsu, przekazuj¹ca input z interfejsu, wysy³aj¹ca ¿¹dania do przycisków menu */
	std::string triggerButton(Control::KEYBOARD key /**< Nazwa klawisza */) ////////////WORK IN PROGRES//////////////////////
	{
		std::string request;
		switch (key)
		{
		case Control::KEYBOARD::Left:
			buttons[current]->hint(0);
			if (current == 0)
			{
				current = buttons.size() - 1;
			}
			else
			{
				current--;
				if (current == 1)
				{
					current--;
				}
			}
			buttons[current]->hint(1);
			break;
		case Control::KEYBOARD::Right:
			buttons[current]->hint(0);
			if (current == buttons.size() - 1)
			{
				current = 0;
			}
			else
			{
				current++;
				if (current == 1)
				{
					current++;
				}
			}
			buttons[current]->hint(1);
			break;
		case Control::KEYBOARD::Enter:
			request = buttons[current]->buttonRequest(key);
			if (request == "LEVEL1")
			{
					game = new Game("map1.txt",numberOfPlayers);
					return request;
			}
			if (request == "PLAYER1")
			{
				numberOfPlayers = 1;
			}
			if (request == "PLAYER2")
			{
				numberOfPlayers = 2;
			}
			if (request == "PLAYER3")
			{
				numberOfPlayers = 3;
			}
			if (request == "PLAYER4")
			{
				numberOfPlayers = 4;
			}
			return request;
			break;
		default:
			break;
		}
		return "";
	}/**Funkcja obs³uguj¹ca ¿¹dania od interfejsu, przekazuj¹ca input z interfejsu, wysy³aj¹ca ¿¹dania do przycisków menu jak i gry */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(background, states);
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->draw(target, states);
		}
		if (game != nullptr)
		{
			game->draw(target,states);
		}
	};/** Funkcja rysuj¹ca wszystkie przyciski i t³o menu oraz gre */
	/**Funkcja obs³uguj¹ca ¿¹dania od interfejsu, przekazuj¹ca input z interfejsu, wysy³aj¹ca ¿¹dania do gry */
	std::string sendToGame(Control::KEYBOARD key /**< Nazwa klawisza */)
	{
		switch (key)
		{
		case Control::KEYBOARD::W:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::S:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::D:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::A:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::C:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::I:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::K:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::L:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::J:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::N:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::CTRL:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::Up:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::Down:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::Right:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::Left:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::NUM8:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::NUM5:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::NUM6:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::NUM4:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::NUM0:
			game->triggerCore(key);
			break;
		case Control::KEYBOARD::ESC:
			delete game;
			game = nullptr;
		default:
			break;
		}
		return "";
	}
	/**Funkcja sprawdzaj¹ca stan bomb bomby, czy wybuch³y, czy ¿yj¹ */
	void checkBombs()
	{
		game->checkBombs();
	}
	/**Funkcja sprawdzaj¹ca stan gry, czy ju¿ zwyciê¿yliœmy */
	bool win()
	{
		if (game->win() == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
/**
* Klasa reprezentuj¹ca Menu pomocy, sterowania 
*/
class HelpMenu : public Menu {
private:
	sf::Texture basicButtonTex; /*!< Tekstura przycisku powrotu w menu pomocy*/
public:
	/** Konstruktor Help Menu, tworz¹cy przyciski i ustawiajacy ich pozycje w menu, akutalnie wybranym przyciskiem jest pierwszy przycisk w liœcie*/
	HelpMenu(const sf::RenderWindow& window/**Okno wed³ug którego, skalowane jest ustawienie przycisków*/, const sf::Texture& parse/** Tekstura, t³a menu*/, const sf::Font& font/**G³ówny font menu*/)
	{
		background.setTexture(parse);
		loadTextures();
		buttons.push_back(new ButtonReturn(basicButtonTex, font));
		sf::Vector2f pos(0, 0);
		pos.x = window.getSize().x - (10 + buttons[0]->getSpriteRect().width);
		pos.y = window.getSize().y - (20 + buttons[0]->getSpriteRect().height);
		buttons[0]->upadatePosition(pos);
		current = 0;
		buttons[current]->hint(1);
	}
	/**Funkcja przekazywania ¿¹dania do przycisków menu*/
	std::string triggerButton(Control::KEYBOARD key /**< Nazwa klawisza */)
	{
		switch(key)
		{
			case Control::KEYBOARD::Enter:
				return buttons[current]->buttonRequest(key);
				break;
		default:
			break;
		}
		return "";
	}
	/**Funkcja wczytuj¹ca teksture przycisku*/
	void loadTextures()
	{
		basicButtonTex.loadFromFile(PATH_BUTTON2);
	};
	/**Funkcja obs³uguj¹ca ¿¹dania od interfejsu, przekazuj¹ca input z interfejsu, wysy³aj¹ca ¿¹dania do przycisków menu */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(background, states);
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->draw(target, states);
		}
	};
};
/**Klasa reprezentuj¹ca ekran zwyciêstwa*/
class WinMenu : public Menu {
private:
	sf::Texture basicButtonTex; /*!< Tekstura przycisku koñca gry*/
public:
	/** Konstruktor WinMenu, tworz¹cy przyciski i ustawiajacy ich pozycje w menu, akutalnie wybranym przyciskiem jest pierwszy przycisk w liœcie, aktualizuje te¿ t³o menu na ekran wygranej*/
	WinMenu(const sf::RenderWindow& window/**Okno wed³ug którego, skalowane jest ustawienie przycisków*/, const sf::Texture& parse/** Tekstura, t³a menu*/, const sf::Font& font/**G³ówny font menu*/)
	{
		background.setTexture(parse);
		loadTextures();
		buttons.push_back(new ButtonEnd(basicButtonTex, font));
		sf::Vector2f pos(640,520);
		buttons[0]->upadatePosition(pos);
		current = 0;
		buttons[current]->hint(1);
	}
	/**Funkcja wczytuj¹ca teksture przycisku*/
	void loadTextures()
	{
		basicButtonTex.loadFromFile(PATH_BUTTON2);
	};
	/**Funkcja przekazywania ¿¹dania do przycisku menu*/
	std::string triggerButton(Control::KEYBOARD key /**< Nazwa klawisza */)
	{
		switch (key)
		{
		case Control::KEYBOARD::Enter:
			return buttons[current]->buttonRequest(key);
			break;
		default:
			break;
		}
		return "";
	}
	/**Funkcja obs³uguj¹ca ¿¹dania od interfejsu, przekazuj¹ca input z interfejsu, wysy³aj¹ca ¿¹dania do przycisków menu */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(background, states);
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->draw(target, states);
		}
	}
};
