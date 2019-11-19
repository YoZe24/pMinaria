#include "model/LavaBlock.h"

using namespace std;
LavaBlock::LavaBlock(vector<float> s):Block(s,10.0,EnumBlock::LAVA)
{
    //ctor
}

LavaBlock::~LavaBlock()
{
    //dtor
}

LavaBlock::LavaBlock(const LavaBlock& other):Block(other)
{
    //copy ctor
}

LavaBlock& LavaBlock::operator=(const LavaBlock& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
