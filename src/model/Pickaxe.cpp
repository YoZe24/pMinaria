#include "model/Pickaxe.h"

using namespace std;
/**
*   Class Pickaxe
*   Contains a instance of PX_Strategy (Design Pattern Strategy)
*   Contains functions to switch easily comportement according to object's type
*/

/**
*   Main Constructor
*   Agregation intern pointer (AIP)
*/
Pickaxe::Pickaxe()
{
    this->px_s = new PX_Strategy_Wood;
}

/**
*   Destructor AIP -> need to delete px_s
*/
Pickaxe::~Pickaxe()
{
    cout << "destructor pickaxe";
    delete px_s;
}
/**
*   Copy Constructor
*   Parameter passing by reference
*   @param other : A reference constant of Pickaxe object
*/
Pickaxe::Pickaxe(const Pickaxe& other):px_s(other.px_s)
{
}
/**
*   Function to return EnumPickaxe type attribute
*/
EnumPickaxe Pickaxe::getType()const{
    return px_s->getType();
}
/**
*   Function to return float power attribute
*/
float Pickaxe::getPower()const{
    return px_s->getPower();
}
/**
*   Function to return a new instance of PX_Strategy object according to EnumPickaxe ep
*   The switch allow concisely to return the good instance according to his type
*   Return a pointer of PX_Strategy
*   @param ep : A EnumPickaxe variable
*/
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
/**
*   Function to set the strategy (Desgin Pattern Strategy) -> permet switch easily of strategy (comportement)
*   Call of setStrategy(PX_Strategy* px) -> call of getNextStrategy to recup the good instance of strategy
*/
void Pickaxe::setPXStrategy(){
    setPXStrategy(getNextStrategy(px_s->getType()));
}
/**
*   Function which delete the old strategy and modifies the current strategy
*   @param px : A Pointer of an instance of PX_Strategy
*/
void Pickaxe::setPXStrategy(PX_Strategy* px){
    if(getType() != EnumPickaxe::PX_EMERALD)
        delete px_s;
    this->px_s = px;
}
/**
*   Function which return true if the type of block can be breakable according to Pickaxe type
*   The behavior will change (due to the polymorphism)according to the current strategy that has been redefined
*   @param b : an EnumBlock type
*/
bool Pickaxe::isBreakable(EnumBlock b){
    return this->px_s->isBreakable(b);
}

/**
*   Super Class of Pattern Strategy
*
*/

/**
*   Main Constructor
*   @param power : float who represent a coefficient to reduce break's time of a block
*   @param nbOresCraft : int who represent numbers of ores
*   @param ep : type of EnumPickaxe ep
*/
PX_Strategy::PX_Strategy(float power,int nbOresCraft,EnumPickaxe ep):power(power),nbOresCraft(nbOresCraft),type(ep)
{
}
/**
*   Copy Constructor
*   Recup all attributes from other Object
*   @param other : a reference constant of PX_Strategy object
*/
PX_Strategy::PX_Strategy(const PX_Strategy& other):power(other.power),nbOresCraft(other.nbOresCraft),type(other.type)
{
}
/**
*   Function virtual
*   operator= overloading
*   Recup all attributes from rhs object
*   @param rhs : a reference constant of PX_Strategy object
*/
PX_Strategy& PX_Strategy::operator=(const PX_Strategy& ps){
    if(this != &ps){
        this->nbOresCraft = ps.nbOresCraft;
        this->power = ps.power;
        this->type = ps.type;
    }
    return *this;
}
/**
*   Function to return the type attribute
*/
EnumPickaxe PX_Strategy::getType()const{
    return this->type;
}

/**
*   First sub-class of PX_Strategy
*/
/**
*   Main Constructor
*   constructor inherits from PX_Strategy constructor
*   All attributes have default value in "Pickaxe.h"
*   @param power : float who represent a coefficient to reduce break's time of a block
*   @param nbOresCraft : int who represent numbers of ores
*   @param ep : type of EnumPickaxe ep
*/
PX_Strategy_Wood::PX_Strategy_Wood(float power,int nbOresCraft,EnumPickaxe ep):PX_Strategy(power,nbOresCraft,EnumPickaxe::PX_WOOD)
{
}
/**
*   Function virtual
*   Function which return true if the type of block can be breakable according to pickaxe type
*   It is the comportement that changes according to Pickaxe type (Design Pattern Strategy)
*   @param eb : a EnumBlock variable
*/
bool PX_Strategy_Wood::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
        case EnumBlock::DIRT:       return true;
        case EnumBlock::STONE:      return true;
    }
    return false;
}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Wood object
*/
PX_Strategy_Wood& PX_Strategy_Wood::operator=(const PX_Strategy_Wood& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}


