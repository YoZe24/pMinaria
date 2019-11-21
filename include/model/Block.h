#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

enum EnumBlock {
    VOID = -1,DIRT, STONE, IRON, GOLD, DIAMOND,EMERALD,OBSIDIAN,LAVA
};


class Block
{
    public:
        Block();
        Block(std::vector<float> s,float d,EnumBlock t);
        virtual ~Block();
        Block(const Block& other);
        Block& operator=(const Block& other);
        std::string str() const;

        std::vector<float> getSpawn() {return spawn;}
        float getDuration() const{return duration;}
        EnumBlock getType() const{return type;}

    protected:

    private:
        float duration;
        std::vector<float> spawn;
        EnumBlock type;
};

#endif // BLOCK_H
