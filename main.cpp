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
  Idle, Speaking, Searching, GroupChat
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
    guia.setFillColor(sf::Color::White);
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
            std::pair <float, std::string >(0, "Hi mates!"),
            std::pair <float, std::string >(5, "Hi brother!")
        }
        ,
        {
            std::pair <float, std::string >(0, "Yo man !"),
            std::pair <float, std::string >(8, "penguins!")
        }
        ,
        {
            std::pair <float, std::string >(0, "Yo 1 !"),
            std::pair <float, std::string >(8, "pengu1ins!")
        }
        ,
        {
            std::pair <float, std::string >(0, "Yo 2 !"),
            std::pair <float, std::string >(8, "peng2uins!")
        }
        ,
        {
            std::pair <float, std::string >(0, "Yo 3 !"),
            std::pair <float, std::string >(8, "pengu3ins!")
        }
    };


    moonSentences.push_back("stufstufstuf");
    moonSentences.push_back("stufstufstuf2");
    moonSentences.push_back("stufstufstuf3");
    moonSentences.push_back("stufstufstuf4");
    moonSentences.push_back("stufstufstuf5");

    Moon moon("The life of the moon is so lonely", font);
    moon.setOrigin(moon.getGlobalBounds().width/2, moon.getGlobalBounds().height/2);

    std::vector < Star > stars;

    State::state currentState = State::Idle;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"The Moon", sf::Style::Resize|sf::Style::Close);

    window.setFramerateLimit(30);

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
                moon.setSentence(moonSentences[moonSentenceIndex]);
                ++moonSentenceIndex;
                currentState = State::Speaking;
            }
            break;
        case State::Speaking:
            //std::cout << "speaking" << std::endl;
            if(moon.textBox.finished()){
                currentState = State::Searching;
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
                groupPosition = moon.getPosition()+sf::Vector2f((w_size + rand()%w_size) * sign1,
                                                                (w_size + rand()%w_size) * sign2);


                for(auto pair: group){
                    stars.push_back(Star(font, pair.first));
                    stars[stars.size()-1].setPosition(groupPosition+sf::Vector2f((20 + rand()%100) * sign3,
                                                                                 (20 + rand()%100) * sign4));
                    stars[stars.size()-1].setSentence(pair.second);
                    //std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << pair.second << std::endl;
                }
            }
            break;
        case State::Searching:
        {
            std::cout << "seraching the meaning of life" << moon.getPosition().x << "," <<moon.getPosition().y << std::endl;
            bool goToNextState = true;
            for(Star &s : stars){
                std::cout << "star -> " << s.getPosition().x << ";" << s.getPosition().y << std::endl;
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
            //std::cout << "groupchating (. Y .)" << std::endl;
            for(Star &s : stars){
                s.update(deltatime);
            }

            bool finished = true;
            for(Star &s : stars){
                if(!s.textBox.finished()) finished = false;
            }

            if(finished) {
                stars.clear();
                currentState = State::Idle;
            }

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

        sf::Color c = sf::Color(0,0,0,1);
        window.clear(c);



        if(stars.size() > 0){
            float angle = getAngle(moon.getPosition(), stars[0].getPosition());
            std::cout << "the angle is "<< angle << std::endl;
            sf::Vector2f guiaPos;
            guiaPos.x = moon.getPosition().x + std::cos(angle*M_PI/180) * (moon.getRadius() + guia.getRadius() + 10);
            guiaPos.y = moon.getPosition().y + std::sin(angle*M_PI/180) * (moon.getRadius() + guia.getRadius() + 10);
            guia.setPosition(guiaPos);
            window.draw(guia);
        }

        for(Star &s : stars){
            s.render(window);
        }
        moon.render(window);
        window.display();

	}
}
