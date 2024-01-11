function onStart(e)
    playerTable[e] = {}
end

function onDestroy(e)

end

function update(e)
    local transform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeScript(e)
    local rigidBody = getComponentRigidBody(e)

    ---- handle animation ----
    -- local seconds = getElapsedTimeAnimation(e)
    -- if seconds > drawable.frameDuration and drawable.isAnimated then
    --     restartClockAnimation(e)
    --     drawable.currentFrame = drawable.currentFrame + 1
    --     drawable.floatRect.left = drawable.floatRect.left + drawable.leftDecal
    --     if drawable.currentFrame > drawable.frameCount then
    --         drawable.currentFrame = 0
    --     end
    -- end

    ---- handle movement ----
    if getInput(e, "moveUp") then
        if (transform.position.y - rigidBody.velocity.y) > 0 then
            transform.position.y = transform.position.y - rigidBody.velocity.y
            networkSendPosToServer(e)
        end
    end
    if getInput(e, "moveDown") then
        if transform.position.y + rigidBody.velocity.y < cameraSize.y then
            transform.position.y = transform.position.y + rigidBody.velocity.y
            networkSendPosToServer(e)
        end
    end
    if getInput(e, "moveLeft") then
        if transform.position.x - rigidBody.velocity.x > 0 then
            transform.position.x = transform.position.x - rigidBody.velocity.x
            networkSendPosToServer(e)
        end
    end
    if getInput(e, "moveRight") then
        if transform.position.x + rigidBody.velocity.x < cameraSize.x then
            transform.position.x = transform.position.x + rigidBody.velocity.x
            networkSendPosToServer(e)
        end
    end

    ---- handle shooting ----
    if getInput(e, "fire") and timeElapsed > 1 then
        networkSendInputToServer("fire")
        playSound(e, "pewpew")
        restartClockScript(e)
    end
end

function updateServer(e)

end

function onClientInput(e, input)
    if input == "fire" then
        eBullet = addPrefab("bullet")
        local bulletTransform = getComponentTransform(eBullet)
        local transform = getComponentTransform(e)
        bulletTransform.position.x = transform.position.x
        bulletTransform.position.y = transform.position.y
    end
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    if tagOther == "enemy" then
        destroyEntity(other)
    end
end
