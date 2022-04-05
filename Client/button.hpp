#ifndef button_h
#define button_h

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
public:
    // Add Rect dimensions
    // Add Rect color
    Button();
    Button(int id, sf::RenderWindow *window);
    int getID();
    void draw(int x, int y);

private:
    int ID;
    sf::RenderWindow *window;
    sf::RectangleShape *rect;
};

#endif
