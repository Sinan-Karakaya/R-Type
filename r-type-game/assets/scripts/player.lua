-- Fill your copyright notice in copyrightNotice.txt

-- r-type - starSpawner.lua
-- Created by 
-- Thu Jan 11 10:33:56 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    playerTable[e] = {}
    playerTable[e].upgrade = {}
    playerTable[e].upgrade[1] = {}
    playerTable[e].upgrade[1].name = "none"
    playerTable[e].upgrade[1].id = -1
end

-- @brief This function will be called when the entity is destroyed
-- @param e The entity that is being destroyed
function onDestroy(e)
    print("Player is dead")
    local text = getEntityByTag("deadText")
    setText(text, "You are dead")
end

-----------------------------------------------------------------------------------
-- Update functions
-- These functions will be called every frame
-----------------------------------------------------------------------------------

-- @brief This function will be called every frame
-- @param e The entity that is being updated
function update(e, dt)
    local transform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeScript(e)
    local rigidBody = getComponentRigidBody(e)
    local drawable = getComponentDrawable(e)
    local yIsMoving = false

    ---- handle movement ----
    if getInput(e, "moveUp") then
        if (transform.position.y - rigidBody.velocity.y) > 0 then
            transform.position.y = transform.position.y - rigidBody.velocity.y
            drawable.floatRect.left = 133
            yIsMoving = true
            networkSendPosToServer(e)
        end
    end
    if getInput(e, "moveDown") then
        if transform.position.y + rigidBody.velocity.y < cameraSize.y then
            transform.position.y = transform.position.y + rigidBody.velocity.y
            drawable.floatRect.left = 0
            yIsMoving = true
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
    if not yIsMoving then
        drawable.floatRect.left = 67
    end

    -- move upgrade --
    for k, v in pairs(playerTable[e].upgrade) do
        if v.name == "Upgrade1" then
            local transformUpgrade = getComponentTransform(v.id)
            transformUpgrade.position.x = transform.position.x + drawable.floatRect.width * transform.scale.x
            transformUpgrade.position.y = transform.position.y
        end
    end

    ---- handle shooting ----
    if getInput(e, "fire") and timeElapsed > 0.33 then
        -- loop through upgrade table
        for k, v in pairs(playerTable[e].upgrade) do
            if v.name == "Upgrade1" then
                eBullet = addPrefab("bullet")
                local bulletTransform = getComponentTransform(eBullet)
                local transform = getComponentTransform(e)
                local bulletRB = getComponentRigidBody(eBullet)
                bulletTransform.position.x = transform.position.x + drawable.floatRect.width
                bulletTransform.position.y = transform.position.y - (drawable.floatRect.height * transform.scale.y) / 2
                bulletRB.velocity.y = 0

                eBullet = addPrefab("bullet")
                local bulletTransform = getComponentTransform(eBullet)
                local transform = getComponentTransform(e)
                local bulletRB = getComponentRigidBody(eBullet)
                bulletRB.velocity.y = 0
                bulletTransform.position.x = transform.position.x + drawable.floatRect.width
                bulletTransform.position.y = transform.position.y + (drawable.floatRect.height * transform.scale.y) / 2
            end
        end

        eBullet = addPrefab("bullet")
        local bulletTransform = getComponentTransform(eBullet)
        local transform = getComponentTransform(e)
        local bulletRB = getComponentRigidBody(eBullet)

        bulletRB.velocity.y = 0
        bulletTransform.position.x = transform.position.x + drawable.floatRect.width
        bulletTransform.position.y = transform.position.y
        -- networkSendInputToServer("fire")
        playSound(e, "pewpew")
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
    local transform = getComponentTransform(e)

    if tagOther == "enemy" then
        destroyEntity(e)
    end
    if tagOther == "Mob" then
        destroyEntity(e)
    end

    local isAlreadyUpgraded = isAlreadyUpgraded(e, tagOther)
    local idx = #playerTable[e].upgrade + 1
    if tagOther == "Upgrade1" and not isAlreadyUpgraded then
        playerTable[e].upgrade[idx] = {}
        playerTable[e].upgrade[idx].name = "Upgrade1"
        playerTable[e].upgrade[idx].id = other
        local transformUpgrade = getComponentTransform(other)
        transformUpgrade.position.x = transform.position.x + drawable.floatRect.width * transform.scale.x
        transformUpgrade.position.y = transform.position.y
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
end

function isAlreadyUpgraded(e, nameUpgrade)

    local result = false
    for k, v in pairs(playerTable[e].upgrade) do
        if nameUpgrade == v.name then
            result = true
            return result
        end
    end
    return result
end