#include "model/Block.h"

#include <sstream>

using namespace std;

Block::Block()
{

}

Block::Block(vector<float> s,float d,EnumBlock t):spawn(s),duration(d),type(t)
{

}

Block::~Block()
{
    //dtor
}

Block::Block(const Block& other):spawn(other.spawn),duration(other.duration),type(other.type)
{
    //copy ctor
}

Block& Block::operator=(const Block& other){
    if(this != &other){
        this->spawn = other.spawn;
        this->duration = other.duration;
        this->type = other.type;
    }
    return *this;
}

string Block::str() const{
    stringstream sstr;
    sstr << "spawn : {";
    for(float f:spawn)
        sstr << f << ",";
    sstr << "} duration : " << this->duration << ", type : " << type;
    return sstr.str();

}
