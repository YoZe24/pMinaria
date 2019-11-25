#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include "model/GestionUser.h"
#include "gamestate/Game.h"
#include "gamestate/GameStateMainMenu.h"
#include "SFML/Audio.hpp"

using namespace sf;
using namespace std;

int main()
{
    sf::Music music;
    if(!music.openFromFile("background_music.wav")){}
    music.play();
    music.setVolume(50);



    GestionUser* gestion = GestionUser::getInstance();
    gestion->readFromFile("User.txt");

    srand(time(NULL));
    Game game;
    game.pushState(new GameStateMainMenu(&game));
    game.gameLoop();

    return 0;
}
