#include "model/BlockDiamond.h"
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
BlockDiamond::BlockDiamond(vector<float> s):Block(s,6.0,EnumBlock::DIAMOND)
{
    //ctor
}
/**
*   Default Constructor
*/
BlockDiamond::BlockDiamond(){}

/**
*   Destructor
*   Not Implemented
*/
BlockDiamond::~BlockDiamond()
{
    //dtor
}
/**
*   Copy constructor
*   Inherits of copy constructor from Block
*   @param other : a reference constant BlockDiamond
*/
BlockDiamond::BlockDiamond(const BlockDiamond& other):Block(other)
{
    //copy ctor
}
/**
*   Operator= overloading
*   If object current and other are not equals, inherits of operator= overloading from Block
*   @param other : a reference constant BlockDiamond
*/
BlockDiamond& BlockDiamond::operator=(const BlockDiamond& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
