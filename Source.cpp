#include <iostream>
#include "SFML/Graphics.hpp"
#include "Gameplay.h"


int main()
{
    srand(time(NULL));
	
    Gameplay gameplay;
    gameplay.run();

    return 0;
}