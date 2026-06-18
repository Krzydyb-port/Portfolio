#pragma once
#include <SFML/Graphics.hpp>
#include "define.h"
/**Klasa logicznej reprezentacji bomby w programie*/
class Bomb {
private: 
	int x; /**Wspó³¿êdna iksowa pola bomby na logicznej mapie gry*/
	int y; /**Wspó³¿êdna ygrekowa pola bomby na logicznej mapie gry*/
	sf::Clock clock; /**Zegar czasu ¿ycia bomba, inicjalizowany automatycznie*/
public:
	/**Konstruktor klasy BOMB*/
	Bomb(int x /**Wspó³¿êdna iksowa pola bomby na logicznej mapie gry*/, int y /**Wspó³¿êdna ygrekowa pola bomby na logicznej mapie gry*/) : x(x), y(y) {};
	/**Funkcja sprawdzaj¹ca czy czas ¿ycia bomby ju¿ mni¹³*/
	bool bombCheck()
	{
		if (clock.getElapsedTime().asSeconds() > BOMB_TIME)
		{
			
			return true;
		}
		else
		{
			return false;
		}
	}
	/**funkcja zwracaj¹ca Wspó³¿êdn¹ iksow¹ pola bomby na logicznej mapie gry*/
	int getx()

	{
		return x;
	}
	/**funkcja zwracaj¹ca Wspó³¿êdn¹ iksow¹ pola bomby na logicznej mapie gry*/
	int gety()
	{
		return y;
	}
};