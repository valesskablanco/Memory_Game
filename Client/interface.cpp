#include "interface.hpp"

using namespace std;
using namespace sf;

Interface::Interface()
{
    // create the window
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_W, WINDOW_H), "Memory Game");
    // create a new client
    this->client = new Client();
    // if needed, use this->client->Send() to send information to the server

    for (int i = 0; i < BOARD_SIZE; ++i)
    {

        //TROUBLESHOTING
        int type = rand() % CARD_TYPES;
        this->buttons[i] = new Button(type, this->window);
        cout << type;
    }
}

void Interface::run()
{
    Event event;

    while (this->window->isOpen())
    {
        while (this->window->pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed)
                this->window->close();
        }

        this->window->clear(sf::Color::White);
        this->paintMatrix();
        this->window->display();
    }

    // when game finishes close socket
    // this->client->CloseSocket();
}

void Interface::paintMatrix()
{
    // dibujar botones aleatoriamente

    int x = SPACE_W;
    int y = SPACE_H;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        this->buttons[i]->draw(x,y);
        x += (CARD_W + SPACE_W);

        if (x >= 540){
            x = SPACE_W;
            y += (CARD_H + SPACE_H);
        }
    }
}
