#ifndef BLOCKSTONE_H
#define BLOCKSTONE_H

#include "model/Block.h"

class BlockStone : public Block
{
    public:
        BlockStone(std::vector<float> s);
        virtual ~BlockStone();
        BlockStone(const BlockStone& other);
        BlockStone& operator=(const BlockStone& other);
    protected:

    private:
};

#endif // BLOCKSTONE_H
