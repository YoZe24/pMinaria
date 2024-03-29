#include "model/Player.h"

Player::Player(int health,bool life):Entity(health,life)
{

}

Player::~Player()
{
    //dtor
}

Player::Player(const Player& other):Entity(other)
{
    //copy ctor
}

Player& Player::operator=(const Player& other){
    if(this != &other){
        Entity::operator=(other);
    }
    return *this;
}


float Player::updatePickaxe(){
    if(ores[pickaxe.getType()] >= pickaxe.getSrategy()->getNbOresCraft()){
        pickaxe.setPXStrategy();
    }
    return pickaxe.getPower();
}

EnumPickaxe Player::getType()const{
    return this->pickaxe.getType();
}

int Player::getNbOresCraftCurrentPickaxe(){
    return this->pickaxe.getSrategy()->getNbOresCraft();
}

int Player::getNbOresCurrentPickaxe(){
    return ores[pickaxe.getType()];
}

void Player::reset(){
    Entity::reset();
    ores.clear();
    this->pickaxe.setPXStrategy(new PX_Strategy_Wood);
}
