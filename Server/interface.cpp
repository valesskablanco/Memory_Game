#include "interface.hpp"

using namespace std;
using namespace sf;


/**
 * @brief Construct a new Interface object
 * Paints memory information
 */
Interface::Interface()
{
    // create the window
    window = new sf::RenderWindow(sf::VideoMode(200, 200), "Memory Usage");
}

/**
 * @brief Runs the interface logic
 */
void Interface::run()
{
    // creating a theard for server
    //thread server_thread(&Interface::runServer, this);
    //server_thread.detach();

    window->setFramerateLimit(FPS);
    Event event;

    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return;
            }
        }
        window->clear(Color::White);
        this->drawLabels();
        window->display();
    }
}

/**
 * @brief Gets the memoryUsage
 * @return string
 */
string Interface::memoryUsage()
{
    int bytes = server.getMemorySize();
    return to_string(bytes);
}

/**
 * @brief draw the labels of the interface
 */
void Interface::drawLabels()
{
    font.loadFromFile("../Client/assets/font.ttf");

    this->memory_usage.setFont(font);
    this->memory_usage.setCharacterSize(10);
    this->memory_usage.setString("Memory Usage :" + memoryUsage() + " bytes");
    this->memory_usage.setFillColor(Color::Black);
    this->memory_usage.setPosition(15.f, 50.f);
    this->window->draw(this->memory_usage);

    this->page_faults.setFont(font);
    this->page_faults.setCharacterSize(10);
    this->page_faults.setString("Page Faults: " + to_string(server.getPageFaults()));
    this->page_faults.setFillColor(Color::Black);
    this->page_faults.setPosition(15.f, 100.f);
    this->window->draw(this->page_faults);

    this->page_hits.setFont(font);
    this->page_hits.setCharacterSize(10);
    this->page_hits.setString("Page Hits: " + to_string(server.getPageHits()));
    this->page_hits.setFillColor(Color::Black);
    this->page_hits.setPosition(15.f, 150.f);
    this->window->draw(this->page_hits);
}

void Interface::runServer()
{
    server.run();
}