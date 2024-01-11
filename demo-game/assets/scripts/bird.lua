-- Fill your copyright notice in copyrightNotice.txt

-- DemoGame - bird.lua
-- Created by skara
-- Thu Jan 11 18:25:30 2024

-- @brief This function will be called when your entity is instantiated
-- @param e The entity that was just created
function onStart(e)
    bird[e] = {}
    bird[e].score = 0
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
    local cameraSize = getCameraSize()
    local rb = getComponentRigidBody(e)

    ---- handle movement ----
    if getInput(e, "Jump") then
        if rb.velocity.y > 0 then
            rb.velocity.y = 0
        end
        if rb.velocity.y > -300 then
            rb.velocity.y = rb.velocity.y - 100
        end
        playSound(e, "flap", false)
    end

    if transform.position.y > cameraSize.y then
        transform.position.y = cameraSize.y
        rb.isColliding = true
    end
    
    ---- handle rotation ----
    if rb.velocity.y > 0 and transform.rotation.x < 50 then
        transform.rotation.x = transform.rotation.x + 1
    elseif rb.velocity.y < 0 and transform.rotation.x > -50 then
        transform.rotation.x = transform.rotation.x - 1
    elseif rb.velocity.y == 0 then
        transform.rotation.x = 0
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
    if getComponentTag(other) == "WallUp" or getComponentTag(other) == "WallDown" then
        if bird[e].score > 0 then
            bird[e].score = bird[e].score / 2
        end
        print("Game over! Score: " .. bird[e].score)
        destroyEntity(e)
    end
end

-- @brief This function will be called when a triggerEvent is called
-- @param event The event that was triggered
function onEvent(event)
    print("Event triggered: " .. event)
    bird[e].score = bird[e].score + 1
end

-- @brief This function will be called when a client presses a key (and it's send from client)
-- with networkSendInputToServer function.
-- @param e The entity that is being updated
-- @param input The input that was pressed
function onClientInput(e, input)

end