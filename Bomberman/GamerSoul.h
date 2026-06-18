#pragma once
/**Klasa logicznej reprezentacji gracza w programie*/
class GamerSoul {
private:
	int x;	/**Wspó³¿êdna iksowa gracza na logicznej mapie gry*/
	int y;	/**Wspó³¿êdna ygrekowa gracza na logicznej mapie gry*/
	bool dead; /**flaga czy dany gracz jest martwy czy ¿ywy*/
public:
	/**Konstuktor GamerSoul  bazowo flaga dead ustawiona jest na wartoœæ false*/
	GamerSoul(int x /**Wspó³¿êdna iksowa gracza na logicznej mapie gry*/, int y /**Wspó³¿êdna iksowa gracza na logicznej mapie gry*/) : x(x), y(y), dead(false) {};
	/**Funkcja akcesora, pozawalajaca zmienic pozycje gracza na mapie logicznej gracza*/
	void update(int x/**Wspó³¿êdna iksowa gracza na logicznej mapie gry*/, int y/**Wspó³¿êdna ygrekowa gracza na logicznej mapie gry*/)
	{
		this->x = x;
		this->y = y;
	}
	/**Funkcja zwracaj¹ca wspó³¿êdn¹ iksowa gracza*/
	int getx() { return x; }
	/**Funkcja zwracaj¹ca wspó³¿êdn¹ ygrekowa gracza*/
	int gety() { return y; }
	/**Funkcja debuguj¹ca, pokazujaca pozycje x i y gracza*/
	void showMe()
	{
		std::cout << "JESTEM" << x << "		" << y << std::endl;
	}
	/**Funkcja akcesora, pozwalajaca ustawiæ flage dead na wartoœæ true*/
	void die()
	{
		dead = true;
	}
	/**Funkcja zwracaj¹ca aktualny stan flagi dead*/
	bool status()
	{
		return dead;
	}


};