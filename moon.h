#ifndef MOON_H
#define MOON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
#include "textBox.h"

class Moon : public sf::CircleShape {

public:

    Moon(std::string s, sf::Font& f);

    void setSentence(std::string s);
    void update(float dt, sf::RenderTarget &window);

    void render(sf::RenderTarget &target);

    TextBox textBox;
private:

    sf::Vector2f speed;

    sf::Sprite glowing;
    sf::Texture texture;

    sf::Sprite smoon;
    sf::Texture tmoon;

    float m_timer;
};

#endif
