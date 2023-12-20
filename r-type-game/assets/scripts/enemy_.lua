function update(e)

    local enemyTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()

    if enemyTransform.position.y >= cameraSize.y then
        velocity = -2
    elseif enemyTransform.position.y <= 0 then
        velocity = 2
    end

    ---- handle movement ----
    enemyTransform.position.y = enemyTransform.position.y + velocity
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    print(tagOther)
    if tagOther == "bullet" then
        destroyEntity(other)
    end
end