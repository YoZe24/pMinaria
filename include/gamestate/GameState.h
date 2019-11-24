#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gamestate/Game.h"
class Game;

class GameState
{
    public:
        Game* game;

        virtual void draw (const float dt) = 0;
        virtual void update(const float dt)= 0;
        virtual void handleInput()=0;
    protected:

    private:
};

#endif // GAMESTATE_H
