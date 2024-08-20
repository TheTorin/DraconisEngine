
#include "DraconisEngine/Draconis.h"

int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{          
	Draconis::runGame();

	// "clean-up"... (not really for these demos)
	Draconis::endGame();

	return 0;                                       
}

