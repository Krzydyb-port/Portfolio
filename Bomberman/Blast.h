#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "define.h"
/**Klasa logicznej reprezentacji wybuchy w programie */
class Blast {
private:
	int x; /**Wspó³¿êdna iksowa pola wybuchu na logicznej mapie gry*/
	int y; /**Wspó³¿êdna ygrekowa pola wybuchu na logicznej mapie gry*/
	sf::Clock clock; /**Zegar czasu ¿ycia wybuchu, inicjalizowany automatycznie*/
public:
	/**Konstruktor klasy Blast*/
	Blast(int x /**Wspó³¿êdna iksowa pola wybuchu na logicznej mapie gry*/, int y/**Wspó³¿êdna iksowa pola wybuchu na logicznej mapie gry*/) : x(x), y(y) {};
	/**Funkcja sprawdzaj¹ca czy czas ¿ycia wybuchy ju¿ mni¹³*/
	bool blastCheck()
	{
		if (clock.getElapsedTime().asSeconds() > BLAST_TIME)
		{

			return true;
		}
		else
		{
			return false;
		}
	}
	/**funkcja zwracaj¹ca Wspó³¿êdn¹ iksow¹ pola wybuchu na logicznej mapie gry*/
	int getx()
	{
		return x;
	}
	/**funkcja zwracaj¹ca Wspó³¿êdn¹ ygrekow¹ pola wybuchu na logicznej mapie gry*/
	int gety()
	{
		return y;
	}
};