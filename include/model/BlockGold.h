#ifndef BLOCKGOLD_H
#define BLOCKGOLD_H

#include "model/Block.h"

class BlockGold : public Block
{
    public:
        BlockGold(std::vector<float> s);
        virtual ~BlockGold();
        BlockGold(const BlockGold& other);
        BlockGold& operator=(const BlockGold&);
    protected:

    private:
};

#endif // BLOCKGOLD_H
