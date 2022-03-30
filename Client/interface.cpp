#include "interface.hpp"

using namespace std;

Interface::Interface(){

    //constructor

    //create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Memory Game");

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                //close window
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            window.display();
        }
}
