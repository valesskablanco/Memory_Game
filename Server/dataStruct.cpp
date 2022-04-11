#include "dataStruct.hpp"

using namespace std;

// card takes 16 bytes

struct Card
{

    int i, j, ID, status;
};

void dataStruct::createFile()
{
    srand(time(0));
    vector<int> types{0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4};
    int size = MATRIX_SIZE;
    int random;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            random = rand() % size;
            int n = types[random];
            setFCard(i, j, n, 0);
            types.erase(types.begin() + random);
            size -= 1;
        }
    }
}

// reading a binary file

card dataStruct::getFCard(int i, int j)
{

    fstream file;

    file.open("cards.txt", fstream::in | fstream::out | fstream::binary);

    file.seekg(i * 6 * sizeof(Card) + j * sizeof(Card), ios::beg); //6 is the amount of cards in a row
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

void dataStruct::setFCard(int i, int j, int ID, int status)
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
        file.seekg(i * 6 * sizeof(Card) + j * sizeof(Card), fstream::beg); //6 is the amount of cards in a row
        file.write((char *)&newCard, sizeof(Card));
        file.close();
    }
    else
    {
        cout << "File can't be reached \n";
    }
}