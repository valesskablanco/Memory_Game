#include "interface.hpp"

using namespace std;
using namespace sf;

Interface::Interface()
{
    // create the window
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_W, WINDOW_H), "Memory Game");

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            buttons.push_back(Button(i, j));
        }
    }

}

void Interface::run()
{
    window->setFramerateLimit(FPS);
    Event event;

    // Labels

    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed)
            {
                window->close();
                client.closeSocket();
                return;
            }
        }

        window->clear(sf::Color::White);
        this->drawLabels();
        this->paintMatrix();
        // this->checkPressed(); Verificar cuantos botones estan en el estado BTN_PRESSED
        // if checkEquals : esperar un segundo y elimina el boton del arreglo
        window->display();
    }

}

void Interface::paintMatrix()
{
    // drawing cards
    int x = SPACE_W;
    int y = SPACE_H;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        buttons[i].draw(window, client, x, y);
        x += (CARD_W + SPACE_W);

        if (x >= 540)
        {
            x = SPACE_W;
            y += (CARD_H + SPACE_H);
        }
    }
}

void Interface::drawLabels()
{
    this->font.loadFromFile("./assets/font.ttf");

    this->player_1.setFont(font);
    this->player_1.setCharacterSize(24);
    this->player_1.setString("Player 1");
    this->player_1.setFillColor(Color::Black);
    this->player_1.setPosition(600.f, 100.f);
    this->window->draw(this->player_1);

    this->player_points_1.setFont(font);
    this->player_points_1.setCharacterSize(24);
    this->player_points_1.setString(to_string(this->points_1));
    this->player_points_1.setFillColor(Color::Black);
    this->player_points_1.setPosition(600.f, 150.f);
    this->window->draw(this->player_points_1);

    this->player_2.setFont(font);
    this->player_2.setCharacterSize(24);
    this->player_2.setString("Player 2");
    this->player_2.setFillColor(Color::Black);
    this->player_2.setPosition(600.f, 200.f);
    this->window->draw(this->player_2);

    this->player_points_2.setFont(font);
    this->player_points_2.setCharacterSize(24);
    this->player_points_2.setString(to_string(this->points_2));
    this->player_points_2.setFillColor(Color::Black);
    this->player_points_2.setPosition(600.f, 250.f);
    this->window->draw(this->player_points_2);
}

void Interface::updatePoints(int player)
{
    if (player == 1)
    {
        this->points_1 += 1;
    }
    else
    {
        this->points_2 += 1;
    }
}

/*
bool Interface::checkPressed()
{
    int n = 0;

    for (int i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i].buttonState == "BTN_PRESSED")
        {
            n += 1;

            if (n == 2)
            {
                return true;
            }
        }
    }

    return false;
}*/
