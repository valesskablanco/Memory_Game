#include "dataStruct.hpp"

using namespace std;

// card takes 16 bytes

struct Card
{

    int i, j, ID, status;
};
/**
 * @brief Construct a new dataStruct object
 * It creates a file randomly
 * It creates a vector cards from the file
 */
dataStruct::dataStruct()
{
    createFile();
    cout << "File created \n";
    createPagedMemory(10);
    cout << "Paged Memory Loaded \n";
}

/**
 * @brief Creates a file with random sorted cards
 */
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
        }
    }
}

/**
 * @brief Reads a binary file
 * @param i position i in disk's matrix
 * @param j position j in disk's matrix
 * @return Card 
 */

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
    delete buffer;

    return actualCard;
}

/**
 * @brief Writes a binary file
 * @param i position i in disk's matrix
 * @param j position j in disk's matrix 
 */
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

/**
 * @brief Loads a third part of the disk cards in memory
 * @param size of the vector needed
 */
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

/**
 * @brief Checks if the card is loaded in memory
 * @param i position i in memory vector
 * @param j position j in memory vector
 * @return int
 */
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

/**
 * @brief Looks for a card in memory and updates page faults/hits
 * @param i position i in memory vector
 * @param j position j in memory vector
 * @return char
 */
char dataStruct::getCardfromMemory(int i, int j)
{

    int n = isCardinMemory(i, j);
    if (n >= 0)
    {
        this->page_hits++;
        return '1';
    }
    else
    {
        this->page_faults++;
        replaceCard(i, j);
        return '0';
    }
}

/**
 * @brief replaces a card from memory
 * @param i position i in memory vector
 * @param j position j in memory vector
 */
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

/**
 * @brief Changes randomly the card in memory
 */
void dataStruct::shuffle()
{
    this->matrix_size -= 2;
    if (this->matrix_size > 3)
    {
        this->memory_size = this->matrix_size / 3;
        createPagedMemory(this->memory_size);
    }
    else
    {
        createPagedMemory(1);
    }
}

/**
 * @brief Veryfis if two card have the same ID
 * @param i1 position i1 in file
 * @param j1 position j1 in file
 * @param i2 position i2 in file
 * @param j2 position j2 in file
 * @return char
 */
char dataStruct::verify(int i1, int j1, int i2, int j2)
{
    
    card Card1 = getFCard(i1, j1);
    card Card2 = getFCard(i2, j2);
 
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
/**
 * @brief Gets the memory vector size
 * @return int
 */
int dataStruct::getMemorySize()
{
    return (this->memory.size() * sizeof(Card));
}
/**
 * @brief Gets the page fault from paged memory
 * @return int
 */
int dataStruct::getPageFaults()
{
    return this->page_faults;
}
/**
 * @brief Gets the page hits from paged memory
 * @return int
 */
int dataStruct::getPageHits()
{
    return this->page_hits;
}