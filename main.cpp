#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <ctime>
#include "view/AnimationManager.h"
#include "model/Entity.h"
#include "model/Player.h"
#include "view/EntityComponent.h"
#include "view/PlayerComponent.h"
#include "view/TileMap.h"
#include "model/BlockDirt.h"
#include "model/BlockStone.h"
#include "model/BlockIron.h"
#include "model/BlockGold.h"
#include "model/BlockDiamond.h"
#include "model/BlockEmerald.h"
#include "model/LavaBlock.h"
#include "model/Pickaxe.h"
#include "model/GestionUser.h"
#include "gui/InterfaceAdmin.h"
#include "gui/InterfaceConAdmin.h"
#include "gui/InterfaceCon.h"
#include "gui/InterfaceTableScore.h"
#include <map>
#include <cmath>
#include "view/EnemyComponent.h"
#include "gamestate/Game.h"
#include "gamestate/GameStateGame.h"
#include "view/Timer.h"
#include "gui/MainMenu.h"
#include "gui/OptionMenu.h"

using namespace sf;
using namespace std;

const int tileMap_height = 400,tileMap_width = 50,tile_size = 32,h_miner = 24,w_miner = 16;
const int screen_h = 600,screen_w = 1200;
int level[tileMap_width * tileMap_height];
TileMap tileMap(tileMap_width,tileMap_height,tile_size,screen_w,screen_h);


int main()
{
//    GestionUser* gestion = GestionUser::getInstance();
//    gestion->readFromFile("User.txt");
//    cout<<gestion->str();

    srand(time(NULL));
    Game game;
    game.pushState(new GameStateGame(&game));
    game.gameLoop();
//
//    RenderWindow window(VideoMode(1200, 700), "The Game!");
//
//    Texture textureBTN,textureBG, textureTXT;
//    textureBTN.loadFromFile("btnSkin.png");
//    textureBG.loadFromFile("background.png");
//    textureTXT.loadFromFile("inputText.png");
//    Font font;
//    font.loadFromFile("gameFont.ttf");
//    Texture textureTitle;
//    textureTitle.loadFromFile("title.png");
//
//    MainMenu menu = MainMenu(textureTitle,textureBG,textureBTN,font,window);
//    InterfaceCon interCon = InterfaceCon(textureTitle,textureBG,textureBTN,textureTXT,font,window);
//    InterfaceAdmin interAdmin = InterfaceAdmin(textureTitle,textureBG,textureBTN,textureTXT,font,window);
//    InterfaceConAdmin interConAdmin = InterfaceConAdmin(textureTitle,textureBG,textureBTN,textureTXT,font,window);
//    InterfaceTableScore interTable = InterfaceTableScore(textureTitle,textureBG,textureBTN,textureTXT,font,window);
//    //MainMenu menu = MainMenu(textureTitle,textureBG,textureBTN,font,window);
//    OptionMenu optionMenu = OptionMenu(textureTitle,textureBG,textureBTN,font,window);
//
//    while(window.isOpen())
//    {
//
//		Event event;
//		while (window.pollEvent(event))
//		{
//
//            //OK
//		    //interAdmin.handleInput(window);
//
//		    //OK
//		    //interCon.handleInput(window, event);
//
//		    //OK
//		    //interConAdmin.handleInput(window,event);
//
//			if (event.type == Event::Closed)
//				window.close();
//				gestion->writeFromFile("User.txt");
//            if(event.type == Event::Resized){
//
//            }
//		}
//
//
//
//		window.clear();
//
//        //interAdmin.draw(window);
//        //interCon.draw(window);
//        //interConAdmin.draw(window);
//		//optionMenu.handleInput(window);
//		optionMenu.handleInput(window);
//		//menu.handleInput(window);
//		window.display();
//    }

    return 0;
}
