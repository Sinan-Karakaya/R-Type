-- Fill your copyright notice in copyrightNotice.txt

-- DemoGame - wall.lua
-- Created by skara
-- Thu Jan 11 18:25:24 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    wall[e] = {}
    wall[e].scored = false
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
    local transform = getComponentTransform(e)

    if not wall[e].scored and transform.position.x < 200 and transform.position.y > 500 then
        wall[e].scored = true
        playSound(e, "score", false)
        triggerEvent("score")
    end

    transform.position.x = transform.position.x - 3
    if transform.position.x < -100 then
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