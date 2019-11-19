#include "model/BlockIron.h"
using namespace std;

BlockIron::BlockIron(vector<float> s):Block(s,3.0,EnumBlock::IRON)
{
}

BlockIron::~BlockIron()
{
    //dtor
}

BlockIron::BlockIron(const BlockIron& other):Block(other)
{
    //copy ctor
}

BlockIron& BlockIron::operator=(const BlockIron& other){
    if(this != &other){
        Block::operator=(other);
    }
    return *this;
}
