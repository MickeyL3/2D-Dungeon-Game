#define OLC_PGE_APPLICATION
#include <iostream>
#include "Enemy.h"
#include "Zombie.h"
#include "Boss.h"
#include <cstdlib>
#include "MonsterWorld.h"


int main()
{

	std::cout << "STARTING PROGRAM" << std::endl;

	MonsterWorld World;
	if (World.Construct(SCREEN_WIDTH, SCREEN_WIDTH+NOTIFICATION_BAR_HEIGHT, PIXEL_SIZE, PIXEL_SIZE))
	{
		World.Start();
	}
	
	return 0;

}