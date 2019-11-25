#ifndef PICKAXE_H
#define PICKAXE_H

#include "model/Block.h"
#include <iostream>

enum EnumPickaxe{
    PX_WOOD,PX_STONE,PX_IRON,PX_GOLD,PX_DIAMOND,PX_EMERALD
};

const int nbOres = 13;

class PX_Strategy;

class Pickaxe
{
    public:
        Pickaxe();
        virtual ~Pickaxe();
        Pickaxe(const Pickaxe& other);
        bool isBreakable(EnumBlock b);
        EnumPickaxe getType()const;
        float getPower()const;
        PX_Strategy* getNextStrategy(EnumPickaxe ep);
        PX_Strategy* getSrategy(){return px_s;}


        void setPXStrategy(PX_Strategy* px_s);
        void setPXStrategy();
    protected:

    private:
//        std::vector<int> breakables;
        PX_Strategy* px_s;
};

class PX_Strategy
{
    public:
        PX_Strategy(float power,int nbOresCraft,EnumPickaxe ep);
        PX_Strategy(const PX_Strategy&);
        virtual bool isBreakable(EnumBlock typeBlock) = 0;
        virtual PX_Strategy& operator=(const PX_Strategy&);

        float getPower()const{return power;}
        int getNbOresCraft()const{return nbOresCraft;}
        EnumPickaxe getType()const;

        void setPower(float Power){power = Power;}
        void setNbOresCraft(int nbO){nbOresCraft = nbO;}
    private:
        float power;
        int nbOresCraft;
        EnumPickaxe type;
};

class PX_Strategy_Wood : public PX_Strategy
{
    public:
        PX_Strategy_Wood(float power = 1.0,int nbOresCraft = 7,EnumPickaxe ep = EnumPickaxe::PX_WOOD);
        virtual bool isBreakable(EnumBlock typeBlock);
        virtual PX_Strategy_Wood& operator=(const PX_Strategy_Wood&);
};

class PX_Strategy_Stone : public PX_Strategy
{
    public:
        PX_Strategy_Stone(float power = 1.7,int nbOresCraft = 6,EnumPickaxe ep = EnumPickaxe::PX_STONE);
        virtual bool isBreakable(EnumBlock typeBlock);
        virtual PX_Strategy_Stone& operator=(const PX_Strategy_Stone&);
};

class PX_Strategy_Iron : public PX_Strategy
{
    public:
        PX_Strategy_Iron(float power = 2.5,int nbOresCraft = 5, EnumPickaxe ep = EnumPickaxe::PX_IRON);
        virtual bool isBreakable(EnumBlock typeBlock);
        virtual PX_Strategy_Iron& operator=(const PX_Strategy_Iron&);
};

class PX_Strategy_Gold : public PX_Strategy
{
    public:
        PX_Strategy_Gold(float power = 3.3,int nbOresCraft = 5, EnumPickaxe ep = EnumPickaxe::PX_GOLD);
        virtual bool isBreakable(EnumBlock typeBlock);
        virtual PX_Strategy_Gold& operator=(const PX_Strategy_Gold&);
};

class PX_Strategy_Diamond : public PX_Strategy
{
    public:
        PX_Strategy_Diamond(float power = 5.0,int nbOresCraft = 5, EnumPickaxe ep = EnumPickaxe::PX_DIAMOND);
        virtual bool isBreakable(EnumBlock typeBlock);
        virtual PX_Strategy_Diamond& operator=(const PX_Strategy_Diamond&);
};

class PX_Strategy_Emerald : public PX_Strategy
{
    public:
        PX_Strategy_Emerald(float power = 9.0,int nbOresCraft = 5, EnumPickaxe ep = EnumPickaxe::PX_EMERALD);
        virtual bool isBreakable(EnumBlock typeBlock);
        virtual PX_Strategy_Emerald& operator=(const PX_Strategy_Emerald&);

};
#endif // PICKAXE_H
