#ifndef interface_h
#define interface_h

#define WINDOW_W 800
#define WINDOW_H 650
#define BOARD_SIZE 30
#define CARD_H 100
#define CARD_W 75
#define SPACE_H 15
#define SPACE_W 15

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <array>
#include <unistd.h>
#include <string>
#include "client.hpp"
#include "button.hpp"
#include "../Utils/common.hpp"

using namespace sf;
using namespace std;
class Interface
{
public:
    Interface();
    void run();
    void paintMatrix();
    void drawLabels();
    void updateTurn();
    void updatePoints(int player);
    bool checkPressed();
    bool checkEquals();
    string winner();
    bool checkMemory();

private:
    RenderWindow *window;
    Client client;
    vector<Button> buttons;
    string player1_name;
    string player2_name;
    Text player_1;
    Text player_2;
    Text player_points_1;
    Text player_points_2;
    Text instructions;
    Font font;
    int points_1;
    int points_2;
    int turn = 1;
    vector<Button> playingButtons;
};
#endif