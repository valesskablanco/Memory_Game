#include "dataStruct.hpp"

using namespace std;

// card takes 16 bytes

struct Card
{

    int i, j, ID, status;
};

dataStruct::dataStruct()
{
    createFile();
    cout << "File created \n";
    createPagedMemory(10);
    cout << "Paged Memory Loaded \n";
}

void dataStruct::createFile()
{
    srand(time(0));
    vector<int> types{0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
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

            cout << "Card " << i << "," << j << ": " << n << endl;
        }
    }

    cout << endl;
}

// reading a binary file

card dataStruct::getFCard(int i, int j)
{

    fstream file;
    char *buffer = (char *)malloc(sizeof(Card));

    file.open("cards.txt", fstream::in | fstream::out | fstream::binary);

    file.seekg(i * COLUMNS * sizeof(Card) + j * sizeof(Card), ios::beg); // 6 is the amount of cards in a row
    file.read(buffer, sizeof(Card));
    file.close();

    Card *c = (Card *)buffer;                             // instance the Struct Card
    card actualCard = card(c->i, c->j, c->ID, c->status); // instance the Class Card
    cout << "Getting Card " << c->i << "," << c->j << ": " << c->ID << endl;
    delete buffer;

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
        file.seekg(i * COLUMNS * sizeof(Card) + j * sizeof(Card), fstream::beg); // 6 is the amount of cards in a row
        file.write((char *)&newCard, sizeof(Card));
        file.close();
    }
    else
    {
        cout << "File can't be reached \n";
    }
}

void dataStruct::createPagedMemory(int size)
{
    // create a vector with the loaded cards
    this->memory.clear();
    this->memory_size = size;

    for (int i = 0; i < size; i++)
    {
        int rand_i = rand() % ROWS;
        int rand_j = rand() % COLUMNS;
        card loaded_card = getFCard(rand_i, rand_j);
        this->memory.push_back(loaded_card);
    }
}

int dataStruct::isCardinMemory(int i, int j)
{
    int lim = this->memory_size;
    for (int n = 0; n < lim; n++)
    {
        if (this->memory[n].i == i && this->memory[n].j == j)
        {
            return n;
        }
    }

    return -1;
}

char dataStruct::getCardfromMemory(int i, int j)
{
    int n = isCardinMemory(i, j);
    if (n >= 0)
    {
        return '1';
    }
    else
    {
        replaceCard(i, j);
        return '0';
    }
}

void dataStruct::printMemory()
{
    int lim = this->memory_size;
    for (int n = 0; n < lim; n++)
    {
        this->memory[n].print();
    }
}

// this method loads a new card to the memory, replacing a random one
void dataStruct::replaceCard(int i, int j)
{
    srand(time(0));

    if (this->memory_size > 0)
    {
        int n = rand() % this->memory_size;
        this->memory.erase(this->memory.begin() + n);
        // random object erased
    }

    card Card = getFCard(i, j);
    this->memory.push_back(Card);
}

void dataStruct::shuffle()
{
    this->matrix_size -= 2;
    this->memory_size = this->matrix_size / 3;
    createPagedMemory(this->memory_size);
    cout << "Shuffle completed \n";
}

char dataStruct::verify(int i1, int j1, int i2, int j2)
{
    card Card1 = getFCard(i1, j1);
    card Card2 = getFCard(i2, j2);

    cout << Card1.ID << endl;
    cout << Card2.ID << endl;

    if (Card1.ID == Card2.ID)
    {
        shuffle();
        return '1';
    }
    else
    {
        return '0';
    }
}