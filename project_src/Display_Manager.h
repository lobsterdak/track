#pragma once 

#include "TinyXML/tinyxml.h"
#include <SFML\Graphics.hpp>

class Animation
{
public:
    std::vector<sf::IntRect> frames, flip_frames;
    sf::Sprite sprite;
    sf::Texture texture;
    bool flip;

    float currentFrame, display_speed;
    Animation()
    {};
    Animation(sf::Texture& texture, int x, int y, int w, int h, int count, int step)
    {
        sprite.setTexture(texture);
        currentFrame = 0;

        flip = false;
        for (int i = 0; i < count; i++)
        {
            frames.push_back(sf::IntRect(x + i*step, y, w, h));
            flip_frames.push_back(sf::IntRect(x + i*step + w, y, -w, h));
        }
    }

    void tick(float time)
    {
        currentFrame += display_speed * time;
        if (currentFrame > frames.size())
            currentFrame -= frames.size();
        int i = currentFrame;
        if (flip == true)
            sprite.setTextureRect(flip_frames[i]);
        else
            sprite.setTextureRect(frames[i]);
    }
};

class Display_Manager
{
public:
    sf::Texture texture;
    sf::String current_anim;
    std::map<sf::String, Animation> anim_list;
    Display_Manager():
        current_anim("stay")
    {}

    void create(sf::String name_of_file, sf::String name, int x, int y, int w, int h, int count, int step)
    {
        texture.loadFromFile(name_of_file);
        anim_list[name] = Animation(texture, x, y, w, h, count, step);
        current_anim = name;
    }

    void draw(sf::RenderWindow &window, int x = 0, int y = 0)
    {
        anim_list[current_anim].sprite.setPosition(x, y);
        window.draw(anim_list[current_anim].sprite);
    }

    void set_anim_and_flip(sf::String name, bool flip)
    {
        current_anim = name;
        anim_list[current_anim].flip = flip;
    }

    void tick(float time) {
        
        anim_list[current_anim].tick(time);

    }

    void loadFromXML(std::string fileName)
    {
        TiXmlDocument animFile(fileName.c_str());

        animFile.LoadFile();

        TiXmlElement *head;
        head = animFile.FirstChildElement("sprites");

        TiXmlElement *animElement;
        animElement = head->FirstChildElement("animation");
        while (animElement)
        {
            Animation anim;
            String current = animElement->Attribute("title");
            int delay = atoi(animElement->Attribute("delay"));
            anim.display_speed = 1.0 / delay; anim.sprite.setTexture(texture);

            TiXmlElement *cut;
            cut = animElement->FirstChildElement("cut");
            while (cut)
            {
                int x = atoi(cut->Attribute("x"));
                int y = atoi(cut->Attribute("y"));
                int w = atoi(cut->Attribute("w"));
                int h = atoi(cut->Attribute("h"));

                anim.frames.push_back(IntRect(x, y, w, h));
                anim.flip_frames.push_back(IntRect(x + w, y, -w, h));
                cut = cut->NextSiblingElement("cut");
            }

            anim.sprite.setOrigin(0, anim.frames[0].height);

            anim_list[current] = anim;
            animElement = animElement->NextSiblingElement("animation");
        }
    }

};
