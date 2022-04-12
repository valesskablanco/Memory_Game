#include "card.hpp"

card::card(int i, int j, int ID, int status){

    this->i = i;
    this->j = j;
    this->ID = ID;
    this->status = status;
}

void card::getImage(int ID){
    switch (ID)
    {
    case 0:
        this->img= "Niall.png";
        break;
    case 1:
        this->img = "Liam.png";
        break;
    case 2:
        this->img = "Zayn.png";
        break;
    case 3:
        this->img = "Harry.png";
        break;
    case 4:
        this->img = "Louis.png";
        break;
    }
}

void card::print(){
    std::cout << this->i << " " << this->j << " " << this->ID << " " << this->status << std::endl;
}