function onStart(e)
    bulletEnemyTable = {}
    bulletEnemyTable.damage = 25
end

function onDestroy(e)
end

function update(e)
end

function updateServer(e)

    local bulletTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local rigidBody = getComponentRigidBody(e)

    ---- handle movement ----
    bulletTransform.position.x = bulletTransform.position.x - rigidBody.velocity.x
    if bulletTransform.position.x <= 0 then
        destroyEntity(e)
    end
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    if tagOther == "Player" then
        destroyEntity(other)
        destroyEntity(e)
    end
    if tagOther == "bullet" then
        destroyEntity(e)
        destroyEntity(other)
    end
end