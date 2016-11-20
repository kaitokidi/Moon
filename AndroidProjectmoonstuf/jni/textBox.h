#ifndef TB_H
#define TB_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class TextBox : public sf::Text {

public:

    TextBox(std::string s, sf::Font& f);

    bool finished(){
        if (m_timer > 3){
            return true;
        }
        return false;
    }

    void setSentence(std::string& s);
    void update(float dt);

private:

    int m_index;
    float maxTime;
    float m_timer;
    std::string m_completeString;

};

#endif
