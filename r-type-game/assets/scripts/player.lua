enemyTable = {}

function onStart(e)
    playerTable[e] = {}
    -- TODO: implement this variables
    -- playerTable[e].health = 100
    -- playerTable[e].score = 0
    playerTable[e].upgradeId = -1
    playerTable[e].upgrade = "none"
    print("ONSTARTPLAYER........")
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
    -- print("debug -> " .. drawable.floatRect.left)
    -- print("debug -> " .. drawable.currentFrame)
    -- if drawable.currentFrame >= drawable.frameCount then
    --     drawable.currentFrame = 0;
    --     drawable.floatRect.left = drawable.startPosition;
    -- else
    --     drawable.currentFrame = drawable.currentFrame + 1;
    --     drawable.floatRect.left = drawable.floatRect.left + drawable.leftDecal;
    -- end

    -- drawable.currentFrame = 1

    ---- handle movement ----
    if getInput(e, "moveUp") then
        -- drawable.currentFrame = 1
        -- drawable.floatRect.left = drawable.leftDecal * drawable.currentFrame
        -- print("debug -> " .. drawable.floatRect.left)
        if (transform.position.y - rigidBody.velocity.y) > 0 then
            transform.position.y = transform.position.y - rigidBody.velocity.y
            networkSendPosToServer(e)
        end
    end
    if getInput(e, "moveDown") then
        -- drawable.currentFrame = 2
        -- drawable.floatRect.left = drawable.leftDecal * drawable.currentFrame
        -- print("debug -> " .. drawable.floatRect.left)
        if transform.position.y + rigidBody.velocity.y < cameraSize.y then
            transform.position.y = transform.position.y + rigidBody.velocity.y
            networkSendPosToServer(e)
        end
    end
    if getInput(e, "moveLeft") then
        -- drawable.currentFrame = 3
        -- drawable.floatRect.left = drawable.leftDecal * drawable.currentFrame
        -- print("debug -> " .. drawable.floatRect.left)
        if transform.position.x - rigidBody.velocity.x > 0 then
            transform.position.x = transform.position.x - rigidBody.velocity.x
            networkSendPosToServer(e)
        end
    end
    if getInput(e, "moveRight") then
        -- drawable.currentFrame = 4
        -- drawable.floatRect.left = drawable.leftDecal * drawable.currentFrame
        -- print("debug -> " .. drawable.floatRect.left)
        if transform.position.x + rigidBody.velocity.x < cameraSize.x then
            transform.position.x = transform.position.x + rigidBody.velocity.x
            networkSendPosToServer(e)
        end
    end

    if timeElapsed > 2 then
        restartClockScript(e)
        print("debug -> " .. playerTable[e].upgrade)
        print("debug -> " .. playerTable[e].upgradeId)
    end

    if playerTable[e].upgrade ~= "none" then
        print("debug -> " .. playerTable[e].upgrade)
        local transformUpgrade = getComponentTransform(playerTable[e].upgradeId)
        transformUpgrade.position.x = transform.position.x
        transformUpgrade.position.y = transform.position.y
    end

    ---- handle shooting ----
    if getInput(e, "fire") and timeElapsed > 0.33 then
        -- fire with upgrade
        if playerTable[e].upgrade == "Upgrade1" then
            eBullet = addPrefab("bullet")
            local bulletTransform = getComponentTransform(eBullet)
            local transform = getComponentTransform(e)
            bulletTransform.position.x = transform.position.x
            bulletTransform.position.y = transform.position.y - 0.5
            eBullet = addPrefab("bullet")
            local bulletTransform = getComponentTransform(eBullet)
            local transform = getComponentTransform(e)
            bulletTransform.position.x = transform.position.x
            bulletTransform.position.y = transform.position.y + 0.5
        end
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
    if tagOther == "Upgrade1" then
        playerTable[e].upgrade = "Upgrade1"
        playerTable[e].upgradeId = other
        -- debug --
        print("changed value -> " .. playerTable[e].upgrade)
        print("changed value -> " .. playerTable[e].upgradeId)
    end
end

function onEvent(e, input)
end