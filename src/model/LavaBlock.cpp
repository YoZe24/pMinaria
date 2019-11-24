#include "model/LavaBlock.h"

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
LavaBlock::LavaBlock(vector<float> s):Block(s,10.0,EnumBlock::LAVA)
{
    //ctor
}
/**
*   Default Constructor
*/
LavaBlock::LavaBlock(){}
/**
*   Destructor
*   Not Implemented
*/
LavaBlock::~LavaBlock()
{
    //dtor
}
/**
*   Copy constructor
*   Inherits of copy constructor from Block
*   @param other : a reference constant BlockIron
*/
LavaBlock::LavaBlock(const LavaBlock& other):Block(other)
{
    //copy ctor
}
/**
*   Operator= overloading
*   If object current and other are not equals, inherits of operator= overloading from Block
*   @param other : a reference constant BlockIron
*/
LavaBlock& LavaBlock::operator=(const LavaBlock& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
