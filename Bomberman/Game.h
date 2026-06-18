#pragma once
#include "Core.h"
#include "BoardBody.h"
#include "GamerBody.h"
/**Klasa bêd¹ca gr¹*/
class Game: sf::Drawable {
private:
	Core core; /** Obiekt logiki gry*/
	BoardBody map; /**Obiekt graficznej reprezentacji mapy*/
	GamerBody* gamers[4] = {nullptr}; /**Talbica obiektów graficznej reprezentacji graczy*/


public:
	/**Konstruktor obiektu Game*/
	Game(std::string file/**nazwa pliku "file.txt" z którego wczytywana jest mapa gry*/, int gamersNumber /**Liczba graczy których Core ma zainicjalizowaæ*/) : core(file,gamersNumber)
	{
		map.setMap(core.returnBridge().Board);
		for (int i = 0; i < gamersNumber; i++)
		{
			gamers[i] = new GamerBody(loadTexture(i));
			if (i == 0)
			{
				sf::Vector2f pos(map.getSpritePos(0,0).left, map.getSpritePos(0, 0).top);
				gamers[i]->update(pos);
			}
			if (i == 1)
			{
				sf::Vector2f pos(map.getSpritePos(19,0).left, map.getSpritePos(19,0).top);
				gamers[i]->update(pos);
			}
			if (i == 2)
			{
				sf::Vector2f pos(map.getSpritePos(0,9).left, map.getSpritePos(0,9).top);
				gamers[i]->update(pos);
			}
			if (i == 3)
			{
				sf::Vector2f pos(map.getSpritePos(19,9).left, map.getSpritePos(19,9).top);
				gamers[i]->update(pos);
			}
		}
	
	};
	/**Funkcja ³aduj¹ca tektury graczy*/
	sf::Texture loadTexture(int number /**Numer gracza którego tekstua ma byæ za³adowana*/)
	{
		sf::Texture tmp;
		switch (number)
		{
		case 0:
			tmp.loadFromFile(PATH_CHAR1);
			break;
		case 1:
			tmp.loadFromFile(PATH_CHAR2);
			break;
		case 2:
			tmp.loadFromFile(PATH_CHAR3);
			break;
		case 3:
			tmp.loadFromFile(PATH_CHAR4);
			break;
		default:
			tmp.create(64, 64);
			break;
		}
		return tmp;
	};
	/**Funkcja rysuj¹ca wszystko*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		target.draw(map, states);
		for  (int i = 0; i < 4; i++)
		{
			if (gamers[i] == nullptr)
			{
				break;
			}
			gamers[i]->draw(target, states);
		}
	}
	/**Funkcja zlecaj¹ca logice gry zmiene swojego wewnêtrznego stanu pod wp³ywem imputu od gracza otrzymanego z klasy wy¿szej instancji*/
	void triggerCore(Control::KEYBOARD key/**Wciœniêty klawisz*/)
	{
		switch (key)
		{
		case Control::KEYBOARD::W:
			if( gamers[0] == nullptr)
			{
				return;
			}
			if (gamers[0]->canMove())
			{
				if (gamers[0]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(0);
					gamers[0]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::S:
			if (gamers[0] == nullptr)
			{
				return;
			}
			if (gamers[0]->canMove())
			{
				if (gamers[0]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(0);
					gamers[0]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::D:
			if (gamers[0] == nullptr)
			{
				return;
			}
			if (gamers[0]->canMove())
			{
				if (gamers[0]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(0);
					gamers[0]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::A:
			if (gamers[0] == nullptr)
			{
				return;
			}
			if (gamers[0]->canMove())
			{
				if (gamers[0]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(0);
					gamers[0]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::C:
			if (gamers[0] == nullptr)
			{
				return;
			}
			if (gamers[0]->status() == false)
			{
				core.triggerCore(key);
				map.updateMap(core.returnBridge().Board);
			}
			break;
		case Control::KEYBOARD::I:
			if (gamers[1] == nullptr)
			{
				return;
			}
			if (gamers[1]->canMove())
			{
				if (gamers[1]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(1);
					gamers[1]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::K:
			if (gamers[1] == nullptr)
			{
				return;
			}
			if (gamers[1]->canMove())
			{
				if (gamers[1]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(1);
					gamers[1]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::L:
			if (gamers[1] == nullptr)
			{
				return;
			}
			if (gamers[1]->canMove())
			{
				if (gamers[1]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(1);
					gamers[1]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::J:
			if (gamers[1] == nullptr)
			{
				return;
			}
			if (gamers[1]->canMove())
			{
				if (gamers[1]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(1);
					gamers[1]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::N:
			if (gamers[1] == nullptr)
			{
				return;
			}
			if (gamers[1]->status() == false)
			{
				core.triggerCore(key);
				map.updateMap(core.returnBridge().Board);
			}
			break;
		case Control::KEYBOARD::Up:
			if (gamers[2] == nullptr)
			{
				return;
			}
			if (gamers[2]->canMove())
			{
				if (gamers[2]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(2);
					gamers[2]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::Down:
			if (gamers[2] == nullptr)
			{
				return;
			}
			if (gamers[2]->canMove())
			{
				if (gamers[2]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(2);
					gamers[2]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::Right:
			if (gamers[2] == nullptr)
			{
				return;
			}
			if (gamers[2]->canMove())
			{
				if (gamers[2]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(2);
					gamers[2]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::Left:
			if (gamers[2] == nullptr)
			{
				return;
			}
			if (gamers[2]->canMove())
			{
				if (gamers[2]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(2);
					gamers[2]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::CTRL:
			if (gamers[2] == nullptr)
			{
				return;
			}
			if (gamers[2]->status() == false)
			{
				core.triggerCore(key);
				map.updateMap(core.returnBridge().Board);
			}
			break;
		case Control::KEYBOARD::NUM8:
			if (gamers[3] == nullptr)
			{
				return;
			}
			if (gamers[3]->canMove())
			{
				if (gamers[3]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(3);
					gamers[3]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::NUM5:
			if (gamers[3] == nullptr)
			{
				return;
			}
			if (gamers[3]->canMove())
			{
				if (gamers[3]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(3);
					gamers[3]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::NUM6:
			if (gamers[3] == nullptr)
			{
				return;
			}
			if (gamers[3]->canMove())
			{
				if (gamers[3]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(3);
					gamers[3]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::NUM4:
			if (gamers[3] == nullptr)
			{
				return;
			}
			if (gamers[3]->canMove())
			{
				if (gamers[3]->status() == false)
				{
					core.triggerCore(key);
					updateGamer(3);
					gamers[3]->resetClock();
				}
			}
			break;
		case Control::KEYBOARD::NUM0:
			if (gamers[3] == nullptr)
			{
				return;
			}
			if (gamers[3]->status() == false)
			{
				core.triggerCore(key);
				map.updateMap(core.returnBridge().Board);
			}
			break;
		default:
			break;
		}
	}
	/**Funkcja aktualizujaca pozycje gracza*/
	void updateGamer(int number /**Numer gracza którego tekstua ma byæ za³adowana*/)
	{

		sf::Vector2f pos;
		pos.x = map.getSpritePos(core.returnBridge().gamers[number]->getx(), core.returnBridge().gamers[number]->gety()).left;
		pos.y = map.getSpritePos(core.returnBridge().gamers[number]->getx(), core.returnBridge().gamers[number]->gety()).top;
		gamers[number]->update(pos);
	}
	/**Funkcja sprawdzaj¹ca stany bomb i wybuchów oraz graczy jak i zwyciêstwa i aktualizcuj¹ca mape na podstawie mostu*/
	void checkBombs()
	{
		if (core.checkBombs())
		{
			map.updateMap(core.returnBridge().Board);
		}
		if (core.checkBlast())
		{
			map.updateMap(core.returnBridge().Board);
		}
		int player = core.checkPlayers();
		if (player != 5)
		{
			sf::Vector2f pos(10000,10000);
			gamers[player]->update(pos);
			gamers[player]->die();
		}
		win();
	}
	/**Funkcja sprawdzaj¹ca czy spe³nione zosta³y warunki zwyciêstwa*/
	bool win()
	{
		if (core.win() == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};