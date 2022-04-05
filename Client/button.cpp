#include "button.hpp"

using namespace sf;

Button::Button() {}

Button::Button(int id, RenderWindow *window)
{
    this->ID = id;
    this->window = window;
    this->rect = new RectangleShape(Vector2f(75.f, 100.f));
    this->rect->setFillColor(Color::Blue);
}

int Button::getID()
{
    return this->ID;
}

void Button::draw(int x, int y)
{
    this->rect->setPosition(x, y);
    this->window->draw(*this->rect);
}
