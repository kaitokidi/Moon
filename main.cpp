#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>
#include "moon.h"
#include "star.h"

bool isWhite(sf::Image& image, float px, float py){
	return image.getPixel(px, py) == sf::Color::White;
}

float getAngle(sf::Vector2f &orig, sf::Vector2i &des) {
    return std::atan2(des.y - orig.y, des.x - orig.x)*180/(M_PI);
}


namespace State{
enum state {
  Idle, Speaking, Searching, GroupChat, fadeOut
};
}

float distance(const sf::Vector2f &orig, const sf::Vector2f &des) {
    return std::sqrt(std::pow(std::abs(des.x-orig.x), 2) + std::pow(std::abs(des.y-orig.y), 2));
}

float getAngle(const sf::Vector2f &orig,const sf::Vector2f &des) {
    return std::atan2(des.y - orig.y, des.x - orig.x)*180/(M_PI);
}

int main(){

    /* initialize random seed: */
    srand (time(NULL));

	//SFML OBJECTS
	sf::View view;
	sf::Event event;
	sf::Clock deltaClock;

    sf::CircleShape guia;
    guia.setRadius(10);
    guia.setFillColor(sf::Color(200,200,200,50));
    guia.setOrigin(guia.getLocalBounds().width/2, guia.getLocalBounds().height/2);

    float deltatime = 0.0;

    sf::Font font;
    font.loadFromFile("res/font.otf");

    int moonSentenceIndex = 0;
    std::vector <std::string> moonSentences;

    int groupIndex = 0;
    std::vector< std::vector <std::pair <float, std::string > > > groups =
    {
        {
            std::pair <float, std::string >(0, "Hi friend!"),
            std::pair <float, std::string >(5, "I've missed you so much!")
        }
        ,
        {
            std::pair <float, std::string >(0, "Glad you are here!"),
            std::pair <float, std::string >(6, "I Really love you : )!")
        }
        ,
        {
        }
        ,
        {
            std::pair <float, std::string >(0, "You are everything to me!"),
            std::pair <float, std::string >(6, "You are awesome!"),
            std::pair <float, std::string >(10, "Guys are you getting sentimental?")
        }
        ,
        {
            std::pair <float, std::string >(0, "Loneliness is hard to accept!"),
            std::pair <float, std::string >(6, "Don't worry, we are good now!")
        }
        ,
        {}
        ,
        {}
    };


    moonSentences.push_back("I'm so alone in this universe... \n Is hard to live this way...");
    moonSentences.push_back("I wish someone missed me too...");
    moonSentences.push_back("Has to be so nice to be loved...");
    moonSentences.push_back("Hope someone would care about me... \n I'm sure is a warm feeling...");
    moonSentences.push_back("Friendship... It hurts so much not having it...");
    moonSentences.push_back("Are we? I'm invisible to them...");
    moonSentences.push_back("But wait...");
    moonSentences.push_back("What if everyone was talking about me this whole time?");

    Moon moon("The life of the moon is so lonely", font);
    moon.setOrigin(moon.getLocalBounds().width/2, moon.getLocalBounds().height/2);

    std::vector < Star > stars;

    State::state currentState = State::Idle;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"The Moon", sf::Style::Resize|sf::Style::Close);

    window.setFramerateLimit(30);

    float fadeOutValue = 0;

	//GAME LOOP
	while(window.isOpen()){

        //Deltatime
        deltatime = deltaClock.restart().asSeconds();

		//Loop for handling events
		while(window.pollEvent(event)){
			switch (event.type){
				//Close event
				case sf::Event::Closed:
					window.close();
					break;
				//KeyPressed event
				case  sf::Event::KeyPressed:
					//Close key
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
					}
					if (event.key.code == sf::Keyboard::Q) {
						window.close();
					}
                //Default
				default:
					//Do nothing
					break;
			}
		}	

