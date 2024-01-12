function onStart(e)

end

function onDestroy(e)

end

function update(e)

end

function updateServer(e)

    local timeElapsed = getElapsedTimeScript(e)
    local screen = getCameraSize()

    if timeElapsed > 6 then
        enemy = addPrefab("enemy")
        enemyTransform = getComponentTransform(enemy)
        enemyTransform.position.x = screen.x + 50
        restartClockScript(e)
    end
end

function onCollision(e, other)

end

function onEvent(e, input)

end