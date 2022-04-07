#include "dataStruct.hpp"

using namespace std;

// card takes 16 bytes

struct Card
{

    int i, j, ID, status;
};

void dataStruct::createFile()
{
    int n = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (n >= CARD_TYPES)
            {
                setCard(i, j, 0, 0);
                n = 1;
            }
            else
            {
                setCard(i, j, n, 0);
                n++;
            }
        }
    }
}

// reading a binary file

card dataStruct::getCard(int i, int j)
{

    fstream file;

    file.open("cards.txt", fstream::in | fstream::out | fstream::binary);

    file.seekg(i * 6 * sizeof(Card) + j * sizeof(Card), ios::beg);
    char *buffer = (char *)malloc(sizeof(Card));
    file.read(buffer, sizeof(Card));

    Card *c = (Card *)buffer;                             // instance the Struct Card
    card actualCard = card(c->i, c->j, c->ID, c->status); // instance the Class Card

    actualCard.getImage(c->ID);
    cout << "The disk loaded card is: ";
    actualCard.print();
    file.close();
    buffer = NULL;

    return actualCard;
}

void dataStruct::setCard(int i, int j, int ID, int status)
{

    fstream file;

    Card newCard;
    newCard.i = i;
    newCard.j = j;
    newCard.ID = ID;
    newCard.status = status;

    file.open("cards.txt", fstream::in | fstream::out | fstream::binary);

    if (file)
    {
        file.seekg(i * 6 * sizeof(Card) + j * sizeof(Card)), fstream::beg);
        file.write((char *)&newCard, sizeof(Card));
        file.close();
    }
    else
    {
        cout << "File can't be reached \n";
    }
}