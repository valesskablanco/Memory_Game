#ifndef interface_h
#define interface_h

#define WINDOW_W 800
#define WINDOW_H 800
#define BOARD_SIZE 30
#define CARD_H 100
#define CARD_W 75
#define SPACE_H 15
#define SPACE_W 15

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "client.hpp"
#include "button.hpp"
#include "../Utils/common.hpp"

using namespace sf;
class Interface
{
public:
    /**
     * @brief Constructor.
     */
    Interface();
    void run();
    void paintMatrix();
    void updateButtons();
    void drawLabels();
    void updatePoints(int player);

private:
    RenderWindow *window;
    Client *client;
    Button buttons[BOARD_SIZE];
    Text player_1;
    Text player_2;
    Text player_points_1;
    Text player_points_2;
    Text instructions;
    Font font;
    int points_1;
    int points_2;
};
#endif