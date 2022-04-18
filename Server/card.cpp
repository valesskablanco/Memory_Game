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
        this->img= "/assets/star.png";
        break;
    case 1:
        this->img = "/assets/square.png";
        break;
    case 2:
        this->img = "/assets/circle.png";
        break;
    case 3:
        this->img = "/assets/heart.png";
        break;
    case 4:
        this->img = "/assets/triangle.png";
        break;
    }
}

void card::print(){
    std::cout << this->i << " " << this->j << " " << this->ID << " " << this->status << std::endl;
}