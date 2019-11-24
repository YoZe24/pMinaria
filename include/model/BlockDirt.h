#ifndef BLOCKDIRT_H
#define BLOCKDIRT_H

#include "model/Block.h"

class BlockDirt : public Block
{
    public:
        BlockDirt(std::vector<float> s);
        BlockDirt();
        virtual ~BlockDirt();
        BlockDirt(const BlockDirt& other);
        BlockDirt& operator=(const BlockDirt& other);

    protected:

    private:

};

#endif // BLOCKDIRT_H
