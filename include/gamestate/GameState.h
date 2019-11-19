#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState
{
    public:
        GameState();
        virtual ~GameState();
        GameState(const GameState& other);

        virtual void draw (const float dt) = 0;
        virtual void update(const float dt)= 0;
        virtual void handleInput()=0;
    protected:

    private:
};

#endif // GAMESTATE_H
