#pragma once
#include <SFML/Graphics.hpp>
#include "define.h"
#include <vector>
#include "GamerSoul.h"
/**Struktura mostu poœrednicz¹cego pomiêdzy klas¹ Core(logik¹ programu), a klas¹ Game(wyœwietlanie)*/
struct Bridge 
{
	TILE_TYPE Board[20][10]; /** Mapa w sensie logiki gry, mapy gry*/
	GamerSoul* gamers[4] = { nullptr }; /**tablica wska¿ników na graczy, graczy w sensie logiki gry*/

};