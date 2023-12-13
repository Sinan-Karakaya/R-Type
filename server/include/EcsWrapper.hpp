#pragma once

#include "RType.hpp"

namespace RType
{
    class EcsWrapper
    {
    public:
        EcsWrapper(RType::Runtime::ECS::Registry &registry);
        ~EcsWrapper();
        void createEntity(int entityId, /*??? EntityType,*/ int posX, int posY); // RFC: 4.7 PacketEntitySpawn
        void deleteEntity(int entityId);
        void moveEntity(int entityId, int posX, int posY, int dirX, int dirY);
        void launchBullet(/*??? BulletType,*/ int posX, int posY, int dirX,
                          int dirY); // RFC: 4.11 PacketPlayerLaunchBullet
        void playerDie(int entityId);
        void playerSpawn(int entityId, int posX, int posY /*, color*/); // RFC: 4.5 PacketPlayerSpawn

    private:
        RType::Runtime::ECS::Registry &m_registry;
    };
}; // namespace RType
