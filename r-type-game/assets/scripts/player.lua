function update(e)
    local transform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local seconds = getElapsedTimeAnimation(e)
    local drawable = getDrawable(e)

    -- debug floatRect
    local floatRect = floatRect(0.1,0.2,0.3,0.4)
    print("floatRect.left: " .. floatRect.left)
    print("floatRect.top: " .. floatRect.top)
    print("floatRect.width: " .. floatRect.width)
    print("floatRect.height: " .. floatRect.height)
    -- debug floatRect
    print("player update")
    print("seconds: " .. seconds)
    print("drawable.frameDuration: " .. drawable.frameDuration)
    print("drawable.isAnimated: " .. tostring(drawable.isAnimated))
    print("drawable.currentFrame: " .. drawable.currentFrame)
    print("drawable.frameCount: " .. drawable.frameCount)
    print("drawable.floatRect.left: " .. drawable.floatRect.left)
    print("drawable.floatRect.width: " .. drawable.floatRect.width)

    ---- handle animation ----
    if seconds > drawable.frameDuration and drawable.isAnimated then
        restartClockAnimation(e)
        drawable.currentFrame = drawable.currentFrame + 1
        drawable.floatRect.left = drawable.floatRect.width * drawable.currentFrame
        if drawable.currentFrame > drawable.frameCount then
            drawable.currentFrame = 0
        end
    end

    ---- handle movement ----
    if getInput(e, "moveUp") then
        if (transform.position.y - 2) > 0 then
            transform.position.y = transform.position.y - 2
            sendPosToServer(e)
        end
    end
    if getInput(e, "moveDown") then
        if transform.position.y + 2 < cameraSize.y then
            transform.position.y = transform.position.y + 2
            sendPosToServer(e)
        end
    end
    if getInput(e, "moveLeft") then
        if transform.position.x - 2 > 0 then
            transform.position.x = transform.position.x - 2
            sendPosToServer(e)
        end
    end
    if getInput(e, "moveRight") then
        if transform.position.x + 2 < cameraSize.x then
            transform.position.x = transform.position.x + 2
            sendPosToServer(e)
        end
    end

    ---- handle shooting ----
    if getInput(e, "fire") then
        launchBullet(e)
    end
end

function onCollision(e, other)
    local tagOther = getComponentTag(other)
    -- print(tagOther)
    if tagOther == "enemy" then
        destroyEntity(other)
    end
end
