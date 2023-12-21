function update(e)

    local enemyTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local getComponentRigidBody = getComponentRigidBody(e)
    local drawable = getDrawable(e)

    if enemyTransform.position.y + (drawable.floatRect.height * enemyTransform.scale.y) / 2 >= cameraSize.y then
        getComponentRigidBody.velocity.y = getComponentRigidBody.velocity.y * -1
    elseif enemyTransform.position.y - (drawable.floatRect.height * enemyTransform.scale.y) / 2 <= 0 then
        getComponentRigidBody.velocity.y = getComponentRigidBody.velocity.y * -1
    end

    ---- handle movement ----
    enemyTransform.position.y = enemyTransform.position.y + getComponentRigidBody.velocity.y
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    if tagOther == "bullet" then
        destroyEntity(other)
    end
end