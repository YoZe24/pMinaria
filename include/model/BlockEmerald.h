#ifndef BLOCKEMERALD_H
#define BLOCKEMERALD_H

#include "model/Block.h"

class BlockEmerald : public Block
{
    public:
        BlockEmerald(std::vector<float> s);
        BlockEmerald();
        virtual ~BlockEmerald();
        BlockEmerald(const BlockEmerald& other);
        BlockEmerald& operator=(const BlockEmerald& other);

    protected:

    private:
};

#endif // BLOCKEMERALD_H
