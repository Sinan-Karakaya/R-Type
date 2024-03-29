-- Fill your copyright notice in copyrightNotice.txt

-- r-type - starSpawner.lua
-- Created by 
-- Thu Jan 11 10:33:56 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    bulletEnemyTable = {}
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
function update(e, dt)
    local bulletTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local rigidBody = getComponentRigidBody(e)

    ---- handle movement ----
    bulletTransform.position.x = bulletTransform.position.x - rigidBody.velocity.x
    bulletTransform.position.y = bulletTransform.position.y - rigidBody.velocity.y
    if bulletTransform.position.x <= 0 then
        destroyEntity(e)
    end
    if bulletTransform.position.x >= cameraSize.x then
        destroyEntity(e)
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

    if tagOther == "Boss" then
        destroyEntity(e)
    end
    if tagOther == "Player" then
        destroyEntity(other)
        destroyEntity(e)
    end
    if tagOther == "bullet" then
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