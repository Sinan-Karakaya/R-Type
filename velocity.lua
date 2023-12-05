function updateVelocity(velocityComponent)

    -- avant d'avoir comprit
    local velocity = velocityComponent.velocity
    local acceleration = velocityComponent.acceleration
    local maxSpeed = velocityComponent.maxSpeed
    local friction = velocityComponent.friction
    local position = velocityComponent.position

    -- après avoir comprit
    -- local transform = getComponent(velocityComponent.entity, "transform")
    local transform = getComponent("transform")

    -- Apply acceleration
    velocity.x = velocity.x + acceleration.x
    velocity.y = velocity.y + acceleration.y

    -- Apply friction
    velocity.x = velocity.x * friction
    velocity.y = velocity.y * friction

    -- Limit speed
    if velocity.x > maxSpeed then
        velocity.x = maxSpeed
    elseif velocity.x < -maxSpeed then
        velocity.x = -maxSpeed
    end

    if velocity.y > maxSpeed then
        velocity.y = maxSpeed
    elseif velocity.y < -maxSpeed then
        velocity.y = -maxSpeed
    end

    -- Update position
    position.x = position.x + velocity.x
    position.y = position.y + velocity.y
end
