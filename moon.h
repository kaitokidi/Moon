#ifndef MOON_H
#define MOON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "textBox.h"

class Moon : public sf::CircleShape {

public:

    Moon(std::string s, sf::Font& f);

    void setSentence(std::string s);
    void update(float dt);

    void render(sf::RenderTarget &target);

    TextBox textBox;
private:

};

#endif
