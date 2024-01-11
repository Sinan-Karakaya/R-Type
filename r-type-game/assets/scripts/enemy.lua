function onStart(e)
    enemyTable[e] = {}
    enemyTable[e].amp = 200 -- Amplitude of the wave (how far up and down it goes)
    enemyTable[e].freq = 2 -- Frequency of the wave (how fast it oscillates)
    enemyTable[e].speed = 0.25 -- Speed at which the wave moves (can be adjusted separately from frequency)
    enemyTable[e].offset = math.pi / math.random(1, 4) -- Phase shift of the wave (how far to shift the wave horizontally)
end

function update(e)
end

function updateServer(e)
    local enemyTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local rigidBody = getComponentRigidBody(e)
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeIAControllable(e)

    -- enemyTable[e].time = enemyTable[e].time + timeElapsed
    -- local y_position = enemyTable[e].amplitude * math.sin(enemyTable[e].speed * enemyTable[e].time)

    local t = timeElapsed * enemyTable[e].speed + enemyTable[e].offset -- Get current time and adjust by phase shift and speed
    pos_y = -enemyTable[e].amp * math.sin(enemyTable[e].freq * t * 2 * math.pi) + cameraSize.y / 2 -- Map time value to y coordinate range

    ---- sinusoide movement ----
    -- enemyTable[e].phaseShift = enemyTable[e].phaseShift + timeElapsed * enemyTable[e].frequency
    -- local yNewPos = enemyTable[e].amplitude * math.sin(enemyTable[e].phaseShift)
    enemyTransform.position.y = pos_y
    enemyTransform.position.x = enemyTransform.position.x - rigidBody.velocity.x * 2

    if enemyTransform.position.x + (drawable.floatRect.width * enemyTransform.scale.x) <= 0 then
        destroyEntity(e)
    end
end

function onCollision(e, other)
    if getComponentTag(other) == "bullet" then
        destroyEntity(e)
        destroyEntity(other)
    end
end

function onDestroy(e)

end