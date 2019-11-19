#include "model/BlockDiamond.h"
using namespace std;

BlockDiamond::BlockDiamond(vector<float> s):Block(s,6.0,EnumBlock::DIAMOND)
{
    //ctor
}

BlockDiamond::~BlockDiamond()
{
    //dtor
}

BlockDiamond::BlockDiamond(const BlockDiamond& other):Block(other)
{
    //copy ctor
}

BlockDiamond& BlockDiamond::operator=(const BlockDiamond& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
