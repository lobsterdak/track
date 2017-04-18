#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "string.h"
#include "Vector2.h"


using namespace sf;

class Enemy : public Object
{
    int life = 10;
    float speed = 150;
    float CurrentFrame = 1;
    Vector_2 target;
public:

    Enemy(Vector_2 pos_, Vector_2 target_)
    {
        position = pos_;
        target = target_;
        velocity = (target - position).unit_vector() * speed;
        //display.sprite.setOrigin(90, 70);
    }
    void update(float time)
    {
        if ((position - target).len() < speed * time)
            velocity = { 0, 0 };
        else
            position += time * velocity;
    }
    /*void Enemy_animation(float time);*/
    void Enemy_new_target(Vector_2 hero_pos)
    {
        if (velocity.len() == 0)
        {
            target = hero_pos;
            velocity = (target - position).unit_vector() * speed;
        }
    }
    void logic()
    {};
    void control()
    {};

};

//void Enemy::Enemy_animation(float time)
//{
//    if (velocity.x != 0 && velocity.y != 0)
//    {
//        CurrentFrame += 10 * time;
//        String name = "enemy_";
//        String name_left = "enemy_left_";
//        if (CurrentFrame > 10)
//            CurrentFrame -= 10;
//        int code = (int)CurrentFrame;
//        if (velocity.x < 0)
//        {
//            if (code == 9)
//                //display.texture.loadFromFile(name_left + (char)('10') + ".png");
//            else
//                //display.texture.loadFromFile(name_left + (char)('1' + code) + ".png");
//        }
//        else
//        {
//            if (code == 9)
//                //display.texture.loadFromFile(name + (char)('10') + ".png");
//            else
//                //display.texture.loadFromFile(name + (char)('1' + code) + ".png");
//        }
//        //display.sprite.setTexture(display.texture);
//    }
//}