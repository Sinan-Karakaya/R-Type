function onStart(e)

end

function onDestroy(e)

end

function update(e)
    local starTransform = getComponentTransform(e)
    local rigidBody = getComponentRigidBody(e)

    starTransform.position.x = starTransform.position.x - rigidBody.velocity.x

    if starTransform.position.x < -10 then
        starTransform.position.x = getCameraSize().x + 10
    end
end

function updateServer(e)

end
