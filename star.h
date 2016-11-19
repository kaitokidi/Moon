#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "textBox.h"

class Star : public sf::Sprite {

public:

    Star(sf::Font& f, float timeToStart);

    void setSentence(std::string s);
    void update(float dt);

    void render(sf::RenderTarget &target);

    TextBox textBox;

    void setCanSpeak(bool value);
    bool getCanSpeak() const;
private:
    bool canSpeak;
    sf::Texture texture;
    float m_timeToStart;
    float m_timer;

};

#endif
