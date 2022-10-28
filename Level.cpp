#include "Level.h"

Level::Level()
{
    _grid = sf::Vector2f(40, 30);
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
                case ' ':
                {
				    ////TODO cambiar clase Sidewalk o Street
                    int orientation = rand() % 3;

                    switch (orientation)
                    {
                    case 0:
                        _tile[i][j] = new Tree("Texture/void_1.png", sf::Vector2u(1, 1));
                        _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                        _tile[i][j]->getSprite().setRotation(0);
                        break;
                    case 1:
                        _tile[i][j] = new Tree("Texture/void_2.png", sf::Vector2u(1, 1));
                        _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                        _tile[i][j]->getSprite().setRotation(180);
                        break;
                    case 2:
                        _tile[i][j] = new Tree("Texture/void_3.png", sf::Vector2u(1, 1));
                        _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); 
                        _tile[i][j]->getSprite().setRotation(180);
                        break;
                    };
                }
                break;
                case '0':
                    _tile[i][j] = new Unbreakable("Texture/wall_1.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    break;
                case '1':
                    _tile[i][j] = new Tree("Texture/block_down_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    break;
                case 'X':
                    _tile[i][j] = new Tree("Texture/block_down_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setScale({ 1.0f, -1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    break;
                case '2':
                    _tile[i][j] = new Tree("Texture/block_left_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    break;
                case 'y':
                    _tile[i][j] = new Tree("Texture/block_left_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    break;
                case '3':
                    _tile[i][j] = new Tree("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    break;
                case '4':
                    _tile[i][j] = new Tree("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    break;
                case '5':
                    _tile[i][j] = new Tree("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    _tile[i][j]->setScale({ 1.0f, -1.0f });
                    break;
                case 'V':
                    _tile[i][j] = new Tree("Texture/block_corner_3.png", sf::Vector2u(1, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205)); //TODO cambiar clase Sidewalk o Street
                    _tile[i][j]->setScale({ -1.0f, -1.0f });
                    break;
                case 'Z':
                {
                    int option = rand() % 3;
                    std::cout << option << std::endl;
                    switch (option)
                    {
                    case 0:
					    _tile[i][j] = new Tree("Texture/block_center.png", sf::Vector2u(1, 1)); //TODO cambiar clase Sidewalk o Street
                         break;
                    case 1:
                        _tile[i][j] = new Tree("Texture/block_center_1.png", sf::Vector2u(1, 1)); //TODO cambiar clase Sidewalk o Street
                        break;
                    case 2:
                        _tile[i][j] = new Tree("Texture/block_center_2.png", sf::Vector2u(1, 1)); //TODO cambiar clase Sidewalk o Street
                        break;
                    }
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                }
                break;
                case '6':
				    _tile[i][j] = new Unbreakable("Texture/wall_2.png", sf::Vector2u(1, 1)); //TODO: Cambiar a clase Wall
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '7':
                    _tile[i][j] = new Unbreakable("Texture/wall.png", sf::Vector2u(1, 1)); //TODO: Cambiar a clase Wall
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '8':
                    _tile[i][j] = new Brick("Texture/bridge.png", sf::Vector2u(1, 1));
                    break;
                case 'a':
                    _tile[i][j] = new Brick("Texture/house_1_a.png", sf::Vector2u(3, 1));
                    break;
                case 'b':
                    _tile[i][j] = new Brick("Texture/house_1_b.png", sf::Vector2u(3, 1));
                    break;
                case 'c':
                    _tile[i][j] = new Brick("Texture/house_1_c.png", sf::Vector2u(3, 1));
                    break;
                case 'd':
                    _tile[i][j] = new Brick("Texture/house_1_d.png", sf::Vector2u(3, 1));
                    break;
                case 'e':
                    _tile[i][j] = new Brick("Texture/house_2_a.png", sf::Vector2u(3, 1));
                    break;
                case 'f':
                    _tile[i][j] = new Brick("Texture/house_2_b.png", sf::Vector2u(3, 1));
                    break;
                case 'g':
                    _tile[i][j] = new Brick("Texture/house_2_c.png", sf::Vector2u(3, 1));
                    break;
                case 'h':
                    _tile[i][j] = new Brick("Texture/house_2_d.png", sf::Vector2u(3, 1));
                    break;
                case 'i':
                    _tile[i][j] = new Brick("Texture/house_3_a.png", sf::Vector2u(3, 1));
                    break;
                case 'j':
                    _tile[i][j] = new Brick("Texture/house_3_b.png", sf::Vector2u(3, 1));
                    break;
                case 'k':
                    _tile[i][j] = new Brick("Texture/house_3_c.png", sf::Vector2u(3, 1));
                    break;
                case 'l':
                    _tile[i][j] = new Brick("Texture/house_4_a.png", sf::Vector2u(3, 1));
                    break;
                case 'm':
                    _tile[i][j] = new Brick("Texture/house_4_b.png", sf::Vector2u(3, 1));
                    break;
                case 'n':
                    _tile[i][j] = new Brick("Texture/house_5_a.png", sf::Vector2u(3, 1));
                    break;
                case 'o':
                    _tile[i][j] = new Brick("Texture/house_5_b.png", sf::Vector2u(3, 1));
                    break;
                case 'p':
                    _tile[i][j] = new Brick("Texture/house_5_c.png", sf::Vector2u(3, 1));
                    break;
                case 'q':
                    _tile[i][j] = new Brick("Texture/house_5_d.png", sf::Vector2u(3, 1));
                    break;
                case 'r':
                    _tile[i][j] = new Brick("Texture/house_7_a.png", sf::Vector2u(3, 1));
                    break;
                case 's':
                    _tile[i][j] = new Brick("Texture/house_7_b.png", sf::Vector2u(3, 1));
                    break;
                case 't':
                    _tile[i][j] = new Brick("Texture/house_8_a.png", sf::Vector2u(3, 1));
                    break;
                case 'u':
                    _tile[i][j] = new Brick("Texture/house_8_b.png", sf::Vector2u(3, 1));
                    break;
                case 'v':
                    _tile[i][j] = new Brick("Texture/house_8_c.png", sf::Vector2u(3, 1));
                    break;
                case 'x':
                    _tile[i][j] = new Brick("Texture/house_8_d.png", sf::Vector2u(3, 1));
                    break;
                case '9':
                    _tile[i][j] = new Brick("Texture/water_2.png", sf::Vector2u(1, 1));
                    break;
                case 'W':
                    _tile[i][j] = new Tree("Texture/dock.png", sf::Vector2u(1, 1));
                    break;
                case '-':
                    _tile[i][j] = new Brick("Texture/barricade_wall.png", sf::Vector2u(3, 1));
                    break;
                case '¡':
                    _tile[i][j] = new Brick("Texture/barricade_wall_2.png", sf::Vector2u(3, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '!':
                    _tile[i][j] = new Brick("Texture/barricade_wall_2.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '>':
                    _tile[i][j] = new Brick("Texture/barricade_corner.png", sf::Vector2u(3, 1));
                    _tile[i][j]->setScale({ -1.0f, 1.0f });
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '<':
                    _tile[i][j] = new Brick("Texture/barricade_corner.png", sf::Vector2u(3, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));
                    break;
                case '$':
                {
                    _tile[i][j] = new Target("Texture/military_base.png", sf::Vector2u(5, 1));
                    _tile[i][j]->getSprite().setColor(sf::Color(255, 255, 255, rand() % 20 + 205));

                }
                    break;
                default:
                    break;
            }

            _tile[i][j]->setPosition({ j * _grid.x, i * _grid.y }); //Grid i y grid j

            if (j == WIDTH_MAP - 1)
                _tile[i][j]->setScale({ -1.0f, 1.0f });
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
    int targetIndexI = 0;
    int targetIndexJ = 0;
	
    for (int i = 0; i < HEIGHT_MAP; i++)
    {
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if (_tile[i][j]->getTarget())
            {
                targetIndexI = i;
                targetIndexJ = j;

            }
            _tile[i][j]->render(window);
        }
    }

    _tile[targetIndexI][targetIndexJ]->render(window);
}

int Level::getHeight()
{
    return HEIGHT_MAP;
}

int Level::getWidth()
{
    return WIDTH_MAP;
}

