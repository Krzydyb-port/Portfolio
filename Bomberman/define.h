#pragma once
#define CHAR_SIZE 30 /**Wielkoœ napisu na przyciskach*/
#define CHAR_COLOR sf::Color::Black /**Kolor tekstu na przycisku*/
#define ACTION_TIME 100 /** buffor czasu pomiêdzy reakcj¹ na wiœniecie przycisku(podany w milisekundach)*/
#define MAP_COUNT 1 /** makymalna iloœæ map dostêpnych w grze*/
#define PLAYER_COUNT 4; /**Maksymalna iloœæ graczy w grze*/
#define PATH_BUTTON "Textures/button.png" /**Œcie¿ka do tekstury przycisku*/
#define PATH_CHAR1 "Textures/char1.png" /**Œcie¿ka do tekstury gracza 1*/
#define PATH_CHAR2 "Textures/char2.png" /**Œcie¿ka do tekstury gracza 2*/
#define PATH_CHAR3 "Textures/char3.png" /**Œcie¿ka do tekstury gracza 3*/
#define PATH_CHAR4 "Textures/char4.png" /**Œcie¿ka do tekstury gracza 4*/
#define PATH_GRASS "Textures/grass.png" /**Œcie¿ka do tekstury pola z traw¹*/
#define PATH_ROCK "Textures/rock.png" /**Œcie¿ka do tekstury pola z kamieniami*/
#define PATH_BEDROCK "Textures/bedrock.png" /**Œcie¿ka do tekstury pola z ceg³ami*/
#define PATH_BOMB "Textures/bomb.png" /**Œcie¿ka do tekstury pola z bomb¹*/
#define PATH_BLAST "Textures/blast.png" /**Œcie¿ka do tekstury pola z wybuchem*/
#define PATH_BUTTON2 "Textures/button2.png" /**Œcie¿ka do tekstury przycisku return*/
#define PATH_MAP1 "Textures/map1.png" /**Œcie¿ka do tekstury przycisku z map¹*/
#define PATH_WIN "Textures/win.png" /**Œcie¿ka do tekstury planszy z zwyciêstwem*/
#define GAME_OFFSET_Y 38 /** offset may z gr¹*/
#define BOMB_TIME 2 /**czas po któym wybucha bomba podany w sekundach*/
#define BLAST_TIME 3 /**cza po któym pole z wybuchem znika*/

/** enumerator typów klocków sk³adajacych siê na mape*/
enum class TILE_TYPE {
	grass = 0,
	rock = 1,
	bedrock = 2,
	blast = 3,
	none = 4,
	bomb = 5
};
/** enumerator kierunków ruchy*/
enum class ROSE_DIR {
	up,down,left,right
};
