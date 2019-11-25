#ifndef GAME_H
#define GAME_H

#include <stack>
#include <string>
#include <SFML/Graphics.hpp>
#include "gamestate/GameState.h"

class GameState;

class Game
{
    public:
        Game();
        virtual ~Game();
        Game(const Game& other);

        sf::RenderWindow window;

        void pushState(GameState* state);
        void popState();
        void changeState(GameState* state);
        GameState* peekState();

        void gameLoop();

        int TIME_TIMER = 2;
        float DURABILITY = 1.0;
    protected:

    private:
        std::stack<GameState*> states;
};

#endif // GAME_H
