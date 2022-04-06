#ifndef interface_h
#define interface_h

#define WINDOW_W 800
#define WINDOW_H 800
#define BOARD_SIZE 30
#define BOARD_H 6
#define BOARD_W 5
#define CARD_TYPES 5
#define CARD_H 100
#define CARD_W 75
#define SPACE_H 15
#define SPACE_W 15

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "client.hpp"
#include "button.hpp"

class Interface
{
public:
    /**
     * @brief Constructor.
     */
    Interface();
    void run();
    void paintMatrix();

private:
    sf::RenderWindow *window;
    Client *client;
    Button *buttons[BOARD_SIZE];
};
#endif