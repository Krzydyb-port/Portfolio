#pragma once
#include "BoardSoul.h"
#include "GamerSoul.h"
#include <vector>
#include "Bridge.h"
#include "Bomb.h"
#include "Blast.h"
/**Klasa bêd¹ca rdzeniem logiki gry*/
class Core {
private:
	BoardSoul board; /**Logiczna reprezentacja mapy gry*/
	GamerSoul* gamers[4]; /**Mapa wska¿nikó na graczy*/
	std::vector <Bomb> bombs; /**Wektro bomb akutalnie aktwynych*/
	std::vector <Blast> blasts; /**Wektor wybuchów aktualnie trwaj¹cych*/

public:
	/**Bazowy kontruktor klasy Core*/
	Core(std::string file /**nazwa pliku "file.txt" z którego wczytywana jest mapa gry*/, int numberOfPlayers/**Liczba graczy których Core ma zainicjalizowaæ*/) : board(file)
	{
		for (int i = 0; i < 4; i++)
		{
			if (numberOfPlayers > i)
			{
				gamers[i] = new GamerSoul(0, 0);
				if (i == 1)
				{
					gamers[i]->update(19, 0);
				}
				if (i == 2)
				{
					gamers[i]->update(0, 9);
				}
				if (i == 3)
				{
					gamers[i]->update(19, 9);
				}
			}
			else
			{
				gamers[i] = nullptr;
			}
		}
	}
	/**Funkcja zwracaj¹ca obiekt MOstu pomiêdzy Corem a Game*/
	Bridge returnBridge()
	{
		Bridge parse;
		board.getMap(parse.Board);
		for (int i = 0; i < 4; i++)
		{
			parse.gamers[i] = gamers[i];
		}
		return parse;
	}
	/**Funkcja przyjmuj¹ca ¿¹dania zmiany stanu wewnêtrzengo gry*/
	void triggerCore(Control::KEYBOARD key /**Wciœniêty przycisk*/)
	{

		switch (key)
		{
		case Control::KEYBOARD::W:
			if (colisionCheck(gamers[0]->getx(), gamers[0]->gety(), ROSE_DIR::up) == true)
			{
				if (board.ReturnType(gamers[0]->getx(), gamers[0]->gety() - 1) == TILE_TYPE::grass)
				{
					if (gamers[0]->status() == false)
					{
						gamers[0]->update(gamers[0]->getx(), gamers[0]->gety() - 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::S:
			if (colisionCheck(gamers[0]->getx(), gamers[0]->gety(), ROSE_DIR::down) == true)
			{
				if (board.ReturnType(gamers[0]->getx(), gamers[0]->gety() + 1) == TILE_TYPE::grass)
				{
					if (gamers[0]->status() == false)
					{
						gamers[0]->update(gamers[0]->getx(), gamers[0]->gety() + 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::D:
			if (colisionCheck(gamers[0]->getx(), gamers[0]->gety(), ROSE_DIR::right) == true)
			{
				if (board.ReturnType(gamers[0]->getx() + 1, gamers[0]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[0]->status() == false)
					{
						gamers[0]->update(gamers[0]->getx() + 1, gamers[0]->gety());
					}
				}

			}
			break;
		case Control::KEYBOARD::A:
			if (colisionCheck(gamers[0]->getx(), gamers[0]->gety(), ROSE_DIR::left) == true)
			{
				if (board.ReturnType(gamers[0]->getx() - 1, gamers[0]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[0]->status() == false)
					{
						gamers[0]->update(gamers[0]->getx() - 1, gamers[0]->gety());
					}
				}
			}
			break;
		case Control::KEYBOARD::C:
			if (gamers[0]->status() == false)
			{
				bombs.push_back(Bomb(gamers[0]->getx(), gamers[0]->gety()));
				board.addBomb(gamers[0]->getx(), gamers[0]->gety());
			}
			break;
		case Control::KEYBOARD::I:
			if (colisionCheck(gamers[1]->getx(), gamers[1]->gety(), ROSE_DIR::up) == true)
			{
				if (board.ReturnType(gamers[1]->getx(), gamers[1]->gety() - 1) == TILE_TYPE::grass)
				{
					if (gamers[1]->status() == false)
					{
						gamers[1]->update(gamers[1]->getx(), gamers[1]->gety() - 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::K:
			if (colisionCheck(gamers[1]->getx(), gamers[1]->gety(), ROSE_DIR::down) == true)
			{
				if (board.ReturnType(gamers[1]->getx(), gamers[1]->gety() + 1) == TILE_TYPE::grass)
				{
					if (gamers[1]->status() == false)
					{
						gamers[1]->update(gamers[1]->getx(), gamers[1]->gety() + 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::L:
			if (colisionCheck(gamers[1]->getx(), gamers[1]->gety(), ROSE_DIR::right) == true)
			{
				if (board.ReturnType(gamers[1]->getx() + 1, gamers[1]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[1]->status() == false)
					{
						gamers[1]->update(gamers[1]->getx() + 1, gamers[1]->gety());
					}
				}

			}
			break;
		case Control::KEYBOARD::J:
			if (colisionCheck(gamers[1]->getx(), gamers[1]->gety(), ROSE_DIR::left) == true)
			{
				if (board.ReturnType(gamers[1]->getx() - 1, gamers[1]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[1]->status() == false)
					{
						gamers[1]->update(gamers[1]->getx() - 1, gamers[1]->gety());
					}
				}
			}
			break;
		case Control::KEYBOARD::N:
			if (gamers[1]->status() == false)
			{
				bombs.push_back(Bomb(gamers[1]->getx(), gamers[1]->gety()));
				board.addBomb(gamers[1]->getx(), gamers[1]->gety());
			}
			break;
		case Control::KEYBOARD::Up:
			if (colisionCheck(gamers[2]->getx(), gamers[2]->gety(), ROSE_DIR::up) == true)
			{
				if (board.ReturnType(gamers[2]->getx(), gamers[2]->gety() - 1) == TILE_TYPE::grass)
				{
					if (gamers[2]->status() == false)
					{
						gamers[2]->update(gamers[2]->getx(), gamers[2]->gety() - 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::Down:
			if (colisionCheck(gamers[2]->getx(), gamers[2]->gety(), ROSE_DIR::down) == true)
			{
				if (board.ReturnType(gamers[2]->getx(), gamers[2]->gety() + 1) == TILE_TYPE::grass)
				{
					if (gamers[2]->status() == false)
					{
						gamers[2]->update(gamers[2]->getx(), gamers[2]->gety() + 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::Right:
			if (colisionCheck(gamers[2]->getx(), gamers[2]->gety(), ROSE_DIR::right) == true)
			{
				if (board.ReturnType(gamers[2]->getx() + 1, gamers[2]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[2]->status() == false)
					{
						gamers[2]->update(gamers[2]->getx() + 1, gamers[2]->gety());
					}
				}

			}
			break;
		case Control::KEYBOARD::Left:
			if (colisionCheck(gamers[2]->getx(), gamers[2]->gety(), ROSE_DIR::left) == true)
			{
				if (board.ReturnType(gamers[2]->getx() - 1, gamers[2]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[2]->status() == false)
					{
						gamers[2]->update(gamers[2]->getx() - 1, gamers[2]->gety());
					}
				}
			}
			break;
		case Control::KEYBOARD::CTRL:
			if (gamers[2]->status() == false)
			{
				bombs.push_back(Bomb(gamers[2]->getx(), gamers[2]->gety()));
				board.addBomb(gamers[2]->getx(), gamers[2]->gety());
			}
			break;
		case Control::KEYBOARD::NUM8:
			if (colisionCheck(gamers[3]->getx(), gamers[3]->gety(), ROSE_DIR::up) == true)
			{
				if (board.ReturnType(gamers[3]->getx(), gamers[3]->gety() - 1) == TILE_TYPE::grass)
				{
					if (gamers[3]->status() == false)
					{
						gamers[3]->update(gamers[3]->getx(), gamers[3]->gety() - 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::NUM5:
			if (colisionCheck(gamers[3]->getx(), gamers[3]->gety(), ROSE_DIR::down) == true)
			{
				if (board.ReturnType(gamers[3]->getx(), gamers[3]->gety() + 1) == TILE_TYPE::grass)
				{
					if (gamers[3]->status() == false)
					{
						gamers[3]->update(gamers[3]->getx(), gamers[3]->gety() + 1);
					}
				}

			}
			break;
		case Control::KEYBOARD::NUM6:
			if (colisionCheck(gamers[3]->getx(), gamers[3]->gety(), ROSE_DIR::right) == true)
			{
				if (board.ReturnType(gamers[3]->getx() + 1, gamers[3]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[3]->status() == false)
					{
						gamers[3]->update(gamers[3]->getx() + 1, gamers[3]->gety());
					}
				}

			}
			break;
		case Control::KEYBOARD::NUM4:
			if (colisionCheck(gamers[3]->getx(), gamers[3]->gety(), ROSE_DIR::left) == true)
			{
				if (board.ReturnType(gamers[3]->getx() - 1, gamers[3]->gety()) == TILE_TYPE::grass)
				{
					if (gamers[3]->status() == false)
					{
						gamers[3]->update(gamers[3]->getx() - 1, gamers[3]->gety());
					}
				}
			}
			break;
		case Control::KEYBOARD::NUM0:
			if (gamers[3]->status() == false)
			{
				bombs.push_back(Bomb(gamers[3]->getx(), gamers[3]->gety()));
				board.addBomb(gamers[3]->getx(), gamers[3]->gety());
			}
			break;
		default:
			break;
		}

	}
	/**Funkcja realizujaca sprawdzenie kolizji*/
	bool colisionCheck(int x/**iksowa wspó³rzêdna obiektu którego kolizja ma byæ sprawdzona */, int y/**ygrekowa wspó³rzêdna obiektu którego kolizja ma byæ sprawdzona */, ROSE_DIR course/**kierunek w którym ma zostaæ sprawdzona kolizja*/)
	{
		switch (course)
		{
		case ROSE_DIR::up:
			if (y - 1 >= 0 && y - 1 < 10)
			{
				return true;
			}
			break;
		case ROSE_DIR::down:
			if (y + 1 >= 0 && y + 1 < 10)
			{
				return true;
			}
			break;
		case ROSE_DIR::right:
			if (x + 1 >= 0 && x + 1 < 20)
			{
				return true;
			}
			break;
		case ROSE_DIR::left:
			if (x - 1 >= 0 && x - 1 < 20)
			{
				return true;
			}
			break;
		default:
			return false;
			break;
		}
		return false;
	}
	/**Funcka sprawdzajaca czy któraœ z bomb z vectora bomb ju¿ wybuch³a i dodajaca wybuchy*/
	bool checkBombs()
	{
		bool boom = false;
		for (int i = 0; i < bombs.size(); i++)
		{
			if (bombs[i].bombCheck() == true)
			{
				blasts.push_back(Blast(bombs[i].getx(), bombs[i].gety()));
				board.addBlast(bombs[i].getx(), bombs[i].gety());
				if (colisionCheck(bombs[i].getx(), bombs[i].gety(), ROSE_DIR::up) == true)
				{
					if (board.ReturnType(bombs[i].getx(), bombs[i].gety() - 1) != TILE_TYPE::bedrock)
					{
						blasts.push_back(Blast(bombs[i].getx(), bombs[i].gety() - 1));
						board.addBlast(bombs[i].getx(), bombs[i].gety() - 1);
					}
				}
				if (colisionCheck(bombs[i].getx(), bombs[i].gety(), ROSE_DIR::down) == true)
				{
					if (board.ReturnType(bombs[i].getx(), bombs[i].gety() + 1) != TILE_TYPE::bedrock)
					{
						blasts.push_back(Blast(bombs[i].getx(), bombs[i].gety() + 1));
						board.addBlast(bombs[i].getx(), bombs[i].gety() + 1);
					}
				}
				if (colisionCheck(bombs[i].getx(), bombs[i].gety(), ROSE_DIR::right) == true)
				{
					if (board.ReturnType(bombs[i].getx() + 1, bombs[i].gety()) != TILE_TYPE::bedrock)
					{
						blasts.push_back(Blast(bombs[i].getx() + 1, bombs[i].gety()));
						board.addBlast(bombs[i].getx() + 1, bombs[i].gety());
					}
				}
				if (colisionCheck(bombs[i].getx(), bombs[i].gety(), ROSE_DIR::left) == true)
				{
					if (board.ReturnType(bombs[i].getx() - 1, bombs[i].gety()) != TILE_TYPE::bedrock)
					{
						blasts.push_back(Blast(bombs[i].getx() - 1, bombs[i].gety()));
						board.addBlast(bombs[i].getx() - 1, bombs[i].gety());
					}
				}
				bombs.erase(bombs.begin() + i);
				boom = true;
			}
		}
		return boom;
	}
	/**Funcka sprawdzajaca czy któryœ wybuch z vectora wybychów ju¿ powinnien zczezn¹æ i zamieniajaca go na pole trawy*/
	bool checkBlast()
	{
		bool relief = false;
		for (int i = 0; i < blasts.size(); i++)
		{
			if (blasts[i].blastCheck() == true)
			{
				board.addGrass(blasts[i].getx(), blasts[i].gety());
				blasts.erase(blasts.begin() + i);
				relief = true;
			}
		}
		return relief;
	}
	/**Funkcja sprawdzaj¹ca czy który z graczy nie powinnien ju¿ kipn¹æ*/
	int checkPlayers()
	{

		for (int i = 0; i < 4; i++)
		{
			if (gamers[i] != nullptr)
			{
				if (board.ReturnType(gamers[i]->getx(), gamers[i]->gety()) == TILE_TYPE::blast)
				{
					gamers[i]->die();
					return i;
				}
			}
		}
		return 5;
	}
	/**Funkcja spradzaj¹ca czy zosta³y spe³nione warunki zwyciêstwa*/
	bool win()

	{
		int left = 0;
		for (int i = 0; i < 4; i++)
		{
			if (gamers[i] != nullptr)
			{
				if (gamers[i]->status() != true)
				{
					left++;
				}
			}
		}
		if (left > 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};