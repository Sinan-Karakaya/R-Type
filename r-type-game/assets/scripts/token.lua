function update(e)
    local transform=getComponentTransform(e)

    if getInput(e, "moveUp") then
        transform.position.y = transform.position.y - 1
        print("moveUp")
    end
    if getInput(e, "moveDown") then
        transform.position.y = transform.position.y + 1
        print("moveDown")
    end
    if getInput(e, "moveLeft") then
        transform.position.x = transform.position.x - 1
        print("moveLeft")
    end
    if getInput(e, "moveRight") then
        transform.position.x = transform.position.x + 1
        print("moveRight")
    end
end