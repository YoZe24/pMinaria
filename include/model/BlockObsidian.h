#ifndef BLOCKOBSIDIAN_H
#define BLOCKOBSIDIAN_H

#include "model/Block.h"

class BlockObsidian : public Block
{
    public:
        BlockObsidian(std::vector<float> s);
        virtual ~BlockObsidian();
        BlockObsidian(const BlockObsidian& other);
        BlockObsidian& operator=(const BlockObsidian&);
    protected:

    private:
};

#endif // BLOCKOBSIDIAN_H
