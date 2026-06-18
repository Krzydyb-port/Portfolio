#pragma once
#include <SFML/Graphics.hpp>
#include "define.h"
/**Klasa reprezentuj¹ca graficznie pojedyñcze pole mapy*/
class Tile : public sf::Drawable {
protected:
	sf::Sprite sprite; /**Sprite przedstawiaj¹cy pojedyñcze pole mapy*/
	TILE_TYPE type; /**Zmienna reprezentuj¹cy typ, dla logiki programu, pojedyñczego pola mapy*/
public:
	/**Funkcja obs³uguj¹ca ¿¹dania od interfejsu, przekazuj¹ca input z interfejsu, wysy³aj¹ca ¿¹dania do przycisków menu */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states);}
	/**Funkcja akcesora, zmieniaj¹ca pozycje sprita w oknie*/
	void upadate(const sf::Vector2f position)
	{
		sprite.setPosition(position);
	}
	/** Funkcja ¿¹dania po³o¿enia sprita, zwracaj¹ca globalne koordynaty sprita(bierze pod uwage transformacje) */
	sf::FloatRect getSpriteRect() { return sprite.getGlobalBounds(); }
	/**Kontruktor Tile-a*/
	Tile(const sf::Texture& parse /**Tekstóra która ma byæ na³o¿ona na sprita*/, TILE_TYPE granted /**Typ pojedyñczego pola mapy*/)
	{
		sprite.setTexture(parse);
		type = granted;
	};

};
