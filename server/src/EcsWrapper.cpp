#include "EcsWrapper.hpp"

void RType::EcsWrapper::deleteEntity(int entityId)
{
    m_registry.DestroyEntity(entityId);
}

void RType::EcsWrapper::moveEntity(int entityId, int posX, int posY, int dirX, int dirY)
{
    auto &entity = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entityId);
    entity.position.x = posX;
    entity.position.y = posY;
    entity.rotation.x = dirX;
    entity.rotation.y = dirY;
}

void RType::EcsWrapper::hitEntity(int entityId)
{
}

void RType::EcsWrapper::playerDie(int entityId)
{
    m_registry.DestroyEntity(entityId);
}

void RType::EcsWrapper::playerHitEntity(int entityId, int score)
{
}
