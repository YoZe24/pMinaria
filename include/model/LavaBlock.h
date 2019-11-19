#ifndef LAVABLOCK_H
#define LAVABLOCK_H

#include "model/Block.h"

class LavaBlock : public Block
{
    public:
        LavaBlock();
        LavaBlock(std::vector<float> s);
        virtual ~LavaBlock();
        LavaBlock(const LavaBlock& other);
        LavaBlock& operator=(const LavaBlock&);
    protected:

    private:
};

#endif // LAVABLOCK_H
