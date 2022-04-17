#ifndef button_h
#define button_h

#include <SFML/Graphics.hpp>
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
    int get_i();
    int get_j();
    void draw(sf::RenderWindow *window, int x, int y);
    void update(const sf::Vector2f mousePos);

private:
    int ID[2];
    BtnState buttonState;
};

#endif
