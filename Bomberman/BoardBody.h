#pragma once
#include "Tile.h"
#include <map>
#include <utility>
/**Klasa reprezentujaca graficznie mape gry*/
class BoardBody : public sf::Drawable {
private:
	Tile* map[20][10]; /**tablica wska¿ników na obiekty klasy Tile, pojedyñcze pola mapy*/
	std::map <TILE_TYPE,sf::Texture> tiltex; /**Mapa tekstur poszczególnych Tili*/
public:
	/**Kontruktor BoardBody*/
	BoardBody()
	{
		sf::Texture tmp;
		tmp.loadFromFile(PATH_GRASS);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				map[j][i] = new Tile(tmp, TILE_TYPE::grass);
			}
		}
	}
	/**Funkcja ustawiaj¹ca mape na podstawie reprezentacji logicznej mapy*/
	void setMap(TILE_TYPE soulMap[20][10]/**Mapa bêd¹ca logiczn¹ reprezentacj¹ mapy gry*/) 
	{
		sf::Texture tmp;
		tmp.loadFromFile(PATH_GRASS);
		tiltex.insert(std::pair<TILE_TYPE, sf::Texture>(TILE_TYPE::grass, tmp));
		tmp.loadFromFile(PATH_ROCK);
		tiltex.insert(std::pair<TILE_TYPE, sf::Texture>(TILE_TYPE::rock, tmp));
		tmp.loadFromFile(PATH_BEDROCK);
		tiltex.insert(std::pair<TILE_TYPE, sf::Texture>(TILE_TYPE::bedrock, tmp));
		tmp.loadFromFile(PATH_BLAST);
		tiltex.insert(std::pair<TILE_TYPE, sf::Texture>(TILE_TYPE::blast, tmp));
		tmp.loadFromFile(PATH_BOMB);
		tiltex.insert(std::pair<TILE_TYPE, sf::Texture>(TILE_TYPE::bomb, tmp));
		sf::Vector2f pos(0, 38);
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{

				map[i][j] = new Tile(tiltex[soulMap[i][j]], soulMap[i][j]);
				if (j != 0)
				{
					pos.y += 64;
				}
				map[i][j]->upadate(pos);
			}
			pos.y = 38;
			pos.x += 64;
		}
	};
	/**Funkcja rysuj¹ca wszystkie pojedyñcze pola mapy*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{

				map[i][j]->draw(target, states);
			}
		}
	}
	/**Funkcja sprawcaj¹ca SFML obiekt reprezentujacy pozycje i wielokœæ danego tila*/
	sf::FloatRect getSpritePos(int x, int y)
	{
		return map[x][y]->getSpriteRect();
	}
	/**Funkcja akutalizuj¹ca mape na podstawie reprezentacji logicznej mapy*/
	void updateMap(TILE_TYPE soulMap[20][10])
	{
		sf::Vector2f pos(0, 38);
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				delete map[i][j];
				map[i][j] = new Tile(tiltex[soulMap[i][j]], soulMap[i][j]);
				if (j != 0)
				{
					pos.y += 64;
				}
				map[i][j]->upadate(pos);
			}
			pos.y = 38;
			pos.x += 64;
		}
	}
};