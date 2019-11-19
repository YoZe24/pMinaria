#ifndef GAME_H
#define GAME_H


class Game
{
    public:
        Game();
        virtual ~Game();
        Game(const Game& other);

        void pushState(GameState* state);
        void popState();
        void changeState();
    protected:

    private:
        void loadTextures();
        void loadTiles();

};

#endif // GAME_H
