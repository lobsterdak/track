#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Vector2.h"

using namespace sf;

class Player : public Object
{
public:
    std::map<std::string, bool> key;
    Player(Vector_2 position_, String name_of_file) {
        display_manager.texture.loadFromFile("Boss_1.png");
        display_manager.loadFromXML("hero.xml");
        position = position_;
        velocity = { 0, 0 };
        speed = 15;
    }
    void draw(RenderWindow* window, float time)
    {
        display_manager.tick(time);
        display_manager.draw(*window, position.x, position.y);
    }
    void logic()
    {};

    void control()
    {
#define KEY_PRESS_OR_NOT(name)                                      \
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::##name))       \
            key[#name] = true;                                      \
        else                                                        \
            key[#name] = false

        KEY_PRESS_OR_NOT(Left);
        KEY_PRESS_OR_NOT(Right);
        KEY_PRESS_OR_NOT(Up);
        KEY_PRESS_OR_NOT(Down);
        KEY_PRESS_OR_NOT(Space);
        KEY_PRESS_OR_NOT(K);
        
        #undef KEY_PRESS_OR_NOT
        
        key_check();
    };

    void key_check()
    {
#define STATE display_manager.current_anim
#define FLIP display_manager.anim_list[STATE].flip
        if (key["Right"])
        {
            if (STATE == "stay")
            {
                STATE = "right";
                velocity = { 1, 0 };
            }
        }
        if (key["Left"])
        {
            if (STATE == "stay")
            {
                STATE = "right";
                FLIP = true;
                velocity = { -1, 0 };
            }
        }
        if (key["Up"])
        {
            if (STATE == "stay")
            {
                STATE = "stay";
                velocity = { 0, 0 };
            }
        }
        if (key["Down"])
        {
            if (STATE == "stay")
            {
               STATE = "stay";
                velocity = { 0, 0 };
            }
        }
        if (key["Space"])
        {
            if ((STATE == "stay") || (STATE == "right"))
            {
                STATE= "atack_right";
                velocity = { 0, 0 };
            }
        }
        if (key["K"])
        {
            if ((STATE == "stay") || (STATE == "right") || (STATE == "atack_right"))
            {
                STATE = "death";
                velocity = { 0, 0 };
            }
        }
        if (!key["Right"])
        {
            if (STATE == "right" && !FLIP)
            {
               STATE = "stay";
                velocity = { 0, 0 };
            }
        }
        if (!key["Left"])
        {
            if (STATE == "right" && FLIP)
            {
                FLIP = false;
                STATE = "stay";
                velocity = { 0, 0 };
            }
        }
        if (!key["Space"])
        {
            if (STATE == "atack_right")
            {
                STATE = "stay";
                velocity = { 0, 0 };
            }
        }
#undef STATE
#undef FLIP
    }
};
