#ifndef BLOCKIRON_H
#define BLOCKIRON_H

#include "model/Block.h"

class BlockIron : public Block
{
    public:
        BlockIron(std::vector<float> s);
        BlockIron();
        virtual ~BlockIron();
        BlockIron(const BlockIron& other);
        BlockIron& operator=(const BlockIron& other);

    protected:

    private:
};

#endif // BLOCKIRON_H
