#include "model/BlockIron.h"
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
BlockIron::BlockIron(vector<float> s):Block(s,3.0,EnumBlock::IRON)
{
}
/**
*   Default Constructor
*/
BlockIron::BlockIron(){}
/**
*   Destructor
*   Not Implemented
*/
BlockIron::~BlockIron()
{
    //dtor
}
/**
*   Copy constructor
*   Inherits of copy constructor from Block
*   @param other : a reference constant BlockIron
*/
BlockIron::BlockIron(const BlockIron& other):Block(other)
{
    //copy ctor
}
/**
*   Operator= overloading
*   If object current and other are not equals, inherits of operator= overloading from Block
*   @param other : a reference constant BlockIron
*/
BlockIron& BlockIron::operator=(const BlockIron& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
