#include "BlockObsidian.h"
using namespace std;
BlockObsidian::BlockObsidian(vector<float> s):Block(s,13,EnumBlock::OBSIDIAN){}

/**
*   Default Constructor
*/

BlockObsidian::~BlockObsidian()
{
    //dtor
}
/**
*   Default Copy Constructor
*   @param other : a reference constant of BlockObsidian
*/
BlockObsidian::BlockObsidian(const BlockObsidian& other)
{
    //copy ctor
}

BlockObsidian& BlockObsidian::operator=(const BlockObsidian& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
