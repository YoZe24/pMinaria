#ifndef BLOCKDIAMOND_H
#define BLOCKDIAMOND_H
#include "model/Block.h"

class BlockDiamond : public Block
{
    public:
        BlockDiamond(std::vector<float> s);
        BlockDiamond();
        virtual ~BlockDiamond();
        BlockDiamond(const BlockDiamond& other);
        BlockDiamond& operator=(const BlockDiamond& );
    protected:

    private:
};

#endif // BLOCKDIAMOND_H
