/*
** EPITECH PROJECT, 2023
** testLua [WSL: Ubuntu-22.04]
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <sol/sol.hpp>

struct vector {
    int x;
    int y;

    vector get_vector_component() { return vector {3, 4}; };
};

struct transform {
    int x;
    int y;
    sf::Vector2f v;

    transform get_transorm_component() { return transform {1, 2, sf::Vector2f {3, 4}}; };
};

int main()
{
    sol::state lua;

    lua.open_libraries(sol::lib::base);

    // make usertype metatable for vector
    sol::usertype<sf::Vector2f> vector_type =
        lua.new_usertype<sf::Vector2f>(
            "vector", sol::constructors<sf::Vector2f(float, float)>(),
            "x", &sf::Vector2f::x,
            "y", &sf::Vector2f::y
        );

    // vector_type["x"] = &sf::Vector2f::x;
    // sol::property(&vector::get_x, &vector::set_x);
    // vector_type["y"] = &sf::Vector2f::y;
    // sol::property(&vector::get_y, &vector::set_y);

    // make usertype metatable
    sol::usertype<transform> transform_type =
        lua.new_usertype<transform>("transform", sol::constructors<transform(int, int, sf::Vector2f)>(), "x", &transform::x,
                                    "y", &transform::y, "v", &transform::v);

    // typical member function that returns a variable
    transform_type["getComponent"] = &transform::get_transorm_component;

    // read and write variable
    // transform_type["x"] = &transform::x;
    // transform_type["y"] = &transform::y;
    // can only read from, not write to
    // .set(foo, bar) is the same as [foo] = bar;
    // player_type.set("bullets", sol::readonly(&player::bullets));

    lua.script("function test () print(\"----\") transform=transform.new(5, 6, vector.new(7, 8)) print(transform.x) "
               "print(transform.y) print(transform.v.x) print(transform.v.y) transform.x = 10 transform.y = 11 "
               "transform.v.x = 12 transform.v.y = 13  print(\"----\") return transform end");
    sol::function f = lua["test"];
    transform things = f();

    std::cout << "things.a: " << things.x << std::endl;
    std::cout << "things.b: " << things.y << std::endl;
    std::cout << "things.c: " << things.v.x << ", " << things.v.y << std::endl;

    return 0;
}
