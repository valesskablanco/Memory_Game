#include "button.hpp"

using namespace sf;
using namespace std;

Button::Button() {}

Button::Button(int i, int j)
{
    // if needed, use this->client->Send() to send information to the server

    this->i = i;
    this->j = j;
    buttonState = BTN_IDLE;
}

void Button::draw(RenderWindow *window, Client client, int x, int y)
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
                string request = "0" + to_string(this->i) + to_string(this->j);
                cout << "Asking for: " << this->i << "," << this->j << endl;
                char char_array[BUFFER_SIZE];
                char_array[0] = '0';
                char_array[1] = this->i + '0';
                char_array[2] = this->j + '0';
                char_array[3] = '\0';
                // strcpy(char_array, request.c_str());

                client.send(char_array);

                texture.loadFromFile("./temp/rebuild.png");
                sprite.setTexture(texture);
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
        window->draw(rect);
        break;

    case BTN_PRESSED:
    {
        sprite.setPosition(x, y);
        window->draw(sprite);
    }
    break;

    default:
        rect.setFillColor(Color::Blue);
        window->draw(rect);
        break;
    }
}
