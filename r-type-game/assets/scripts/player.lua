function update(e)
    local transform=getComponentTransform(e)
    local cameraSize = getCameraSize()

    -- local var = getElapsedTime(e)

    -- print("elapsed time: " .. var)

    ---- handle movement ----
    if getInput(e, "moveUp") then
        if (transform.position.y - 2) > 0 then
            transform.position.y = transform.position.y - 2
            sendPosToServer(e)
        end
    end
    if getInput(e, "moveDown") then
        if transform.position.y + 2 < cameraSize.y then
            transform.position.y = transform.position.y + 2
            sendPosToServer(e)
        end
    end
    if getInput(e, "moveLeft") then
        if transform.position.x - 2 > 0 then
            transform.position.x = transform.position.x - 2
            sendPosToServer(e)
        end
    end
    if getInput(e, "moveRight") then
        if transform.position.x + 2 < cameraSize.x then
            transform.position.x = transform.position.x + 2
            sendPosToServer(e)
        end
    end

    ---- handle shooting ----
    if getInput(e, "fire") then
        launchBullet(e)
    end
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    -- print(tagOther)
    if tagOther == "enemy" then
        destroyEntity(other)
    end
end
