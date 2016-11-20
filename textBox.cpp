#include "textBox.h"



TextBox::TextBox(std::string s, sf::Font &f)
{
    setFont(f);
    m_index = 0;
    maxTime = 0.05;
    m_timer = 0.0;
    m_completeString = s;
}

void TextBox::setSentence(std::string &s)
{
    m_index = 0;
    m_timer = 0.0;
    m_completeString = s;
}

void TextBox::update(float dt)
{

    m_timer += dt;
    if(m_timer > maxTime && m_index < m_completeString.size()){
        setString(getString()+m_completeString[m_index]);
        ++m_index;
        m_timer = 0;

        //std::cout << ": (   " << m_completeString[m_index-1] << std::endl;
    }
    else if(m_timer >= 3 && m_index >= m_completeString.size() && m_completeString.size() > 0){
  //      std::cout << "DELETEVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
        setString("");
        m_completeString = "";
    }
    else {
       /* std::cout << m_completeString << " nd " << std::string(getString()) <<"VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
                std::cout << m_timer <<"VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
                        std::cout << maxTime << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
                                std::cout << m_index << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
                                        std::cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
                                                std::cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
                                                        std::cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl;
*/
    }
}
