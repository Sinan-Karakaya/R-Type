function update(e)

end

function updateServer(e)
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
    enemyTransform.position.x = enemyTransform.position.x - getComponentRigidBody.velocity.x * 2

    if enemyTransform.position.x + (drawable.floatRect.width * enemyTransform.scale.x) <= 0 then
        destroyEntity(e)
    end
end

function onCollision(e, other)

end

function onEvent(e, input)
    print("Enemy received event: " .. input)
end