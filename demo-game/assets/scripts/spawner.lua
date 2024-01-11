-- Fill your copyright notice in copyrightNotice.txt

-- DemoGame - spawner.lua
-- Created by skara
-- Thu Jan 11 18:25:18 2024

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
function update(e, dt)
    local timeElapsed = getElapsedTimeScript(e)

    if timeElapsed > 2 then
        local entity = addPrefab("wallUp")
        local transform = getComponentTransform(entity)
        local cameraSize = getCameraSize()
        local randomOffset = math.random(-200, 200)
        transform.position.x = cameraSize.x + 100
        transform.position.y = -50 + randomOffset

        local entity2 = addPrefab("wallDown")
        local transform2 = getComponentTransform(entity2)
        transform2.position.x = cameraSize.x + 100
        transform2.position.y = cameraSize.y + 50 + randomOffset

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