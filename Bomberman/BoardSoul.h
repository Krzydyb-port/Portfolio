#pragma once
#include "define.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <utility>
/**Klasa logicznej reprezentacji mapy w grze*/
class BoardSoul {
private:
	TILE_TYPE map[20][10] = {TILE_TYPE::none};
public:
	BoardSoul(std::string file)
	{
		std::ifstream f;
		try {
			f.open(file.c_str());
			if (!f.good())
			{
				std::string fileErorr("MAP LOADING ERROR");
				throw fileErorr;
			}
				int tmp;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						tmp = f.get();
						while (whichone(tmp) == TILE_TYPE::none)
						{
							tmp = f.get();
							if (f.eof())
							{
								break;
							}
						}
						map[j][i] = whichone(tmp);
					}
				}

			
		}
		catch (std::string fileError)
		{
			std::cout << fileError << " " << "PLEASE CHECK MAP!" << std::endl;
		}
		f.close();
	}
	TILE_TYPE whichone(int field)
	{
		if (field == 48)
		{
			return TILE_TYPE::grass;
		}
		else if (field == 49)
		{
			return TILE_TYPE::rock;
		}
		else if (field == 50)
		{
			return TILE_TYPE::bedrock;
		}
		else
		{
			return TILE_TYPE::none;
		}
	}
	void getMap(TILE_TYPE r[20][10])
	{ 
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				r[j][i] = map[j][i];
			}
		}
		
	} 
	void addGrass(int x, int y)
	{
		map[x][y] = TILE_TYPE::grass;
	}
	void addBlast(int x, int y)
	{
			map[x][y] = TILE_TYPE::blast;
	}
	void update(int x, int y)
	{
		if (map[x][y] == TILE_TYPE::rock)
			map[x][y] = TILE_TYPE::grass;
	};
	void addBomb(int x, int y)
	{
		map[x][y] = TILE_TYPE::bomb;
	}
	TILE_TYPE ReturnType(int x, int y)
	{
		return map[x][y];
	}
	void showMap()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				std::cout << int(map[j][i]) << "  ";
			}
			std::cout << std::endl;
		}
	}
};