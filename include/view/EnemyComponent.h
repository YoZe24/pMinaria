#ifndef ENEMYCOMPONENT_H
#define ENEMYCOMPONENT_H

#include "model/Enemy.h"
#include "view/EntityComponent.h"

class EnemyComponent : public EntityComponent
{
    public:
        EnemyComponent(AnimationManager& a,AnimationManager& af,TileMap* tileMap,int x, int y,std::vector<float> s);
        virtual ~EnemyComponent();
        EnemyComponent(const EnemyComponent& other);
        EnemyComponent& operator=(const EnemyComponent&);

        void update(float time);
        void swapDir();
        std::vector<float> getSpawn();

        void Collision(int i);
    protected:

    private:
        bool flip;
};

#endif // ENEMYCOMPONENT_H
