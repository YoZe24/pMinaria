#ifndef TILEMAP_H
#define TILEMAP_H

#include <view/Tile.h>
#include <SFML/Graphics.hpp>
#include <deque>
#include <map>
#include <SFML/Audio.hpp>

class TileMap
{
    public:
        TileMap();
        TileMap(int width,int height,int tileSize,int sW,int sH);
        virtual ~TileMap();
        TileMap(const TileMap& other);
        TileMap& operator=(const TileMap& other);

        void load(int,int,int,int,int);

        std::map<int,Tile>* getTiles(){return &tiles;}
        std::map<int,Tile>::iterator getItStart(int pos);
        std::map<int,Tile>::iterator getItFinish(int pos);
        int getWidth(){return width;}
        int getHeight(){return height;}
        int getTileSize(){return tileSize;}
        int getNbBlockMined()const{return nbBlockMined;}


        void setNbBlockMined(int nb){nbBlockMined = nb;}
        void printTiles()const;

        void draw(sf::RenderWindow& window,float dt,sf::Vector2f v);
        bool add(const Tile& t,int pos);
        EnumBlock deleteTileAt(float x, float y,float power);
        Tile& getTileAt(int pos);
        EnumBlock getEnumBlockAt(int pos);
        EnumBlock getEnumBlockAt(int x,int y);
        int getPos(int x,int y);
        bool isDeleted(int pos);
    protected:

    private:
        std::map<int,Tile> tiles;
        std::deque<int> tilesDeleted;
        int tileSize,nbBlockMined;
        int width,screenW;
        int height,screenH;
        int start,limit;
        float timer,time;
        sf::SoundBuffer sb;
        sf::Sound soundPop;

};

#endif // TILEMAP_H
