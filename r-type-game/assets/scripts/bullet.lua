function onStart(e)

end

function onDestroy(e)

end

function update(e)
    -- local bulletTransform = getComponentTransform(e)
    -- local cameraSize = getCameraSize()

    -- ---- handle movement ----
    -- bulletTransform.position.x = bulletTransform.position.x + 10
    -- if bulletTransform.position.x >= cameraSize.x then
    --     destroyEntity(e)
    -- end
end

function updateServer(e)

    local bulletTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local rigidBody = getComponentRigidBody(e)

    ---- handle movement ----
    bulletTransform.position.x = bulletTransform.position.x + rigidBody.velocity.x
    if bulletTransform.position.x >= cameraSize.x then
        destroyEntity(e)
    end
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    if tagOther == "enemy" then
        destroyEntity(e)
        destroyEntity(other)
    end
end