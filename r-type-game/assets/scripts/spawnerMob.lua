-- Fill your copyright notice in copyrightNotice.txt

-- r-type - starSpawner.lua
-- Created by 
-- Thu Jan 11 10:33:56 2024

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
    local screen = getCameraSize()

    if timeElapsed > 10 then
        local rdm = math.random(1, 2)
        enemy = addPrefab("Mob")
        local enemyTransform = getComponentTransform(enemy)
        local rigidBody = getComponentRigidBody(enemy)
        local drawable = getComponentDrawable(enemy)

        if rdm == 1 then
            enemyTransform.position.x = screen.x + 50
            rigidBody.velocity.x = rigidBody.velocity.x * -1
        else
            enemyTransform.position.x = -50
            drawable.floatRect.top = drawable.floatRect.height
        end
        enemyTransform.position.y =  math.random(1, screen.y)
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