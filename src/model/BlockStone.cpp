#include "model/BlockStone.h"
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
BlockStone::BlockStone(vector<float> s):Block(s,2.00,EnumBlock::STONE)
{

}
/**
*   Default Constructor
*/
BlockStone::BlockStone(){}
/**
*   Destructor
*   Not Implemented
*/
BlockStone::~BlockStone()
{
    //dtor
}
/**
*   Copy constructor
*   Inherits of copy constructor from Block
*   @param other : a reference constant BlockStone
*/
BlockStone::BlockStone(const BlockStone& other):Block(other)
{
    //copy ctor
}
/**
*   Operator= overloading
*   If object current and other are not equals, inherits of operator= overloading from Block
*   @param other : a reference constant BlockStone
*/
BlockStone& BlockStone::operator=(const BlockStone& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
