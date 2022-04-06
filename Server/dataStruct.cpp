#include "dataStruct.hpp"

using namespace std;
fstream file;

// card takes 4 bytes

struct Card
{

    int i, j, ID, status;
};

void dataStruct::createFile()
{

    int n = 0;
    for (int i = 1; i <= 6; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            if (n >= CARD_TYPES)
            {
                n = 0;
                // setCard(i,j,n,0)
                n += 1;
            }
            else
            {
                // setCard(i,j,n,0)
                n += 1;
            }
        }
    }
}

// reading a binary file

card dataStruct::getCard(int i, int j)
{

    file.open("cards.txt", ios::in | ios::out | ios::binary);

    file.seekg((i - 1) * (4) * sizeof(Card) + (j - 1) * sizeof(Card), ios::beg);
    char *buffer = (char *)malloc(sizeof(Card));
    file.read(buffer, sizeof(Card));

    Card *c = (Card *)buffer;                       // instance the Struct Card
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

    Card newCard;
    newCard.i = i;
    newCard.j = j;
    newCard.ID = ID;
    newCard.status = status;

    file.open("cards.txt", ios::in | ios::out | ios::binary);

    file.seekg(((i - 1) * (4) * sizeof(Card) + (j - 1) * sizeof(Card)), ios::beg);
    file.write((char *)&newCard, sizeof(Card));
    file.close();
}