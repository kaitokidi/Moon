#include "moon.h"
#include "textBox.h"

#define MOVEMENTSPEED 200

Moon::Moon(std::string s, sf::Font& f)
    :textBox(s, f)
{
    setRadius(50);
    setPointCount(200);
    setFillColor(sf::Color::White);
}

void Moon::setSentence(std::string s)
{
    textBox.setSentence(s);
}

void Moon::update(float dt) {
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 	move(sf::Vector2f(-MOVEMENTSPEED*dt, 0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	move(sf::Vector2f( MOVEMENTSPEED*dt, 0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	move(sf::Vector2f(0, -MOVEMENTSPEED*dt));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	move(sf::Vector2f(0,  MOVEMENTSPEED*dt));

    textBox.update(dt);
}

void Moon::render(sf::RenderTarget &target)
{
    target.draw(*this);
    textBox.setPosition(sf::Vector2f(getPosition().x - textBox.getGlobalBounds().width/2, getPosition().y -120));
    target.draw(textBox);
}

