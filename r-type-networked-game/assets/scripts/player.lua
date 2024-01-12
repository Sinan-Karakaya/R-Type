-- Fill your copyright notice in copyrightNotice.txt

-- r-type-networked - player.lua
-- Created by 
-- Fri Jan 12 23:34:41 2024

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

    ---- handle shooting ----
    if getInput(e, "fire") and timeElapsed > 0.55 then
        networkSendInputToServer("fire")
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
	if input == "fire" then
        eBullet = addPrefab("Bullet")
        local bulletTransform = getComponentTransform(eBullet)
        local transform = getComponentTransform(e)
        bulletTransform.position.x = transform.position.x
        bulletTransform.position.y = transform.position.y
    end
end


