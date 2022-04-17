#include "button.hpp"

using namespace sf;

Button::Button() {}

Button::Button(int i, int j)
{
    this->ID[0] = i;
    this->ID[1] = j;
    buttonState = BTN_IDLE;
}

int Button::get_i()
{
    return this->ID[0];
}

int Button::get_j()
{
    return this->ID[1];
}

void Button::draw(RenderWindow *window, int x, int y)
{
    RectangleShape rect(Vector2f(75.f, 100.f));
    rect.setPosition(x, y);
    rect.setFillColor(Color::Blue);

    if (buttonState != BTN_PRESSED)
    {
        if (rect.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
        {
            buttonState = BTN_HOVER;

            // Pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                buttonState = BTN_PRESSED;
            }
        }
        else
        {
            buttonState = BTN_IDLE;
        }
    }

    switch (buttonState)
    {
    case BTN_HOVER:
        rect.setFillColor(Color::Black);
        break;

    case BTN_PRESSED:
        // quiero mostrar la carta
        rect.setFillColor(Color::Red);
        break;

    default:
        rect.setFillColor(Color::Blue);
        break;
    }

    window->draw(rect);
}

void Button::update(const sf::Vector2f mousePos)
{ /*
     this->buttonState = BTN_IDLE;

     // Hover
     if (this->rect->getGlobalBounds().contains(mousePos))
     {
         this->buttonState = BTN_HOVER;

         // Pressed
         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
         {
             this->buttonState = BTN_PRESSED;
         }
     }*/
}
