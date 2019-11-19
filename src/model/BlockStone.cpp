#include "model/BlockStone.h"
using namespace std;
BlockStone::BlockStone(vector<float> s):Block(s,2.00,EnumBlock::STONE)
{

}

BlockStone::~BlockStone()
{
    //dtor
}

BlockStone::BlockStone(const BlockStone& other):Block(other)
{
    //copy ctor
}

BlockStone& BlockStone::operator=(const BlockStone& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
