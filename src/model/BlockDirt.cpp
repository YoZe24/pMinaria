#include "model/BlockDirt.h"

using namespace std;

BlockDirt::BlockDirt(vector<float> s):Block(s,0.30,EnumBlock::DIRT)
{
}

BlockDirt::~BlockDirt()
{
    //dtor
}

BlockDirt::BlockDirt(const BlockDirt& other):Block(other)
{
    //copy ctor
}

BlockDirt& BlockDirt::operator=(const BlockDirt& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
