#include "card.hpp"

using namespace std;

card::card(int i, int j, int ID, int status)
{

    this->i = i;
    this->j = j;
    this->ID = ID;
    this->status = status;
}

void card::getPath()
{
    switch (this->ID)
    {
    case 0:
        this->path = "./assets/star.png";
        break;
    case 1:
        this->path = "./assets/square.png";
        break;
    case 2:
        this->path = "./assets/circle.png";
        break;
    case 3:
        this->path = "./assets/heart.png";
        break;
    case 4:
        this->path = "./assets/triangle.png";
        break;
    }
}

void card::encodeImg()
{
    getPath();
    ifstream image(this->path, ios::in | ios::binary);

    while (!image.eof())
    {
        ch = image.get();
        this->img.push_back(ch);
    }
    image.close();
}

void card::print()
{
    cout << this->path << endl;
    cout << this->img.size() << endl;
}
