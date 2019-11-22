#include "Game.h"

using namespace std;
using namespace sf;

void Game::pushState(GameState* state)
{
    this->states.push(state);

    return;
}

void Game::popState()
{
    delete this->states.top();
    this->states.pop();

    return;
}

void Game::changeState(GameState* state)
{
    if(!this->states.empty())
        popState();
    pushState(state);

    return;
}

GameState* Game::peekState()
{
    if(this->states.empty()) return nullptr;
    return this->states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(this->window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time/500;
		if (time > 40) time = 40;

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(time);
        this->window.clear(sf::Color::Black);
        peekState()->draw(time);
        this->window.display();

    }
}

Game::Game()
{
//    this->loadTextures();
//    this->loadTiles();

    this->window.create(sf::VideoMode(1200, 600), "Minaria");
    this->window.setFramerateLimit(60);

//    this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}
