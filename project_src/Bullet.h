#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "string.h"
#include "Vector2.h"

#define PI M_PI

using namespace sf;

class Bullet : public Object
{
public:
    Vector_2 true_direction;
    Vector2i v;
    double max_speed = 10000;
    Bullet()
    {}
    Bullet(float x, float y, Vector2i v)
    {
        Vector_2 v1(v.x, v.y);

        velocity = max_speed * v1.unit_vector();
        //display.sprite.setOrigin(32, 32);
    }
    void update(float time)
    {
        Vector_2 v1(v.x, v.y);
        true_direction = v1 - position;
        position += 0.02 * velocity * time;
        velocity = velocity.unit_vector() + true_direction.unit_vector();
        velocity = velocity.unit_vector() * max_speed;
        //display.sprite.setPosition(position.x, position.y);
    }
    void set_sprite()
    {
        String name;
        double c = velocity.unit_vector() * Vector_2(1, 0);
        double fi = acos(c);
        if (true_direction.len() < 20)
            name = "boom_1.png";
        else
        {
            if (fi < PI / 8)
                name = "right.png";
            else
            {
                if (PI / 8 < fi &&  fi < 3 * PI / 8)
                {
                    if (velocity.y < 0)
                        name = "up_right.png";
                    else
                        name = "down_right.png";
                }
                else
                {
                    if (3 * PI / 8 < fi &&  fi < 5 * PI / 8)
                    {
                        if (velocity.y < 0)
                            name = "up.png";
                        else
                            name = "down.png";
                    }
                    else
                    {
                        if (5 * PI / 8 < fi &&  fi < 7 * PI / 8)
                        {
                            if (velocity.y < 0)
                                name = "up_left.png";
                            else
                                name = "down_left.png";
                        }
                        else
                            name = "left.png";
                    }
                }
            }
        }
        //display.texture.loadFromFile(name);
        //display.sprite.setTexture(display.texture);
    }
    void draw()
    {};
    void logic()
    {};
    void control()
    {};
};