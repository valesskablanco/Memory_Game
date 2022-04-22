#ifndef button_h
#define button_h

#include <SFML/Graphics.hpp>
#include "client.hpp"
#include <iostream>

using namespace sf;

enum BtnState
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_PRESSED
};

class Button
{
public:
    Button();
    Button(int i, int j);
    void draw(sf::RenderWindow *window, Client client, int x, int y);
    bool isInMemory();
    BtnState buttonState;
    int i;
    int j;
    int loaded;

private:
    Texture texture;
    Sprite sprite;
};

#endif
