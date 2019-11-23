#include "model/BlockEmerald.h"
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
BlockEmerald::BlockEmerald(std::vector<float> s):Block(s,12.0,EnumBlock::EMERALD)
{
    //ctor
}
/**
*   Default Constructor
*/
BlockEmerald::BlockEmerald(){}
/**
*   Destructor
*   Not Implemented
*/
BlockEmerald::~BlockEmerald()
{
    //dtor
}
/**
*   Copy constructor
*   Inherits of copy constructor from Block
*   @param other : a reference constant BlockEmerald
*/
BlockEmerald::BlockEmerald(const BlockEmerald& other):Block(other)
{
    //copy ctor
}
/**
*   Operator= overloading
*   If object current and other are not equals, inherits of operator= overloading from Block
*   @param other : a reference constant BlockEmerald
*/
BlockEmerald& BlockEmerald::operator=(const BlockEmerald& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
