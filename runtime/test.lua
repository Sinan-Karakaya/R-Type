function math()

    print("start math")
    -- init vars --
    local a = 10
    local b = 5

    -- call cpp function --
    local add = my_add(a, b)

    print("a + b = " .. add)
    print("end math")

    return add

end

function update()

    print("start update")
    -- init default var --
    local mytable = {x = 10, y = 5}
    print("mytable.x = " .. mytable.x .. ", mytable.y = " .. mytable.y)

    -- call cpp function --
    mytable = getComponent()

    print("ok ici")
    print("mytable.x = " .. mytable.x .. ", mytable.y = " .. mytable.y)
    print("end update")

    return mytable
end

function testGetPos()
   
    -- get data player from cpp loaded function in this script --
    -- data is a table with x and y --
    print("-- start --")
    local table = g()

    -- print data position --
    if table == nil then
        print("Failed to get data player from cpp")
    else
        local x = table.x and string.format("%.2f", table.x) or "nil"
        local y = table.y and string.format("%.2f", table.y) or "nil"
        print("data player: " .. x .. ", " .. y)
    end
    print("-- end --")
end

function updateDataPlayer()
   
    -- get data player from cpp loaded function in this script --
    print("getting data from cpp")
    local data = getDataPlayer()
    print("end getting data from cpp")

    -- print data player --
    if data == nil then
        print("Failed to get data player from cpp")
    else
        local x = data.x and string.format("%.2f", data.x) or "nil"
        local y = data.y and string.format("%.2f", data.y) or "nil"
        print("data player: " .. x .. ", " .. y)
    end
end