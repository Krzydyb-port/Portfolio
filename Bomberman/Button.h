#pragma once
#include <SFML/Graphics.hpp>
#include "Control.h"
#include "define.h"
//dopisaæ gdzie znajduje siê realizacja funkcjonalnoœci danego przycisku


/**
* Klasa abstrakcji reprezentuj¹ca przycisk, aspekt graficzny na podstawie zestawu bibliotek SFML. 
*/
class Button : public sf::Drawable{
protected:
	sf::Sprite sprite; /*!< Sprite przycisku, o po³ó¿enie spritu musi zadbaæ programista*/
	sf::Text text; /*!< Tekst*/
public:
	/** Funkcja czysto virtualna, obs³uga ¿¹dania nazwy przycisku*/
	virtual std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const = 0;
	/** Funkcja rysuj¹ca, implementacjia z biblioteki SFML*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); target.draw(text); }
	/** Funkcja(akcesor) zmieniaj¹ca zarówno po³o¿enie sprita jak i ustawiaj¹ca tekst w wzglêdnym jego œrodku */
	void upadatePosition(const sf::Vector2f position/**< vector z blibloteki SFML zawieraj¹cy zmienn¹ x i y w postaci liczb zmiennoprzecinkowych*/)
	{
		sprite.setPosition(position);
		text.setPosition(position.x+(getSpriteRect().width-text.getGlobalBounds().width)/2, position.y + (getSpriteRect().height - text.getGlobalBounds().height) / 2); //ustwienie napisu w wzglêdnym œrodku sprita
	}
	virtual void hint(bool onof /**< 1, gdy chcemy wyró¿niæ tekst, w innym przypadku tekst staje siê tekstem zwyk³ym*/)
	{
		if (onof == 1) { text.setStyle(sf::Text::Bold); }
		else { text.setStyle(sf::Text::Regular); }
	};
	/** Funkcja ¿¹dania po³o¿enia sprita, zwracaj¹ca globalne koordynaty sprita(bierze pod uwage transformacje) */
	sf::FloatRect getSpriteRect() { return sprite.getGlobalBounds(); }
	
};
/**
* Klasa reprezentuj¹ca przycisk "Start"
*/
class ButtonStart : public Button {
public:
	/**Kontruktor klasy ButtonStart, tekst ustawiany jako "Start Game"*/
	ButtonStart(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na przycisk*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst na przycisku*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("Start Game");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	} 
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca START, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "START"; }/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca START, jeœli wciœniêty klawisz jest Enterem*/
};
/**
* Klasa reprezentuj¹ca przycisk "End"
*/
class ButtonEnd: public Button {
public:
	/**Kontruktor klasy ButtonEnd, tekst ustawiany jako "End"*/
	ButtonEnd(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na przycisk*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst na przycisku*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("End");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca END, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "END"; }
};
/**
* Klasa reprezentuj¹ca przycisk "Game", przejœcie do menu wyboru poziomu i iloœci graczy 
*/
class ButtonGameMenu : public Button {
public:
	/**Kontruktor klasy ButtonGameMenu, tekst ustawiany jako "Game"*/
	ButtonGameMenu(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na przycisk*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst na przycisku*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("Game");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca GAME_MENU, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "GAME_MENU"; }
};
/**
* Klasa reprezentuj¹ca przycisk z miniaturk¹ pierwszej mapy.
*/
class ButtonLeveL1 : public Button
{
private:
	sf::RectangleShape* rectangle; /*!< Obwiednia aktualnie wybranej mapy*/
public:
	/**Kontruktor klasy ButtonLevel1*/
	ButtonLeveL1(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na miniaturke mapy*/, const sf::Font& font/**<Font, zostawiony z powodów kompatybilnoœci z klas¹ bazow¹*/)
	{
		sprite.setTexture(parse);
		rectangle = new sf::RectangleShape(sf::Vector2f(sprite.getLocalBounds().width + 20, sprite.getLocalBounds().height + 20));
		rectangle->setFillColor(sf::Color::Transparent);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca LEVEL1, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key /**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "LEVEL1"; }
	/** Funkcja podœwietlaj¹ca mape*/
	void hint(bool onof/**< 1, gdy chcemy uwidoczniæ obwiednie, w innym przypadku obwiednia staje siê niewidoczna*/) override {
		if (onof == 1) { rectangle->setFillColor(sf::Color::Black); }
		else { rectangle->setFillColor(sf::Color::Transparent); }
	};
	/** Funkcja rysuj¹ca, implementacjia z biblioteki SFML*/
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override 
	{ 
		rectangle->setPosition(sprite.getPosition().x - 10, sprite.getPosition().y - 10);
		target.draw(*rectangle); target.draw(sprite, states);
	}
};

/**
* Klasa reprezentuj¹ca tekst "Players:, metody istniej¹ce w niej nie powinny byæ u¿ywane, istniej¹ tylko przez wymóg kompatyblinoœci z klas¹ bazow¹"
*/
class ButtonSetPlayers : public Button {
public:
	/**Kontruktor klasy ButtonSetPlayes*/
	ButtonSetPlayers(const sf::Texture& parse/**<Tekstura, zostawiony z powodów kompatybilnoœci z klas¹ bazow¹*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst*/)
	{
		text.setFont(font);
		text.setString("Players:");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja istniej¹ca wy³acznie z powodów kompatyblinoœci z klas¹ bazow¹, nie powinna byæ u¿ywana, zwraca pusty ci¹g znakowy*/
	std::string buttonRequest(Control::KEYBOARD key /**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return ""; } 
	/**Funkcja istniej¹ca wy³acznie z powodów kompatyblinoœci z klas¹ bazow¹, nie powinna byæ u¿ywana*/
	void hint(bool onof) override{};
};
/**
* Klasa reprezentuj¹ca przycisk "1", wybór jednego gracza
*/
class ButtonPlayes1 : public Button
{
public:
	/**Kontruktor klasy ButtonSetPlayes1*/
	ButtonPlayes1(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na miniaturke mapy*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("1");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca PLAYER1, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "PLAYER1"; }
};
/**
* Klasa reprezentuj¹ca przycisk "2", wybór jednego gracza
*/
class ButtonPlayes2 : public Button
{
public:
	/**Kontruktor klasy ButtonSetPlayes2*/
	ButtonPlayes2(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na miniaturke mapy*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("2");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca PLAYER2, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "PLAYER2"; }
};
/**
* Klasa reprezentuj¹ca przycisk "3", wybór jednego gracza
*/
class ButtonPlayes3 : public Button
{
public:
	/**Kontruktor klasy ButtonSetPlayes3*/
	ButtonPlayes3(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na miniaturke mapy*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("3");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca PLAYER3, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "PLAYER3"; }
};
/**
* Klasa reprezentuj¹ca przycisk "4", wybór jednego gracza
*/
class ButtonPlayes4 : public Button
{/**Kontruktor klasy ButtonSetPlayes4*/
public:
	ButtonPlayes4(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na miniaturke mapy*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("4");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca PLAYER4, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "PLAYER4"; }
};

/**
* Klasa reprezentuj¹ca przycisk "How to Play", wyœwietlaj¹cy sterowanie
*/
class ButtonHowToPlay : public Button {
public:
	/**Kontruktor klasy HowToPlay, tekst ustawiony jak How To Play*/
	ButtonHowToPlay(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na miniaturke mapy*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("How To Play");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca HOW, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "HOW"; }
};
/**
* Klasa reprezentuj¹ca przycisk "Return", wyœwietlaj¹cy sterowanie
*/
class ButtonReturn : public Button {
public:
	/**Kontruktor klasy ButtonReturn, tekst ustawiony jak Return*/
	ButtonReturn(const sf::Texture& parse/**< Referencja do tekstury, któr¹ chcemy na³o¿yæ na miniaturke mapy*/, const sf::Font& font/**<Font w którym ma byæ wypisany tekst*/)
	{
		sprite.setTexture(parse);
		text.setFont(font);
		text.setString("Return");
		text.setCharacterSize(CHAR_SIZE);
		text.setFillColor(CHAR_COLOR);
	}
	/** Funkcja obs³ugi ¿¹dania nazwy przycisku, zwracaj¹ca RETURN, jeœli wciœniêty klawisz jest Enterem*/
	std::string buttonRequest(Control::KEYBOARD key/**< Nazwa klawisza */) const { if (key == Control::KEYBOARD::Enter) return "RETURN"; }
};
