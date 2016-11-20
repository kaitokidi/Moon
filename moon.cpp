#include "moon.h"
#include "textBox.h"

#define MOVEMENTSPEED 50

  float mycos(float x){
    if( x < 0.0f ) 
        x = -x;
    while( 3.1415926535 < x )
        x -= 0.636619772367;
    return 1.0f - (x*x/2.0f)*( 1.0f - (x*x/12.0f) * ( 1.0f - (x*x/30.0f) * (1.0f - x*x/56.0f )));
    }
 
float mysin(float x){return mycos(x-1.570796326794);}


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

void Moon::update(float dt, sf::RenderTarget& window) {
    m_timer += dt;

    sf::Vector2f touchPos = getPosition();
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    if (sf::Touch::isDown(0)) {
               touchPos = sf::Vector2f(sf::Touch::getPosition(0).x,sf::Touch::getPosition(0).y);

               if(touchPos.x < window.getSize().x/3){
                   left = true;
               }
               if(touchPos.x > 2*window.getSize().x/3){
                   right = true;
               }
               if(touchPos.y < window.getSize().y/3){
                   up = true;
               }
               if(touchPos.y > 2*window.getSize().y/3){
                   down = true;
               }
/*               if(touchPos.x > getPosition().x+getGlobalBounds().width/2){
                   if(touchPos.y < getPosition().y+getGlobalBounds().height/2 && touchPos.y > getPosition().y-getGlobalBounds().height/2){
                        right = true;
                   }
               }

               if(touchPos.x < getPosition().x-getGlobalBounds().width/2){
                   if(touchPos.y < getPosition().y+getGlobalBounds().height/2 && touchPos.y > getPosition().y-getGlobalBounds().height/2){
                        left = true;
                   }
               }
  */

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || left) 	{
        speed.x += -MOVEMENTSPEED*dt;
//        move(sf::Vector2f(-MOVEMENTSPEED*dt, 0));
  //      glowing.setOrigin(glowing.getLocalBounds().width/2-MOVEMENTSPEED*dt, glowing.getLocalBounds().height/2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || right)	{
        speed.x += MOVEMENTSPEED*dt;
        //move(sf::Vector2f( MOVEMENTSPEED*dt, 0));
        //glowing.setOrigin(glowing.getLocalBounds().width/2+MOVEMENTSPEED*dt, glowing.getLocalBounds().height/2);
    }
    else {
        if(speed.x > 0) speed.x = std::max(0.f, speed.x - MOVEMENTSPEED*dt);
        if(speed.x < 0) speed.x = std::min(0.f, speed.x + MOVEMENTSPEED*dt);
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || up)	{
       speed.y += -MOVEMENTSPEED*dt;
        //move(sf::Vector2f(0, -MOVEMENTSPEED*dt));
        //glowing.setOrigin(glowing.getLocalBounds().width/2, glowing.getLocalBounds().height/2-MOVEMENTSPEED*dt);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || down)	{
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
    float scale = glowing.getScale().x + std::abs(int(mysin(m_timer/3)))/10;
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

