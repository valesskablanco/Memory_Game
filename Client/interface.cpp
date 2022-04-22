#include "interface.hpp"

using namespace std;
using namespace sf;

/**
 * @brief Construct a new Interface object
 * Asks for players names
 * Creates the game window
 * Creates a vector of buttons
 * Sets the instructions text string
 */
Interface::Interface()
{

    // ask for players name
    cout << "Enter Player's 1 name:" << endl;
    cin >> player1_name;
    cout << "Enter Player's 2 name:" << endl;
    cin >> player2_name;

    // create the window
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_W, WINDOW_H), "Memory Game");

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            buttons.push_back(Button(i, j));
        }
    }

    this->instructions.setString(player1_name + " turn");
}

/**
 * @brief runs the client interface
 */
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
                if (checkMemory())
                {
                    updatePoints(this->turn);
                    this->instructions.setString("Extra points!");
                    this->drawLabels();
                    this->paintMatrix();
                    window->display();
                    usleep(5000);
                }

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

/**
 * @brief paint the buttons of the cards
 */
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

/**
 * @brief draw each label of the interface
 */
void Interface::drawLabels()
{
    this->font.loadFromFile("./assets/font.ttf");

    this->player_1.setFont(font);
    this->player_1.setCharacterSize(24);
    this->player_1.setString(player1_name);
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
    this->player_2.setString(player2_name);
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

/**
 * @brief adds one point to the corresponding player
 */
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

/**
 * @brief updates the players turn
 */
void Interface::updateTurn()
{
    if (this->turn == 1)
    {
        this->turn = 2;
        this->instructions.setString(player2_name + " turn");
    }
    else
    {
        this->turn = 1;
        this->instructions.setString(player1_name + " turn");
    }
}

/**
 * @brief checks if a button is pressed
 * @return bool
 */
bool Interface::checkPressed()
{
    int n = 0;

    for (int i = 0; i < buttons.size(); ++i)
    {
        // push back every pressed button
        if (buttons[i].buttonState == 2)
        {
            this->playingButtons.push_back(buttons[i]);
            n++;

            if (n == 2)
                return true;
        }
    }

    return false;
}


/**
 * @brief checks if two cards have the same ID
 * @return bool
 */
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

    return (client.send(char_array) == '1');
}

/**
 * @brief shows the winner
 * @return string
 */
string Interface::winner()
{
    if (this->points_1 > this->points_2)
    {
        return (player1_name + " WINS");
    }
    else if (this->points_2 > this->points_1)
    {
        return (player2_name + " WINS");
    }
    else
    {
        return "TIE";
    }
}
/**
 * @brief Checks if any of the two cards is loaded in memory
 * @return bool
 */
bool Interface::checkMemory()
{
    Button button1 = this->playingButtons[0];
    Button button2 = this->playingButtons[1];

    if (button1.loaded == 1)
    {
        return true;
    }
    else if (button2.loaded == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}