#pragma once
#include "Splitter.h"

int main(int argc, char* argv[])
{
	char a;
#ifdef _DEBUG

	argc = 3;
	argv[1] = (char*)"C:/Users/fynes/Desktop/GAME/ASSETS/DO_NOT_MOD/sprites.png";
	argv[2] = (char*)"C:/Users/fynes/Desktop/GAME/ASSETS/DO_NOT_MOD/sprites.xml";

#endif // DEBUG

	
	Start(argc, argv);
       	

	system("PAUSE");
	return 0;
}
