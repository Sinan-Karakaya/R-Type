function update(e)

    local timeElapsed = getElapsedTimeScript(e)
    local screen = getCameraSize()

    if timeElapsed > 2 then
        enemy = addPrefab("enemy")
        enemyTransform = getComponentTransform(enemy)
        enemyTransform.position.x = screen.x - screen.x / 4
        restartClockScript(e)
    end
end