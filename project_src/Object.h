#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Display_Manager.h"

using namespace sf;



class Object
{
public:
    Vector_2 position;
    Vector_2 velocity;
    float speed; 
    Display_Manager display_manager;
    /*String animation_state;
    bool flip;*/
    virtual void update(float time)
    {
        position += speed * velocity * time/100; 
    }
    virtual void animation()
    {};
    virtual void draw(RenderWindow* window, float time)
    {
        return ;
    }
    virtual void logic() = 0;
    virtual void control() = 0;
};


