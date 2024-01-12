function onStart(e)
    enemyTable[e] = {}
    enemyTable[e].amp = 200 -- Amplitude of the wave (how far up and down it goes)
    enemyTable[e].freq = 2 -- Frequency of the wave (how fast it oscillates)
    enemyTable[e].speed = 0.05 -- Speed at which the wave moves (can be adjusted separately from frequency)
    enemyTable[e].offset = math.pi / math.random(1, 4) -- Phase shift of the wave (how far to shift the wave horizontally)
    enemyTable[e].lastFire = 0
    enemyTable[e].time = 0
end

function update(e)

end

function updateServer(e)
    local enemyTransform = getComponentTransform(e)
    local cameraSize = getCameraSize()
    local rigidBody = getComponentRigidBody(e)
    local drawable = getDrawable(e)
    local timeElapsed = getElapsedTimeIAControllable(e)

    drawable.autoPlay = false

    local t = timeElapsed * enemyTable[e].speed + enemyTable[e].offset -- Get current time and adjust by phase shift and speed
    pos_y = -enemyTable[e].amp * math.sin(enemyTable[e].freq * t * 2 * math.pi) + cameraSize.y / 2 -- Map time value to y coordinate range

    ---- sinusoide movement ----
    enemyTransform.position.y = pos_y
    enemyTransform.position.x = enemyTransform.position.x - rigidBody.velocity.x * 2

    print("debug -> " .. enemyTransform.position.x)
    print("debug -> " .. enemyTransform.position.y)

    -- debug the entire enemyTable --
    print("debug -> " .. enemyTable[e].amp)
    print("debug -> " .. enemyTable[e].freq)
    print("debug -> " .. enemyTable[e].speed)
    print("debug -> " .. enemyTable[e].offset)
    print("debug -> " .. enemyTable[e].lastFire)
    print("debug -> " .. enemyTable[e].time)

    enemyTable[e].time = math.floor(timeElapsed)
    if enemyTable[e].time - enemyTable[e].lastFire >= 2  then
        ---- handle shooting ----
        enemyTable[e].lastFire = enemyTable[e].time
        -- playSound(e, "pewpew")
        eBullet = addPrefab("bulletEnemy")
        local bulletTransform = getComponentTransform(eBullet)
        bulletTransform.position.x = enemyTransform.position.x
        bulletTransform.position.y = enemyTransform.position.y
    end

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

    local var = math.random(1, 1)

    -- spawn upgrade
    if var == 1 then
        eUpgrade = addPrefab("Upgrade1")
        local upgradeTransform = getComponentTransform(eUpgrade)
        local transform = getComponentTransform(e)
        upgradeTransform.position.x = transform.position.x
        upgradeTransform.position.y = transform.position.y
    end
end