-- Fill your copyright notice in copyrightNotice.txt

-- r-type - starSpawner.lua
-- Created by 
-- Thu Jan 11 10:33:56 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    bossTable[e] = {}
    bossTable[e].isShielding = 1 -- true
    bossTable[e].shieldTimer = 10
    bossTable[e].weakTimer = 3
    bossTable[e].lastFire = 0

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
function update(e)
    local cameraSize = getCameraSize()
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeIAControllable(e)

    -- check boss state change
    if bossTable[e].isShielding == 1 and timeElapsed >= bossTable[e].shieldTimer then
        bossTable[e].isShielding = false
        restartClockIAControllable(e)
    elseif bossTable[e].isShielding == 0 and timeElapsed >= bossTable[e].weakTimer then
        bossTable[e].isShielding = true
        restartClockIAControllable(e)
    end

    -- handle animation on state change
    if bossTable[e].isShielding and drawable.floatRect.left ~= 1849 then
        drawable.leftDecal = 263
        drawable.autoPlay = true
    elseif not bossTable[e].isShielding and drawable.floatRect.left >= 0 then
        drawable.leftDecal = -263
        drawable.autoPlay = true
    elseif drawable.autoPlay then
        drawable.autoPlay = false
    end

    -- handle attack
    if not bossTable[e].isShielding and bossTable[e].lastFire + 1 <= timeElapsed then
        bossTable[e].lastFire = timeElapsed
        local bullet = createEntity("bullet")
        local bulletTransform = getComponentTransform(bullet)
        local bulletRigidBody = getComponentRigidBody(bullet)
        local bossTransform = getComponentTransform(e)

        bulletTransform.position.x = bossTransform.position.x
        bulletTransform.position.y = bossTransform.position.y + bossDrawable.floatRect.width / 2
        bulletRigidBody.velocity.x = -8
        bulletRigidBody.velocity.y = math.random(-2, 2)
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
    if getComponentTag(other) == "bullet" then
        destroyEntity(e)
        destroyEntity(other)
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