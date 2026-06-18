#pragma once
#include <SFML/Graphics.hpp>
/**Klasa reprezentujaca graficznie gracza*/
class GamerBody : sf::Drawable {
private:
	sf::Sprite sprite; /**Sprite gracza*/
	sf::Texture tex; /** Tekstura gracza */
	sf::Clock clock; /**Wewnêtrzny zegar gracza*/
	int dead; /**flaga czy gracz jest martwy*/
public:
	/**Kontruktor GamerBody*/
	GamerBody(const sf::Texture& parse /**Tekstura danego gracza*/) 
	{
		tex = sf::Texture(parse);
		sprite.setTexture(tex); 
		dead = false;
	}
	/**Funkcja rysuj¹ca gracza*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); }
	/**Funkcja akcesor, pozawalajaæa zmieniæ pozycje gracza w oknie*/
	void update(sf::Vector2f position /**vector floatów SFML z wspó³¿êdna x i y na oknie*/) { sprite.setPosition(position); }
	/**Funkcja sprawdzaj¹ca czy gracz mo¿e wykonaæ ruch*/
	bool canMove()
	{
		if (clock.getElapsedTime().asMilliseconds() > ACTION_TIME)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	/**Funkcja akcesor resetujaca wewnêtrzny zegar gracza*/
	void resetClock()
	{
		clock.restart();
	}
	/**Funkcja akcesor zmieniajacy wewnêtrzeny stan gracza na martwice*/
	void die()
	{
		dead = true;
	}
	/**Funkcja sprawdzaj¹ca status gracza*/
	bool status()
	{
		return dead;
	}
};