-- Fill your copyright notice in copyrightNotice.txt

-- r-type-networked - ennemy.lua
-- Created by 
-- Sat Jan 13 00:00:12 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)

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

end

-- @brief This function will be called every frame on the server
-- @param e The entity that is being updated
function updateServer(e)
    local enemyTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local rigidBody = getComponentRigidBody(e)

    local t = 0.01 * 0.05 + math.pi / math.random(1, 4) -- Get current time and adjust by phase shift and speed
    local pos_y = -200 * math.sin(2 * t * 2 * math.pi) + cameraSize.y / 2 -- Map time value to y coordinate range

    ---- sinusoide movement ----
    enemyTransform.position.y = pos_y
    enemyTransform.position.x = enemyTransform.position.x - rigidBody.velocity.x * 2

    local drawable = getDrawable(e)
    if enemyTransform.position.x + (drawable.floatRect.width * enemyTransform.scale.x) <= 0 then
        destroyEntity(e)
    end
end

-----------------------------------------------------------------------------------
-- Other functions
-- These functions will be called when certain events happen
-----------------------------------------------------------------------------------

-- @brief This function will be called when the entity collides with another entity
-- @param e The entity that is being updated
-- @param other The entity that was collided with
function onCollision(e, other)
    if getComponentTag(other) == "Bullet" then
        destroyEntity(e)
        destroyEntity(other)
    end
end

-- @brief This function will be called when a triggerEvent is called
-- @param e The entity that is being updated
-- @param event The event that was triggered
function onEvent(e, event)

end

-- @brief This function will be called when a client presses a key (and it's send from client)
-- with networkSendInputToServer function.
-- @param e The entity that is being updated
-- @param input The input that was pressed
function onClientInput(e, input)

end
