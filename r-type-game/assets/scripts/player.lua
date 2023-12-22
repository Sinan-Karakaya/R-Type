function update(e)
    local transform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local drawable = getDrawable(e)

    local timeElapsed = getElapsedTimeScript(e)

    ---- handle animation ----
    -- local seconds = getElapsedTimeAnimation(e)
    -- if seconds > drawable.frameDuration and drawable.isAnimated then
    --     restartClockAnimation(e)
    --     drawable.currentFrame = drawable.currentFrame + 1
    --     drawable.floatRect.left = drawable.floatRect.left + drawable.leftDecal
    --     if drawable.currentFrame > drawable.frameCount then
    --         drawable.currentFrame = 0
    --     end
    -- end

    ---- actualize position ----
    -- drawable.floatRect.left = drawable.floatRect.left + drawable.leftDecal

    ---- handle movement ----
    if getInput(e, "moveUp") then
        if (transform.position.y - 8) > 0 then
            transform.position.y = transform.position.y - 8
            sendPosToServer(e)
        end
        drawable.currentFrame = 8
        drawable.floatRect.left = drawable.floatRect.width * drawable.currentFrame
    end
    if getInput(e, "moveDown") then
        if transform.position.y + 8 < cameraSize.y then
            transform.position.y = transform.position.y + 8
            sendPosToServer(e)
        end
        drawable.currentFrame = 4
        drawable.floatRect.left = drawable.floatRect.width * drawable.currentFrame
    end
    if getInput(e, "moveLeft") then
        if transform.position.x - 8 > 0 then
            transform.position.x = transform.position.x - 8
            sendPosToServer(e)
        end
        drawable.currentFrame = 0
        drawable.floatRect.left = drawable.floatRect.width * drawable.currentFrame
    end
    if getInput(e, "moveRight") then
        if transform.position.x + 8 < cameraSize.x then
            transform.position.x = transform.position.x + 8
            sendPosToServer(e)
        end
        drawable.currentFrame = 0
        drawable.floatRect.left = drawable.floatRect.width * drawable.currentFrame
    end

    ---- handle shooting ----
    if getInput(e, "fire") and timeElapsed > 1 then
        launchBullet(e)
        playSound(e, "pewpew")
        -- eBullet = addPrefab("bullet")
        -- local bulletTransform = getComponentTransform(eBullet)
        -- bulletTransform.position.x = transform.position.x - drawable.floatRect.width * transform.scale.x - 100 / 2
        -- bulletTransform.position.y = transform.position.y - drawable.floatRect.height * transform.scale.y - 100 / 2
        restartClockScript(e)
    end
end

function updateServer(e)

end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    if tagOther == "enemy" then
        destroyEntity(other)
    end
end
