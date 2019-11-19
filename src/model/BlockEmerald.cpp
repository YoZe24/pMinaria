#include "model/BlockEmerald.h"

BlockEmerald::BlockEmerald(std::vector<float> s):Block(s,12.0,EnumBlock::EMERALD)
{
    //ctor
}

BlockEmerald::~BlockEmerald()
{
    //dtor
}

BlockEmerald::BlockEmerald(const BlockEmerald& other):Block(other)
{
    //copy ctor
}

BlockEmerald& BlockEmerald::operator=(const BlockEmerald& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
