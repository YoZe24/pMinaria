#include "view/TileMap.h"
#include "iostream"
#include <cmath>
using namespace sf;
using namespace std;

/**
*   Default constructor
*/
TileMap::TileMap()
{
    //ctor
}

/**
*   Main constructor
*
*   @param width : Tilemap's width
*   @param height : Tilemap's height
*   @param tileSize : Tile's size
*   @param sW : Screen's width
*   @param sH : Screen's height
*/
TileMap::TileMap(int width,int height,int tileSize,int sW,int sH):width(width),height(height),tileSize(tileSize),screenW(sW),screenH(sH)
{
    nbBlockMined = 0;
}

/**
*   Destructor
*/
TileMap::~TileMap()
{
    tiles.clear();
}

/**
*   Copy constructor
*/
TileMap::TileMap(const TileMap& other):
width(other.width),height(other.height),tileSize(other.tileSize),tiles(other.tiles),screenW(other.screenW),screenH(other.screenH),nbBlockMined(other.nbBlockMined)
{
    //copy ctor
}

/**
*   Operator= to compare 2 tiles
*/
TileMap& TileMap::operator=(const TileMap& other){
    if(this != &other){
        this->width = other.width;
        this->height = other.height;
        this->tileSize = other.tileSize;
        this->tiles = other.tiles;
        this->screenW = other.screenW;
        this->screenH = other.screenH;
        this->nbBlockMined = other.nbBlockMined;
        this->time = other.time;
    }
    return *this;
}

/**
*   Load function to set the tile map
*
*   @param width : Tilemap's width
*   @param height : Tilemap's height
*   @param tileSize : Tile's size
*   @param sW : Screen's width
*   @param sH : Screen's height
*/
void TileMap::load(int width,int height,int tileSize,int sW,int sH){
    this->width = width;
    this->height = height;
    this->tileSize = tileSize;
    this->screenW = sW;
    this->screenH = sH;
}

/***/
map<int,Tile>::iterator TileMap::getItStart(int pos){
    int start = pos - (width * 3) - nbBlockMined < 0 ? 0 : pos - (width * 3) - nbBlockMined;
    map<int,Tile>::iterator it = tiles.begin();
    advance(it,start);
    return it;
}
/***/
map<int,Tile>::iterator TileMap::getItFinish(int pos){
    int finish = pos + width * 3 > (width * height)-3 ? (width * height)-3 : pos+width*3;
    map<int,Tile>::iterator it = tiles.begin();
    advance(it,finish);
    return it;
}

/***/
void TileMap::draw(RenderWindow& window,float dt,sf::Vector2f vPos){
    int pos = (vPos.x/tileSize) + (vPos.y/tileSize) * width;
    int nbBlocH = (width * ((screenH/tileSize)+3))/2;

    start = pos - nbBlocH - nbBlockMined < 0 ? 0 : pos - nbBlocH - nbBlockMined;
    limit = pos + nbBlocH > tiles.size() ? tiles.size() : pos+nbBlocH;

    time = dt;
    map<int,Tile>::iterator it = tiles.begin(), itFinish = tiles.begin();
    advance(it,start);
    advance(itFinish,limit);

    for(auto i = it ; i != itFinish;  i++){
        if(i->second.getBlock().getType() != EnumBlock::VOID)
            i->second.draw(window,dt);
    }
}

/**
*
*   Adding function for the map
*
*   @param t : Tile to add at the map
*   @param pos : The position where to add the tile into the map
*
*   @return value : Return true
*/
bool TileMap::add(const Tile& t,int pos){
    tiles.insert(make_pair(pos,t));
    return true;
}

/**
*
*   Delete function from the map
*
*   We remove the tile from the map and we added tile removed to the tilesDeleted map.
*
*   @param pos : Tile's position in the map
*
*   @return eb : Return the block's type
*/
EnumBlock TileMap::deleteTileAt(int pos){
    EnumBlock eb = tiles[pos].getBlock().getType();
    tilesDeleted.push_back(pos);
    tiles.erase(tiles.find(pos));
    nbBlockMined++;
    return eb;
}

/**
*
*   Delete function from the map
*
*   We use x,y to get the position of the tile in the map.
*
*
*/
EnumBlock TileMap::deleteTileAt(float x,float y,float power){
    int pos = getPos(x,y);

    map<int,Tile>::iterator itFinish = getItFinish(pos);
    for(auto i = getItStart(pos) ; i != itFinish;i++){

        int posX = i->second.getX() / tileSize;
        int posY = i->second.getY() / tileSize;

        if( x >= posX * tileSize && x <= (posX+1) *tileSize && y >= posY * tileSize && y <= (posY+1) * tileSize){

            i->second.updateTime(time);
            if(i->second.getTime()/1000 >= i->second.getDuration()/power){
                    EnumBlock eb = i->second.getBlock().getType();
                    tilesDeleted.push_back(i->first);
                    tiles.erase(tiles.find(i->first));
                    nbBlockMined++;
                    return eb;
            }
            return EnumBlock::VOID;
        }
    }
    return EnumBlock::VOID;

}

/**
*   Test function to find if the tile at position pos is well removed
*
*   @param pos : Tile's position
*
*   @return value : Return if the tile is removed from the map
*/
bool TileMap::isDeleted(int pos){
    return find(tilesDeleted.begin(),tilesDeleted.end(),pos) != tilesDeleted.end();
}

Tile& TileMap::getTileAt(int pos){
    return tiles[pos];
}

EnumBlock TileMap::getEnumBlockAt(int pos){
    if(isDeleted(pos))
        return EnumBlock::VOID;
    return getTileAt(pos).getBlock().getType();
}

EnumBlock TileMap::getEnumBlockAt(int x,int y){
    return getEnumBlockAt(getPos(x,y));
}

void TileMap::printTiles()const{
    for(auto& i:tiles){
        if(i.first == 10) break;
        cout << i.first << " = " << i.second.str() << endl;
    }
}

int TileMap::getPos(int x,int y){
    return floor(x/tileSize) + floor(y/tileSize) * width;
}

