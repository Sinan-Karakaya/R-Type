#include "EcsWrapper.hpp"

RType::EcsWrapper::EcsWrapper(RType::Runtime::ECS::Registry &registry) : m_registry(registry) {}

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

void RType::EcsWrapper::playerDie(int entityId)
{
    m_registry.DestroyEntity(entityId);
}
