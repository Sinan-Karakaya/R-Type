-- Fill your copyright notice in copyrightNotice.txt

-- r-type - starSpawner.lua
-- Created by 
-- Thu Jan 11 10:33:56 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    enemyTable[e] = {}
    enemyTable[e].amp = 200 -- Amplitude of the wave (how far up and down it goes)
    enemyTable[e].freq = 2 -- Frequency of the wave (how fast it oscillates)
    enemyTable[e].speed = 0.05 -- Speed at which the wave moves (can be adjusted separately from frequency)
    enemyTable[e].offset = math.pi / math.random(1, 4) -- Phase shift of the wave (how far to shift the wave horizontally)
    enemyTable[e].lastFire = 0
    enemyTable[e].time = 0
end

-- @brief This function will be called when the entity is destroyed
-- @param e The entity that is being destroyed
function onDestroy(e)
    local var = math.random(1, 1)

    -- spawn upgrade
    if var == 1 then
        eUpgrade = addPrefab("Upgrade1")
        local upgradeTransform = getComponentTransform(eUpgrade)
        local transform = getComponentTransform(e)
        upgradeTransform.position.x = transform.position.x
        upgradeTransform.position.y = transform.position.y
    end
end

-----------------------------------------------------------------------------------
-- Update functions
-- These functions will be called every frame
-----------------------------------------------------------------------------------

-- @brief This function will be called every frame
-- @param e The entity that is being updated
function update(e)
    local cameraSize = getCameraSize()
    local rigidBody = getComponentRigidBody(e)
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeIAControllable(e)

    local t = timeElapsed * enemyTable[e].speed + enemyTable[e].offset -- Get current time and adjust by phase shift and speed
    pos_y = -enemyTable[e].amp * math.sin(enemyTable[e].freq * t * 2 * math.pi) + cameraSize.y / 2 -- Map time value to y coordinate range

    ---- sinusoide movement ----
    enemyTransform.position.y = pos_y
    enemyTransform.position.x = enemyTransform.position.x - rigidBody.velocity.x * 2

    enemyTable[e].time = math.floor(timeElapsed)
    if enemyTable[e].time - enemyTable[e].lastFire >= 4  then
        ---- handle shooting ----
        enemyTable[e].lastFire = enemyTable[e].time
        -- playSound(e, "pewpew")
        eBullet = addPrefab("bulletEnemy")
        local bulletTransform = getComponentTransform(eBullet)
        bulletTransform.position.x = enemyTransform.position.x
        bulletTransform.position.y = enemyTransform.position.y
    end

    if enemyTransform.position.x + (drawable.floatRect.width * enemyTransform.scale.x) <= 0 then
        destroyEntity(e)
    end
end

-- @brief This function will be called every frame on the server
-- @param e The entity that is being updated
function updateServer(e)
    -- local enemyTransform = getComponentTransform(e)
    -- local cameraSize = getCameraSize()
    -- local rigidBody = getComponentRigidBody(e)
    -- local drawable = getDrawable(e)
    -- local timeElapsed = getElapsedTimeIAControllable(e)

    -- drawable.autoPlay = false

    -- local t = timeElapsed * enemyTable[e].speed + enemyTable[e].offset -- Get current time and adjust by phase shift and speed
    -- pos_y = -enemyTable[e].amp * math.sin(enemyTable[e].freq * t * 2 * math.pi) + cameraSize.y / 2 -- Map time value to y coordinate range

    -- ---- sinusoide movement ----
    -- enemyTransform.position.y = pos_y
    -- enemyTransform.position.x = enemyTransform.position.x - rigidBody.velocity.x * 2

    -- enemyTable[e].time = math.floor(timeElapsed)
    -- if enemyTable[e].time - enemyTable[e].lastFire >= 4  then
    --     ---- handle shooting ----
    --     enemyTable[e].lastFire = enemyTable[e].time
    --     -- playSound(e, "pewpew")
    --     eBullet = addPrefab("bulletEnemy")
    --     local bulletTransform = getComponentTransform(eBullet)
    --     bulletTransform.position.x = enemyTransform.position.x
    --     bulletTransform.position.y = enemyTransform.position.y
    -- end

    -- if enemyTransform.position.x + (drawable.floatRect.width * enemyTransform.scale.x) <= 0 then
    --     destroyEntity(e)
    -- end
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

