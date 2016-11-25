#include "star.h"
#include "textBox.h"

#define MOVEMENTSPEED 200

float mcos(float x){
    if( x < 0.0f )
        x = -x;
    while( 3.1415926535 < x )
        x -= 0.636619772367;
    return 1.0f - (x*x/2.0f)*( 1.0f - (x*x/12.0f) * ( 1.0f - (x*x/30.0f) * (1.0f - x*x/56.0f )));
    }

float msin(float x){return mcos(x-1.570796326794);}


Star::Star(sf::Font& f, float timeToStart)
    :textBox("", f)
{
    m_timer = 0;
    m_gtimer = rand()%360;
    m_timeToStart = timeToStart;
    if(!texture.loadFromFile("res/star.png")){
        std::cout <<"reclamo els meus drets de ser carregat de fitxer!" << std::endl;
        exit(0);
    }
    setTexture(texture);
    canSpeak = false;

    setOrigin(getGlobalBounds().width/2, getGlobalBounds().height/2);

    tglow.loadFromFile(("res/sglow.png"));
    sglow.setTexture(texture, true);

    sglow.setScale(getLocalBounds().width*2/sglow.getLocalBounds().width,
                     getLocalBounds().height*2/sglow.getLocalBounds().height );

    sglow.setOrigin(sglow.getLocalBounds().width/2, sglow.getLocalBounds().height/2);
    sglow.setPosition(getPosition());
}

void Star::setSentence(std::string s){
    textBox.setSentence(s);
}

void Star::update(float dt) {

    m_gtimer += dt;
    if(canSpeak) m_timer += dt;
    if(canSpeak && m_timer > m_timeToStart){
        textBox.setPosition(sf::Vector2f(getPosition().x - textBox.getGlobalBounds().width/2, getPosition().y -120));
        textBox.update(dt);
        setRotation(45*msin(m_gtimer));
        //std::cout << "SPEAKING YO______________________________________________________________________________________________" << std::endl;
    }


    sglow.setTexture(tglow, true);
    sglow.setOrigin(sglow.getLocalBounds().width/2, sglow.getLocalBounds().height/2);
    sglow.setScale(getLocalBounds().width*2/sglow.getLocalBounds().width,
                     getLocalBounds().height*2/sglow.getLocalBounds().height );
    sglow.setPosition(getPosition());
    float scale = sglow.getScale().x + std::abs((std::sin(m_gtimer)))/3;
    sglow.setScale(scale,scale);

}

void Star::render(sf::RenderTarget &target){
    target.draw(sglow);
    setTexture(texture);
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