/**
*   Second sub-class of PX_Strategy
*/
/**
*   Main Constructor
*   constructor inherits from PX_Strategy constructor
*   All attributes have default value in "Pickaxe.h"
*   @param power : float who represent a coefficient to reduce break's time of a block
*   @param nbOresCraft : int who represent numbers of ores
*   @param ep : type of EnumPickaxe ep
*/
PX_Strategy_Stone::PX_Strategy_Stone(float power,int nbOresCraft,EnumPickaxe ep):PX_Strategy(power,nbOresCraft,ep)
{}
/**
*   Function virtual
*   Function to return true if the type of block can be breakable according to pickaxe type
*   It is the comportement who change according to Pickaxe type (Design Pattern Strategy)
*   @param eb : a EnumBlock variable
*/
bool PX_Strategy_Stone::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:   return false;
        case EnumBlock::DIRT:   return true;
        case EnumBlock::STONE:  return true;
        case EnumBlock::IRON:   return true;
    }
    return false;
}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
PX_Strategy_Stone& PX_Strategy_Stone::operator=(const PX_Strategy_Stone& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}


/**
*   Third sub-class of PX_Strategy
*/
/**
*   Main Constructor
*   constructor inherits from PX_Strategy constructor
*   All attributes have default value in "Pickaxe.h"
*   @param power : float who represent a coefficient to reduce break's time of a block
*   @param nbOresCraft : int who represent numbers of ores
*   @param ep : type of EnumPickaxe ep
*/
PX_Strategy_Iron::PX_Strategy_Iron(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}
/**
*   Function virtual
*   Function to return true if the type of block can be breakable according to pickaxe type
*   It is the comportement who change according to Pickaxe type (Design Pattern Strategy)
*   @param eb : a EnumBlock variable
*/
bool PX_Strategy_Iron::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
        case EnumBlock::DIAMOND:    return false;
        case EnumBlock::EMERALD:    return false;
        case EnumBlock::OBSIDIAN:   return false;
    }
    return true;
}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
PX_Strategy_Iron& PX_Strategy_Iron::operator=(const PX_Strategy_Iron& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}


/**
*   Fourth sub-class of PX_Strategy
*/
/**
*   Main Constructor
*   constructor inherits from PX_Strategy constructor
*   All attributes have default value in "Pickaxe.h"
*   @param power : float who represent a coefficient to reduce break's time of a block
*   @param nbOresCraft : int who represent numbers of ores
*   @param ep : type of EnumPickaxe ep
*/
PX_Strategy_Gold::PX_Strategy_Gold(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
bool PX_Strategy_Gold::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
        case EnumBlock::EMERALD:    return false;
        case EnumBlock::OBSIDIAN:   return false;
    }
    return true;
}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
PX_Strategy_Gold& PX_Strategy_Gold::operator=(const PX_Strategy_Gold& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}


/**
*   Fifth sub-class of PX_Strategy
*/
/**
*   Main Constructor
*   constructor inherits from PX_Strategy constructor
*   All attributes have default value in "Pickaxe.h"
*   @param power : float who represent a coefficient to reduce break's time of a block
*   @param nbOresCraft : int who represent numbers of ores
*   @param ep : type of EnumPickaxe ep
*/
PX_Strategy_Diamond::PX_Strategy_Diamond(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
bool PX_Strategy_Diamond::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
        case EnumBlock::OBSIDIAN:   return false;
    }
    return true;
}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
PX_Strategy_Diamond& PX_Strategy_Diamond::operator=(const PX_Strategy_Diamond& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}


/**
*   Sixth sub-class of PX_Strategy
*/
/**
*   Main Constructor
*   constructor inherits from PX_Strategy constructor
*   All attributes have default value in "Pickaxe.h"
*   @param power : float who represent a coefficient to reduce break's time of a block
*   @param nbOresCraft : int who represent numbers of ores
*   @param ep : type of EnumPickaxe ep
*/
PX_Strategy_Emerald::PX_Strategy_Emerald(float power,int nb,EnumPickaxe ep):PX_Strategy(power,nb,ep)
{}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
bool PX_Strategy_Emerald::isBreakable(EnumBlock eb){
    switch(eb){
        case EnumBlock::VOID:       return false;
    }
    return true;
}
/**
*   Function virtual
*   Operator= overloading
*   Inherits from operator= of PX_Strategy
*   Recup all atributes from other object
*   @param psw: a reference constant PX_Strategy_Stone object
*/
PX_Strategy_Emerald& PX_Strategy_Emerald::operator=(const PX_Strategy_Emerald& psw){
    if(this != &psw){
        PX_Strategy::operator=(psw);
    }
    return *this;
}