sf::Vector2f groupPosition;
        switch(currentState){
        case State::Idle:
            //std::cout << "idle" << std::endl;
            if(moon.textBox.finished()){
                //std::cout << "boobs" << std::endl;
                if(moonSentenceIndex >= moonSentences.size()) moon.setSentence(": )");
                else moon.setSentence(moonSentences[moonSentenceIndex]);
                ++moonSentenceIndex;
                currentState = State::Speaking;
            }
            break;
        case State::Speaking:
            //std::cout << "speaking" << std::endl;
            if(moon.textBox.finished()){
                currentState = State::Searching;

                if(groupIndex < groups.size()){
                    auto group = groups[groupIndex];
                    ++groupIndex;

                    int sign1 = -1;
                    if( rand()%2 == 0) sign1 = 1;
                    int sign2 = -1;
                    if( rand()%2 == 0) sign2 = 1;
                    int sign3 = -1;
                    if( rand()%2 == 0) sign3 = 1;
                    int sign4 = -1;
                    if( rand()%2 == 0) sign4 = 1;

                    int w_size = static_cast<int>(window.getSize().y);
                    groupPosition = moon.getPosition() + sf::Vector2f((w_size/5 + rand()%w_size) * sign1,
                                                                    (w_size/5 + rand()%w_size) * sign2);


                    for(auto pair: group){
                        stars.push_back(Star(font, pair.first));
                        stars[stars.size()-1].setPosition(groupPosition+sf::Vector2f((20 + rand()%150) * sign3,
                                                                                     (20 + rand()%150) * sign4));
                        stars[stars.size()-1].setSentence(pair.second);
                        //std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << pair.second << std::endl;
                    }
                }
                else {
                    int size = 20;
                    stars.push_back(Star(font, 2));
                    stars[stars.size()-1].setPosition(sf::Vector2f(0.0,0.0));
                    stars[stars.size()-1].setSentence(": )");

                    stars.push_back(Star(font, 3));
                    stars[stars.size()-1].setPosition(sf::Vector2f(1*size,-1.42*size));
                    stars[stars.size()-1].setSentence("<3");

                    stars.push_back(Star(font, 3));
                    stars[stars.size()-1].setPosition(sf::Vector2f(-1*size,-1.42*size));
                    stars[stars.size()-1].setSentence("<3");

                    stars.push_back(Star(font, 4));
                    stars[stars.size()-1].setPosition(sf::Vector2f(2*size,-2.84*size));
                    stars[stars.size()-1].setSentence(": )");

                    stars.push_back(Star(font, 4));
                    stars[stars.size()-1].setPosition(sf::Vector2f(-2*size,-2.84*size));
                    stars[stars.size()-1].setSentence("<3");

                    stars.push_back(Star(font, 5));
                    stars[stars.size()-1].setPosition(sf::Vector2f(1.6*size,-3.9*size));
                    stars[stars.size()-1].setSentence(": )");

                    stars.push_back(Star(font, 3));
                    stars[stars.size()-1].setPosition(sf::Vector2f(-1.4*size,-3.9*size));
                    stars[stars.size()-1].setSentence("( :");

                    stars.push_back(Star(font, 6));
                    stars[stars.size()-1].setPosition(sf::Vector2f(0*size,-3.1*size));
                    stars[stars.size()-1].setSentence("<3");
                }
            }
            break;
        case State::Searching:
        {
            ////std::cout << "seraching the meaning of life" << moon.getPosition().x << "," <<moon.getPosition().y << std::endl;
            bool goToNextState = true;
            for(Star &s : stars){
               //// std::cout << "star -> " << s.getPosition().x << ";" << s.getPosition().y << std::endl;
                if(distance(moon.getPosition(), s.getPosition()) > window.getSize().y/2) goToNextState = false;
            }
            if(goToNextState){
                for(Star &s : stars){
                    s.setCanSpeak(true);
                }
                currentState = State::GroupChat;
            }

            break;
        }
        case State::GroupChat:
        {
            //std::cout << "groupchating (. Y .)" << std::endl;
            for(Star &s : stars){
                s.update(deltatime);
            }

            bool finished = true;
            for(Star &s : stars){
                if(!s.textBox.finished()) finished = false;
            }

            if(finished) {
                fadeOutValue = 0.0;
                currentState = State::fadeOut;
            }
            break;
        }
        case State::fadeOut:
            if(fadeOutValue <= 1){
                fadeOutValue += deltatime* 0.5;
                for(Star &s : stars){
                    s.setColor(sf::Color(255,255,255, 255-255*fadeOutValue));
                }
            }
            else {
                stars.clear();
                currentState = State::Idle;
            }
            break;
        default:
            break;
        }

        moon.update(deltatime);
		//Set view values
        sf::Vector2f viewPosition;
        view.reset(sf::FloatRect(moon.getPosition().x, moon.getPosition().y,
                                 window.getSize().x, window.getSize().y));

        viewPosition.y = moon.getPosition().y+10;
        viewPosition.x = moon.getPosition().x+10;
		view.setCenter(viewPosition);
		view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));

		//Set window view, draw and display
        window.setView(view);

        sf::Color c = sf::Color(0,0,0,0.1);
        window.clear(c);



        if(stars.size() > 0){
            float angle = getAngle(moon.getPosition(), stars[0].getPosition());
            //std::cout << "the angle is "<< angle << std::endl;
            sf::Vector2f guiaPos;
            guiaPos.x = moon.getPosition().x + std::cos(angle*M_PI/180) * (moon.getRadius()*3 + guia.getRadius());
            guiaPos.y = moon.getPosition().y + std::sin(angle*M_PI/180) * (moon.getRadius()*3 + guia.getRadius());
            guia.setPosition(guiaPos);
            window.draw(guia);
        }

        for(Star &s : stars){
            /*
            float dist = std::abs(distance(moon.getPosition(), s.getPosition()));
            if(dist < 2*moon.getGlobalBounds().width){
                float factor = dist/2.f*moon.getGlobalBounds().width;
                s.setColor(sf::Color(255,255,255,int(255*factor)));
            }else s.setColor(sf::Color(255,255,255,255));
            */
            s.render(window);
            //window.draw(s);
        }
        moon.render(window);
        window.display();

	}
}
