#include "star.h"
#include "textBox.h"

#define MOVEMENTSPEED 200

Star::Star(sf::Font& f, float timeToStart)
    :textBox("", f)
{
    m_timer = 0;
    m_timeToStart = timeToStart;
    if(!texture.loadFromFile("res/star.png")){
        std::cout <<"reclamo els meus drets de ser carregat de fitxer!" << std::endl;
        exit(0);
    }
    setTexture(texture);

    setOrigin(getGlobalBounds().width/2, getGlobalBounds().height/2);
}

void Star::setSentence(std::string s){
    textBox.setSentence(s);
}

void Star::update(float dt) {

    if(canSpeak) m_timer += dt;
    if(canSpeak && m_timer > m_timeToStart){
        textBox.setPosition(sf::Vector2f(getPosition().x - textBox.getGlobalBounds().width/2, getPosition().y -120));
        textBox.update(dt);
        //std::cout << "SPEAKING YO______________________________________________________________________________________________" << std::endl;
    }
}

void Star::render(sf::RenderTarget &target){
    target.draw(*this);
    textBox.setPosition(sf::Vector2f(getPosition().x - textBox.getGlobalBounds().width/2, getPosition().y -80));
    target.draw(textBox);
}

void Star::setCanSpeak(bool value)
{
    m_timer = 0.0;
    canSpeak = value;
}

bool Star::getCanSpeak() const
{
    return canSpeak;
}


