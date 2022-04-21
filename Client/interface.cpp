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

    this->instructions.setString("Player's 1 turn");
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

        if (this->checkPressed())
        {
            usleep(5000);

            if (this->checkEquals())
            {
                updatePoints(this->turn);
                usleep(2000000);

                // take cards out
                int i = 0;

                while (i < this->buttons.size())
                {
                    if (this->buttons[i].buttonState == 2)
                        this->buttons.erase(this->buttons.begin() + i);
                    else
                        i++;
                }
                updateTurn();
            }
            else
            {
                usleep(2000000);

                // cards to idle status
                for (int i = 0; i < this->buttons.size(); ++i)
                    this->buttons[i].buttonState = BTN_IDLE;

                updateTurn();
            }
        }

        if (this->buttons.size() == 0)
        {
            this->instructions.setString(winner());
            this->drawLabels();
            window->display();

            usleep(1500000);
            
            window->close();
            client.closeSocket();
        }

        this->playingButtons.clear();
        this->drawLabels();
        this->paintMatrix();
        window->display();
    }
}

void Interface::paintMatrix()
{
    // drawing cards
    int x = SPACE_W;
    int y = SPACE_H;

    for (int i = 0; i < buttons.size(); ++i)
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

    this->instructions.setFont(font);
    this->instructions.setCharacterSize(24);
    this->instructions.setFillColor(Color::Black);
    this->instructions.setPosition(250.f, 600.f);
    this->window->draw(this->instructions);
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

void Interface::updateTurn()
{
    if (this->turn == 1)
    {
        this->turn = 2;
        this->instructions.setString("Player's 2 turn");
    }
    else
    {
        this->turn = 1;
        this->instructions.setString("Player's 1 turn");
    }
}

bool Interface::checkPressed()
{
    int n = 0;

    for (int i = 0; i < buttons.size(); ++i)
    {
        // Aqui vamos agregando cada uno de los botones que fue presionado
        if (buttons[i].buttonState == 2)
        {
            this->playingButtons.push_back(buttons[i]);
            n++;

            // Esto es equivalente al return true que tenias antes
            if (n == 2)
                return true;
            /*if (n == 1)
            {
                this->playingButtons.push_back(buttons[i]);
            }
            else if (n == 2 && (playingButtons[0].i == buttons[i].i && playingButtons[0].j == buttons[i].j))
            {
                n -= 1;
            }
            else if (n == 2 && (playingButtons[0].i != buttons[i].i && playingButtons[0].j != buttons[i].j))
            {
                this->playingButtons.push_back(buttons[i]);
                return true;
            }*/
        }
    }

    return false;
}

bool Interface::checkEquals()
{
    int i1 = this->playingButtons[0].i;
    int j1 = this->playingButtons[0].j;
    int i2 = this->playingButtons[1].i;
    int j2 = this->playingButtons[1].j;

    char char_array[BUFFER_SIZE];
    char_array[0] = '1';
    char_array[1] = i1 + '0';
    char_array[2] = j1 + '0';
    char_array[3] = i2 + '0';
    char_array[4] = j2 + '0';
    char_array[5] = '\0';

    if (client.send(char_array) == '0')
    {
        return false;
    }
    else if (client.send(char_array) == '1')
    {
        return true;
    }
    else
    {
        return false;
    }
}

string Interface::winner()
{
    if (this->points_1 > this->points_2)
    {
        return "PLAYER 1 WINS";
    }
    else if (this->points_2 > this->points_1)
    {
        return "PLAYER 2 WINS";
    }
    else
    {
        return "TIE";
    }
}