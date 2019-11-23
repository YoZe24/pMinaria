#include "model/Block.h"

#include <sstream>

using namespace std;

/**
*   Super-class of all different block's type
*/

/**
*   Default constructor
*/
Block::Block()
{

}
/**
*   Constructor
*   @param s : a float vector who represent pourcent of spawn
*   @param d : a float who represent breakable duration of block
*   @param t : a EnumBlock varaible who represent the type of the block
*/
Block::Block(vector<float> s,float d,EnumBlock t):spawn(s),duration(d),type(t)
{

}
/**
*   Destructor
*   Not Implemented
*/
Block::~Block()
{
    //dtor
}
/**
*   Copy Constructor
*   Recup all attributes of other obejct
*   @param other : a reference constant of Block object
*/
Block::Block(const Block& other):spawn(other.spawn),duration(other.duration),type(other.type)
{
    //copy ctor
}
/**
*   Operator= overloading
*   Recup all attributes of other object if not equals of current object
*   @param other : a reference constant of Block object
*/
Block& Block::operator=(const Block& other){
    if(this != &other){
        this->spawn = other.spawn;
        this->duration = other.duration;
        this->type = other.type;
    }
    return *this;
}
/**
*   Function to print a Block object
*   Using a stringstream to inject all attributes value
*   return a string
*/
string Block::str() const{
    stringstream sstr;
    sstr << "spawn : {";
    for(float f:spawn)
        sstr << f << ",";
    sstr << "} duration : " << this->duration << ", type : " << type;
    return sstr.str();

}
