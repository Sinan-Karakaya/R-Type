function onStart(e)

end

function onDestroy(e)

end

-- client side --
function update(e)
    local bulletTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()

    -- ---- handle movement ----
    bulletTransform.position.x = bulletTransform.position.x + 10
    if bulletTransform.position.x >= cameraSize.x then
        destroyEntity(e)
    end
end

-- server side --
function updateServer(e)

    local bulletTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()

    ---- handle movement ----
    bulletTransform.position.x = bulletTransform.position.x - 10
    if bulletTransform.position.x <= 0 then
        destroyEntity(e)
    end
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    if tagOther == "player" then
        destroyEntity(e)
        destroyEntity(other)
    end
end