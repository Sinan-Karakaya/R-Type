function update(e)

    local bulletTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()

    ---- handle movement ----
    bulletTransform.position.x = bulletTransform.position.x + 2
    if bulletTransform.position.x >= cameraSize.x then
        destroyEntity(e)
    end
end
