#include "Level.h"

void Level::initFile() {
	
	//Read Register _level
    if (fileLevel.loadLevels(_level))
    {
        char mapFile[460];
        int k = 0;

        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                _map[i][j] = fileLevel.getLevel()[k++];
            }
        }
    }
}

Level::Level(int level)
{
    _grid = sf::Vector2f(40, 30);
	_level = level;
    initFile();
    initLevel();
}

Level::~Level()
{
}

Block* Level::getTile(int i, int j)
{
    return _tile[i][j];
}


void Level::initLevel()
{
    int cant = 0;

    for (int i = 0; i < HEIGHT_MAP; i++)
    {
        for (int j = 0; j < WIDTH_MAP; j++)
        {

            switch (_map[i][j])
            {

                //CALLE
                case ' ':
                {
                    int orientation = rand() % 3;

                    switch (orientation)
                    {
                    case 0:
                        _tile[i][j] = new Street("Texture/void_1.png", sf::Vector2u(1, 1));
                        _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                        _tile[i][j]->getSprite().setRotation(0);
                        break;
                    case 1:
                        _tile[i][j] = new Street("Texture/void_2.png", sf::Vector2u(1, 1));
                        _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                        _tile[i][j]->getSprite().setRotation(180);
                        break;
                    case 2:
                        _tile[i][j] = new Street("Texture/void_3.png", sf::Vector2u(1, 1));
                        _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); 
                        _tile[i][j]->getSprite().setRotation(180);
                        break;
                    };
                }
                break;
			
				// VEREDAS
                case '1':
                    _tile[i][j] = new Street("Texture/block_down_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case 'X':
                    _tile[i][j] = new Street("Texture/block_down_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setScale({ 1.0f, -1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '2':
                    _tile[i][j] = new Street("Texture/block_left_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case 'y':
                    _tile[i][j] = new Street("Texture/block_left_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '3':
                    _tile[i][j] = new Street("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '4':
                    _tile[i][j] = new Street("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '5':
                    _tile[i][j] = new Street("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    _tile[i][j]->setScale({ 1.0f, -1.0f });
                    break;
                case 'V':
                    _tile[i][j] = new Street("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    _tile[i][j]->setScale({ -1.0f, -1.0f });
                    break;
                case 'Z':
                {
                    int option = rand() % 3;
                    std::cout << option << std::endl;
                    switch (option)
                    {
                    case 0:
					    _tile[i][j] = new Street("Texture/block_center.png", sf::Vector2u(1, 1));
                         break;
                    case 1:
                        _tile[i][j] = new Street("Texture/block_center_1.png", sf::Vector2u(1, 1));
                        break;
                    case 2:
                        _tile[i][j] = new Street("Texture/block_center_2.png", sf::Vector2u(1, 1));
                        break;
                    }
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                }
                break;
				
				// PARED
                case '0':
                    _tile[i][j] = new Unbreakable("Texture/wall_1.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '6':
				    _tile[i][j] = new Unbreakable("Texture/wall_2.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '7':
                    _tile[i][j] = new Unbreakable("Texture/wall.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '8':
                    _tile[i][j] = new Brick("Texture/target_bridge.png", sf::Vector2u(1, 1));
					_tile[i][j]->setHaveEffect(true);
                    break;
					
				//AGUA
                case '9':
                {
                    int orientation = rand() % 2;

                    switch (orientation)
                    {
                    case 0:
                        _tile[i][j] = new Unbreakable("Texture/water_3.png", sf::Vector2u(1, 1));
                        break;
                    case 1:
                        _tile[i][j] = new Unbreakable("Texture/water_4.png", sf::Vector2u(1, 1));
                        break;
                    }
                }
                break;

				//CASA 1
                case 'a':
                    _tile[i][j] = new Brick("Texture/house_1_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'b':
                    _tile[i][j] = new Brick("Texture/house_1_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'c':
                    _tile[i][j] = new Brick("Texture/house_1_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'd':
                    _tile[i][j] = new Brick("Texture/house_1_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                //CASA 2
                case 'e':
                    _tile[i][j] = new Brick("Texture/house_2_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'f':
                    _tile[i][j] = new Brick("Texture/house_2_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'g':
                    _tile[i][j] = new Brick("Texture/house_2_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'h':
                    _tile[i][j] = new Brick("Texture/house_2_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
					
				//CASA 3    
                case 'i':
                    _tile[i][j] = new Brick("Texture/house_3_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'j':
                    _tile[i][j] = new Brick("Texture/house_3_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'k':
                    _tile[i][j] = new Brick("Texture/house_3_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
					
				//CASA 4
                case 'l':
                    _tile[i][j] = new Brick("Texture/house_4_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'm':
                    _tile[i][j] = new Brick("Texture/house_4_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 5
                case 'n':
                    _tile[i][j] = new Brick("Texture/house_5_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'o':
                    _tile[i][j] = new Brick("Texture/house_5_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'p':
                    _tile[i][j] = new Brick("Texture/house_5_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'q':
                    _tile[i][j] = new Brick("Texture/house_5_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 7
                case 'r':
                    _tile[i][j] = new Brick("Texture/house_7_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 's':
                    _tile[i][j] = new Brick("Texture/house_7_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 8
                case 't':
                    _tile[i][j] = new Brick("Texture/house_8_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'u':
                    _tile[i][j] = new Brick("Texture/house_8_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'v':
                    _tile[i][j] = new Brick("Texture/house_8_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'x':
                    _tile[i][j] = new Brick("Texture/house_8_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 9
                case 'P':
                    _tile[i][j] = new Brick("Texture/house_9.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 10	
                case 'A':
                    _tile[i][j] = new Brick("Texture/house_10_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'B':
                    _tile[i][j] = new Brick("Texture/house_10_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'C':
                    _tile[i][j] = new Brick("Texture/house_10_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'D':
                    _tile[i][j] = new Brick("Texture/house_10_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 11
                case 'E':
                    _tile[i][j] = new Brick("Texture/house_11_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'F':
                    _tile[i][j] = new Brick("Texture/house_11_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'G':
                    _tile[i][j] = new Brick("Texture/house_11_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 12
                case 'H':
                    _tile[i][j] = new Brick("Texture/house_12_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'I':
                    _tile[i][j] = new Brick("Texture/house_12_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'J':
                    _tile[i][j] = new Brick("Texture/house_12_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'K':
                    _tile[i][j] = new Brick("Texture/house_12_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 13
                case 'L':
                    _tile[i][j] = new Brick("Texture/house_13_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'M':
                    _tile[i][j] = new Brick("Texture/house_13_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'N':
                    _tile[i][j] = new Brick("Texture/house_13_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'O':
                    _tile[i][j] = new Brick("Texture/house_13_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                    //CASA 14
                case 'Q':
                    _tile[i][j] = new Brick("Texture/house_14_a.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'R':
                    _tile[i][j] = new Brick("Texture/house_14_b.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'S':
                    _tile[i][j] = new Brick("Texture/house_14_c.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case 'T':
                    _tile[i][j] = new Brick("Texture/house_14_d.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;

                //BARRICADA
                case '-':
                    _tile[i][j] = new Brick("Texture/barricade_wall.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    break;
                case '¡':
                    _tile[i][j] = new Brick("Texture/barricade_wall_2.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '!':
                    _tile[i][j] = new Brick("Texture/barricade_wall_2.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '>':
                    _tile[i][j] = new Brick("Texture/barricade_corner.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '<':
                    _tile[i][j] = new Brick("Texture/barricade_corner.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setHaveEffect(true);
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;

                    //SANDBAG
                case 'U':
                    _tile[i][j] = new Brick("Texture/sandbag.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setHaveEffect(true);
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;

					//METAL
                case 'W':
                    _tile[i][j] = new Unbreakable("Texture/metal_1.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
					
				//TARGET
                case '$':
                {
                    _tile[i][j] = new Target("Texture/target_bridge.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setHaveEffect(true);
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
					_tile[i][j]->setLife(5);
                    _targetIndex.x = i;
                    _targetIndex.y = j;
                }
                    break;
					
				//VACIO
                case '%':
                    _tile[i][j] = new Brick("Texture/empty.png", sf::Vector2u(1, 1));
                    break;
                default:
                    break;
            }

			//Posiciones de cada grid
            _tile[i][j]->setPosition({ j * _grid.x, i * _grid.y });

			//Corrige filas y columnas
            if (j == WIDTH_MAP - 1)
                _tile[i][j]->setScale({ -1.0f, 1.0f });

            if (i == 0) {
				_tile[i][j]->setScale({ 1.0f, -1.0f });
			    if(j == WIDTH_MAP - 1)
                    _tile[i][j]->setScale({ -1.0f, -1.0f });
            }
        }
    }
}

void Level::update()
{
    for (int i = 0; i < HEIGHT_MAP; i++)
    {
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            _tile[i][j]->updateLife();
            _tile[i][j]->update();
        }
    }
}

void Level::render(sf::RenderWindow& window)
{
    for (int i = 0; i < HEIGHT_MAP; i++)
    {
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            _tile[i][j]->render(window);
            _tile[i][j]->renderEffect(window);
        }
    }

    _tile[_targetIndex.x][_targetIndex.y]->render(window);
    _tile[_targetIndex.x][_targetIndex.y]->setScale({ 1.5f, 1.5f });
}

int Level::getHeight()
{
    return HEIGHT_MAP;
}

int Level::getWidth()
{
    return WIDTH_MAP;
}

sf::Vector2i Level::getTargetIndex()
{
    return _targetIndex;
}

