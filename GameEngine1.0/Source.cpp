#include "GameLayer.h"
#include "Conquest.h"
#include "demo3d.h"


int main()
{
	Game *pGame = new Conquest(GAME_WIDTH, GAME_HEIGHT);	
	
	pGame->ConsoleRun();


	delete pGame;
	return 0;
}