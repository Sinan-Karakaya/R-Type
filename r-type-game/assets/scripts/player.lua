-- Fill your copyright notice in copyrightNotice.txt

-- r-type - starSpawner.lua
-- Created by 
-- Thu Jan 11 10:33:56 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    playerTable[e] = {}
    playerTable[e].upgradeId = -1
    playerTable[e].upgrade = "none"
end

-- @brief This function will be called when the entity is destroyed
-- @param e The entity that is being destroyed
function onDestroy(e)

end

-----------------------------------------------------------------------------------
-- Update functions
-- These functions will be called every frame
-----------------------------------------------------------------------------------

-- @brief This function will be called every frame
-- @param e The entity that is being updated
function update(e)
    local transform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeScript(e)
    local rigidBody = getComponentRigidBody(e)

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

    if playerTable[e].upgrade ~= "none" then
        local transformUpgrade = getComponentTransform(playerTable[e].upgradeId)
        transformUpgrade.position.x = transform.position.x
        transformUpgrade.position.y = transform.position.y
    end

    ---- handle shooting ----
    if getInput(e, "fire") and timeElapsed > 0.33 then
        print("fire")
        -- fire with upgrade
        if playerTable[e].upgrade == "Upgrade1" then
            eBullet = addPrefab("bullet")
            local bulletTransform = getComponentTransform(eBullet)
            local transform = getComponentTransform(e)
            bulletTransform.position.x = transform.position.x + drawable.floatRect.width * transform.scale.x
            bulletTransform.position.y = transform.position.y - (drawable.floatRect.height * transform.scale.y) / 2
            eBullet = addPrefab("bullet")
            local bulletTransform = getComponentTransform(eBullet)
            local transform = getComponentTransform(e)
            bulletTransform.position.x = transform.position.x + drawable.floatRect.width * transform.scale.x
            bulletTransform.position.y = transform.position.y + (drawable.floatRect.height * transform.scale.y) / 2
        end
        eBullet = addPrefab("bullet")
        local bulletTransform = getComponentTransform(eBullet)
        local transform = getComponentTransform(e)
        bulletTransform.position.x = transform.position.x + drawable.floatRect.width * transform.scale.x
        bulletTransform.position.y = transform.position.y
        -- networkSendInputToServer("fire")
        -- playSound(e, "pewpew")
        restartClockScript(e)
    end
end

-- @brief This function will be called every frame on the server
-- @param e The entity that is being updated
function updateServer(e)

end

-----------------------------------------------------------------------------------
-- Other functions
-- These functions will be called when certain events happen
-----------------------------------------------------------------------------------

-- @brief This function will be called when the entity collides with another entity
-- @param e The entity that is being updated
-- @param other The entity that was collided with
function onCollision(e, other)
    local tagOther = getComponentTag(other)

    if tagOther == "enemy" then
        destroyEntity(other)
    end
    if tagOther == "Upgrade1" then
        playerTable[e].upgrade = "Upgrade1"
        playerTable[e].upgradeId = other
    end
end

-- @brief This function will be called when a triggerEvent is called
-- @param event The event that was triggered
function onEvent(event)

end

-- @brief This function will be called when a client presses a key (and it's send from client)
-- with networkSendInputToServer function.
-- @param e The entity that is being updated
-- @param input The input that was pressed
function onClientInput(e, input)
    local drawable = getDrawable(e)
    if input == "fire" then
        eBullet = addPrefab("bullet")
        local bulletTransform = getComponentTransform(eBullet)
        local transform = getComponentTransform(e)
        bulletTransform.position.x = transform.position.x + drawable.floatRect.width * transform.scale.x
        bulletTransform.position.y = transform.position.y
    end
end
