#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include "map.h"
#include "Vector2.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Engine.h"


int main()
{
    int Screen_width = 800;
    int Screen_height = 600;
    Engine engine;
    engine.start(Screen_width, Screen_height);
    return 0;
}
