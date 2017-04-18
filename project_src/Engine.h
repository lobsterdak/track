#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include "map.h"
#include "Vector2.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;


class Engine
{
public:
    Map map;
    std::vector <Object*> objects;
    float time;
    Clock clock;
    RenderWindow window;
    Engine()
    {
        add_obj(new Player(Vector_2(200, 200), "Boss_1.png"));
		//add_obj(new Enemy(Vector_2(400, 400), "jin.png"));
    }

    void start(unsigned int Width, unsigned int Height)
    {
        RenderWindow window(sf::VideoMode(Width, Height), "SFML_GAME");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            time = clock.getElapsedTime().asMilliseconds();
            clock.restart();
            // need global logic
            map.draw(&window);
            for (auto it : objects)
            {
                it->control();
                it->logic();
                it->update(time);
                it->draw(&window, time);
            }
            window.display();
        }
    }
    
    void add_obj(Object* element)
    {
        objects.push_back(element);
    }
};