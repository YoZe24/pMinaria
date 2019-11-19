#include "model/Pickaxe.h"

using namespace std;

Pickaxe::Pickaxe()
{
    this->px_s = new PX_Strategy_Emerald;
}


Pickaxe::~Pickaxe()
{
    cout << "destructor pickaxe";
    delete px_s;
}

Pickaxe::Pickaxe(const Pickaxe& other):px_s(other.px_s)
{
}

EnumPickaxe Pickaxe::getType()const{
    return px_s->getType();
}

float Pickaxe::getPower()const{
    return px_s->getPower();
}

PX_Strategy* Pickaxe::getNextStrategy(EnumPickaxe ep){
    switch(ep){
        case EnumPickaxe::PX_WOOD:              return new PX_Strategy_Stone;
        case EnumPickaxe::PX_STONE:             return new PX_Strategy_Iron;
        case EnumPickaxe::PX_IRON:              return new PX_Strategy_Gold;
        case EnumPickaxe::PX_GOLD:              return new PX_Strategy_Diamond;
        case EnumPickaxe::PX_DIAMOND:           return new PX_Strategy_Emerald;
        case EnumPickaxe::PX_EMERALD:           return this->px_s;
        default:                                return this->px_s;
    }
}

void Pickaxe::setPXStrategy(){
    setPXStrategy(getNextStrategy(px_s->getType()));
}

void Pickaxe::setPXStrategy(PX_Strategy* px){
    this->px_s = px;
}

bool Pickaxe::isBreakable(EnumBlock b){
    return this->px_s->isBreakable(b);
}

PX_Strategy::PX_Strategy(float power,int nbOresCraft,EnumPickaxe ep):power(power),nbOresCraft(nbOresCraft),type(ep)
{
}

PX_Strategy::PX_Strategy(const PX_Strategy& other):power(other.power),nbOresCraft(other.nbOresCraft),type(other.type)
{
}

PX_Strategy& PX_Strategy::operator=(const PX_Strategy& ps){
    if(this != &ps){
        this->nbOresCraft = ps.nbOresCraft;
        this->power = ps.power;
        this->type = ps.type;
    }
    return *this;
}

EnumPickaxe PX_Strategy::getType()const{
    return this->type;
}

PX_Strategy_Wood::PX_Strategy_Wood(float power,int nbOresCraft,EnumPickaxe ep):PX_Strategy(power,nbOresCraft,EnumPickaxe::PX_WOOD)
{
}

PX_Strategy_Wood::PX_Strategy_Wood(const PX_Strategy_Wood& other):PX_Strategy(other)
{}

bool PX_Strategy_Wood::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
        case EnumBlock::DIRT:       return true;
        case EnumBlock::STONE:      return true;
    }
    return false;
}

PX_Strategy_Wood& PX_Strategy_Wood::operator=(const PX_Strategy_Wood& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}

PX_Strategy_Stone::PX_Strategy_Stone(float power,int nbOresCraft,EnumPickaxe ep):PX_Strategy(power,nbOresCraft,ep)
{}

bool PX_Strategy_Stone::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:   return false;
        case EnumBlock::DIRT:   return true;
        case EnumBlock::STONE:  return true;
        case EnumBlock::IRON:   return true;
    }
    return false;
}

PX_Strategy_Stone& PX_Strategy_Stone::operator=(const PX_Strategy_Stone& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}

PX_Strategy_Iron::PX_Strategy_Iron(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}

bool PX_Strategy_Iron::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
        case EnumBlock::DIAMOND:    return false;
        case EnumBlock::EMERALD:    return false;
    }
    return true;
}

PX_Strategy_Iron& PX_Strategy_Iron::operator=(const PX_Strategy_Iron& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}

PX_Strategy_Gold::PX_Strategy_Gold(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}

bool PX_Strategy_Gold::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
        case EnumBlock::EMERALD:    return false;
    }
    return true;
}

PX_Strategy_Gold& PX_Strategy_Gold::operator=(const PX_Strategy_Gold& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}

PX_Strategy_Diamond::PX_Strategy_Diamond(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}

bool PX_Strategy_Diamond::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
    }
    return true;
}

PX_Strategy_Diamond& PX_Strategy_Diamond::operator=(const PX_Strategy_Diamond& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}

PX_Strategy_Emerald::PX_Strategy_Emerald(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}

bool PX_Strategy_Emerald::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
    }
    return true;
}

PX_Strategy_Emerald& PX_Strategy_Emerald::operator=(const PX_Strategy_Emerald& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}

