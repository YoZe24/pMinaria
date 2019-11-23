#include "model/BlockDirt.h"

using namespace std;

/**
*   Sub-class of Block
*   Inherits of Block -> changement = default value for duration and type attributes
*/

/**
*   Constructor
*   Inhertis from Block
*   Default value (duration, type)
*   @param s : a float vector who represent pourcent of spawn
*   @param d : a float who represent breakable duration of block
*   @param t : a EnumBlock varaible who represent the type of the block
*/
BlockDirt::BlockDirt(vector<float> s):Block(s,0.30,EnumBlock::DIRT)
{
}
/**
*   Default Constructor
*/
BlockDirt::BlockDirt(){}

/**
*   Destructor
*   Not Implemented
*/
BlockDirt::~BlockDirt()
{
    //dtor
}
/**
*   Copy constructor
*   Inherits of copy constructor from Block
*   @param other : a reference constant BlockDirt
*/
BlockDirt::BlockDirt(const BlockDirt& other):Block(other)
{
    //copy ctor
}
/**
*   Operator= overloading
*   If object current and other are not equals, inherits of operator= overloading from Block
*   @param other : a reference constant BlockDirt
*/
BlockDirt& BlockDirt::operator=(const BlockDirt& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
