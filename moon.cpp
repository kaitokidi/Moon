#include "moon.h"
#include "textBox.h"

#define MOVEMENTSPEED 50

Moon::Moon(std::string s, sf::Font& f)
    :textBox(s, f),
      speed(0,0)
{
    texture.loadFromFile(("res/glow.png"));
    tmoon.loadFromFile(("res/moon.png"));
    glowing.setTexture(texture);
    smoon.setTexture(tmoon);

    m_timer = 0;
    setRadius(50);
    setPointCount(200);
    setFillColor(sf::Color::White);

    glowing.setScale(getGlobalBounds().width*2/glowing.getGlobalBounds().width,
                     getGlobalBounds().height*2/glowing.getGlobalBounds().height );

    glowing.setPosition(getPosition());
    glowing.setOrigin(glowing.getLocalBounds().width/2, glowing.getLocalBounds().height/2);

    smoon.setScale(getGlobalBounds().width*2/smoon.getGlobalBounds().width,
                     getGlobalBounds().height*2/smoon.getGlobalBounds().height );

    smoon.setPosition(getPosition());
    smoon.setOrigin(smoon.getLocalBounds().width/2, smoon.getLocalBounds().height/2);

    smoon.setColor(sf::Color(250,250,250,50));


}

void Moon::setSentence(std::string s)
{
    textBox.setSentence(s);
}

void Moon::update(float dt) {
    m_timer += dt;


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 	{
        speed.x += -MOVEMENTSPEED*dt;
//        move(sf::Vector2f(-MOVEMENTSPEED*dt, 0));
  //      glowing.setOrigin(glowing.getLocalBounds().width/2-MOVEMENTSPEED*dt, glowing.getLocalBounds().height/2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))	{
        speed.x += MOVEMENTSPEED*dt;
        //move(sf::Vector2f( MOVEMENTSPEED*dt, 0));
        //glowing.setOrigin(glowing.getLocalBounds().width/2+MOVEMENTSPEED*dt, glowing.getLocalBounds().height/2);
    }
    else {
        if(speed.x > 0) speed.x = std::max(0.f, speed.x - MOVEMENTSPEED*dt);
        if(speed.x < 0) speed.x = std::min(0.f, speed.x + MOVEMENTSPEED*dt);
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    || sf::Keyboard::isKeyPressed(sf::Keyboard::W))	{
       speed.y += -MOVEMENTSPEED*dt;
        //move(sf::Vector2f(0, -MOVEMENTSPEED*dt));
        //glowing.setOrigin(glowing.getLocalBounds().width/2, glowing.getLocalBounds().height/2-MOVEMENTSPEED*dt);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || sf::Keyboard::isKeyPressed(sf::Keyboard::S))	{
        speed.y += MOVEMENTSPEED*dt;
        //move(sf::Vector2f(0,  MOVEMENTSPEED*dt));
        //glowing.setOrigin(glowing.getLocalBounds().width/2, glowing.getLocalBounds().height/2+MOVEMENTSPEED*dt);
    }
    else {
        if(speed.y > 0) speed.y = std::max(0.f, speed.y - MOVEMENTSPEED*dt);
        if(speed.y < 0) speed.y = std::min(0.f, speed.y + MOVEMENTSPEED*dt);
    }

    if(speed.x > 10) speed.x = 10;
    if(speed.y > 10) speed.y = 10;
    if(speed.x < -10) speed.x = -10;
    if(speed.y < -10) speed.y = -10;
    move(speed);
    glowing.setOrigin(glowing.getLocalBounds().width/2 + speed.x, glowing.getLocalBounds().height/2+ speed.y);

    glowing.setPosition(getPosition());
    smoon.setPosition(getPosition());
    textBox.update(dt);

    glowing.setScale(getLocalBounds().width*2/glowing.getLocalBounds().width,
                     getLocalBounds().height*2/glowing.getLocalBounds().height );
    float scale = glowing.getScale().x + std::abs(std::sin(m_timer/3))/10;
    glowing.setScale(scale,scale);
}

void Moon::render(sf::RenderTarget &target)
{
    target.draw(glowing);
    //target.draw(*this);
    target.draw(smoon);
    textBox.setPosition(sf::Vector2f(getPosition().x - textBox.getGlobalBounds().width/2, getPosition().y -120));
    target.draw(textBox);
}

