-- Fill your copyright notice in copyrightNotice.txt

-- r-type - starSpawner.lua
-- Created by 
-- Thu Jan 11 10:33:56 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    bossTable[e] = {}
    bossTable[e].health = 15

    local t = getComponentTransform(e)
    local cameraSize = getCameraSize()
    t.position.x = cameraSize.x - 143
    t.position.y = cameraSize.y / 2 - 131
end

-- @brief This function will be called when the entity is destroyed
-- @param e The entity that is being destroyed
function onDestroy(e)
    -- TODO: win game
end

-----------------------------------------------------------------------------------
-- Update functions
-- These functions will be called every frame
-----------------------------------------------------------------------------------

-- @brief This function will be called every frame
-- @param e The entity that is being updated
function update(e, dt)
    local cameraSize = getCameraSize()
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeIAControllable(e)

    -- handle attack
    if timeElapsed >= 2 then
        local bullet = addPrefab("bulletEnemy")
        local bulletTransform = getComponentTransform(bullet)
        local bulletRigidBody = getComponentRigidBody(bullet)
        local bossTransform = getComponentTransform(e)
        local bossDrawable = getComponentDrawable(e)

        bulletTransform.position.x = bossTransform.position.x
        bulletTransform.position.y = bossTransform.position.y + bossDrawable.floatRect.width / 2
        bulletRigidBody.velocity.x = 8
        bulletRigidBody.velocity.y = math.random(-2, 2)
        restartClockIAControllable(e)
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
    
    destroyEntity(other)
    if getComponentTag(other) == "bullet" then
        bossTable[e].health = bossTable[e].health - 1
        if bossTable[e].health == 0 then
            destroyEntity(e)
        end
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