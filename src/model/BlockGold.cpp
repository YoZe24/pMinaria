#include "model/BlockGold.h"
using namespace std;

BlockGold::BlockGold(vector<float> s):Block(s,4.0,EnumBlock::GOLD)
{
    //ctor
}

BlockGold::~BlockGold()
{
    //dtor
}

BlockGold::BlockGold(const BlockGold& other):Block(other)
{
    //copy ctor
}

BlockGold& BlockGold::operator=(const BlockGold& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
