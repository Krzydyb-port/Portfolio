#pragma once
#include <SFML/Window/Keyboard.hpp>
/**Klasa bêd¹ca interfejsem pomiêdzy programem a u¿ytkownikiem*/
class Control {
public:
	/**Enumerator Wszystki dostêpnych klawiszy*/
	enum class KEYBOARD {
		W, S, A, D, C,
		I, K, J, L, N,
		Up, Down, Left, Right, CTRL,
		NUM8, NUM5, NUM4, NUM6, NUM0,
		ESC, UNKNOW, Enter
	};
	/**Konstruktor klasy Control*/
	Control() {};
	/**Destruktor klasy Control*/
	~Control() {};
	/**Funkcja implementujaca komunikacje z u¿ytkonwnika z programem, zczytuj¹ca wciœniecie klawiszy przez u¿ytkownika*/
	KEYBOARD input() const
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			return KEYBOARD::W;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			return KEYBOARD::S;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			return KEYBOARD::A;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			return KEYBOARD::D;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			return KEYBOARD::C;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			return KEYBOARD::I;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			return KEYBOARD::K;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			return KEYBOARD::J;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			return KEYBOARD::L;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			return KEYBOARD::N;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			return KEYBOARD::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			return KEYBOARD::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			return KEYBOARD::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			return KEYBOARD::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			return KEYBOARD::CTRL;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			return KEYBOARD::NUM8;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			return KEYBOARD::NUM5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			return KEYBOARD::NUM4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			return KEYBOARD::NUM6;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			return KEYBOARD::NUM0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			return KEYBOARD::Enter;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return KEYBOARD::ESC;
		}
		else
		{
			return KEYBOARD::UNKNOW;
		}
	}

};