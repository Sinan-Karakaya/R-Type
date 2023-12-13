/*
** EPITECH PROJECT, 2023
** testLua [WSL: Ubuntu-22.04]
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <sol/sol.hpp>

// Example struct component
struct position {
    int x;
    int y;

    // Define a tuple type using x and y
    using tuple_type = std::tuple<int, int>;

    // Convert position to a tuple
    tuple_type to_tuple() { return std::make_tuple(x, y); }

    // Convert tuple to position
    static position from_tuple(const tuple_type &tuple) { return {std::get<0>(tuple), std::get<1>(tuple)}; }
};

std::ostream &operator<<(std::ostream &os, const position &pos)
{
    os << "position gneu gneu(" << pos.x << ", " << pos.y << ")";
    return os;
}

// Template class for handling Lua interaction with a user-defined type T
template <typename T>
class luaType
{
public:
    /*
     ** Get the number of parameters the struct has
     ** - num_params is the number of parameters the struct has
     ** - static constexpr int type means that num_params is a compile-time constant
     ** - decltype is used to determine the type of an expression at compile time
     */
    static constexpr int num_params = std::tuple_size<decltype(T::to_tuple())>::value;

    /*
     ** constructor and destructor
     */
    luaType() = default;
    ~luaType() = default;

    /*
     ** Function to check if the Lua stack contains the correct number of parameters of type T
     ** https://sol2.readthedocs.io/en/latest/tutorial/customization.html
     */
    template <typename Handler>
    static bool lua_check(sol::types<T>, lua_State *L, int index, Handler &&handler, sol::stack::record &tracking)
    {
        int absolute_index = lua_absindex(L, index);
        bool success = true;

        std::cout << "lua_check" << std::endl;

        // Check each parameter in the tuple
        for (int i = 0; i < num_params; ++i) {
            success = success && sol::stack::check<int>(L, absolute_index + i, handler);
        }

        tracking.use(num_params);
        return success;
    }

    /*
     ** Function to retrieve an instance of T from the Lua stack
     ** - sol::types<T> is a tag type that indicates that the type is T
     ** - lua_State* L is the Lua state
     ** - int index is the index of the first parameter
     ** - sol::stack::record& tracking is used to keep track of the number of parameters
     */
    static T lua_get(sol::types<T>, lua_State *L, int index, sol::stack::record &tracking)
    {
        // absolute_index is the index of the first parameter
        int absolute_index = lua_absindex(L, index);
        // tuple_type is the type of the tuple
        typename T::tuple_type tuple;

        std::cout << "lua_get" << std::endl;

        // Populate the tuple from the Lua stack
        luaType<T>::populate_tuple_from_stack(L, absolute_index, tuple);
        // we use num_params slots, each of the previous takes 1
        tracking.use(num_params);

        // Return an instance of T from the tuple
        return T::from_tuple(tuple);
    }

    /*
     ** Function to push an instance of T onto the Lua stack
     */
    static int lua_push(lua_State *L, const T &value)
    {
        // Push the tuple onto the Lua stack and return the amount pushed
        std::cout << "lua_push" << std::endl;
        int amount = luaType<T>::push_tuple(L, value.to_tuple());
        return amount;
    }

    // void process_lua_function(const char *filepath, const char *function_name);

private:
    /*
        ** Helper function to populate a tuple from the Lua stack

        ** Template parameters:
        ** - Tuple is the type of the tuple
        ** - std::size_t... Is is a parameter pack of indices, in this case 0, 1, 2, ..., num_params - 1

        ** Function parameters:
        ** - lua_State* L is the Lua state
        ** - int index is the index of the first parameter
        ** - Tuple& tuple is the tuple to populate
        ** - std::index_sequence<Is...> is the actual id sequence
        ** - ... is the fold expression

        ** globaly this function is used to populate a tuple from the Lua stack
        ** it adds to all the previous parameters "..." the current parameter "std::get<Is>(tuple) =
       sol::stack::get<int>(L, index + Is)"
    */
    /*
    template <typename Tuple, std::size_t... Is>
    static void populate_tuple_from_stack_impl(lua_State* L, int index, Tuple& tuple, std::index_sequence<Is...>) {
        (..., std::get<Is>(tuple) = sol::stack::get<int>(L, index + Is));
    }
    */

    /*
        ** Function to populate a tuple from the Lua stack

        ** Template parameters:
        ** - Tuple is the type of the tuple

        ** Function parameters:
        ** - lua_State* L is the Lua state
        ** - int index is the index of the first parameter
        ** - Tuple& tuple is the tuple to populate

        ** - std::make_index_sequence<num_params> is used to generate a sequence of indices, in this case 0, 1, 2, ...,
       num_params - 1
    */
    template <typename Tuple>
    static void populate_tuple_from_stack(lua_State *L, int index, Tuple &tuple)
    {

        for (int i = 0; i < num_params; ++i) {
            std::get<i>(tuple) = sol::stack::get<int>(L, index + i);
        }
        // populate_tuple_from_stack_impl(L, index, tuple, std::make_index_sequence<num_params>{});
    }

    /*
        ** Helper function to push a tuple onto the Lua stack

        ** Template parameters:
        ** - Tuple is the type of the tuple
        ** - std::size_t... Is is a parameter pack of indices, in this case 0, 1, 2, ..., num_params - 1

        ** Function parameters:
        ** - lua_State* L is the Lua state
        ** - const Tuple& tuple is the tuple to push
        ** - std::index_sequence<Is...> is the actual id sequence
        ** - ... is the fold expression

    */
    template <typename Tuple, std::size_t... Is>
    static int push_tuple_impl(lua_State *L, const Tuple &tuple, std::index_sequence<Is...>)
    {
        int amount = 0;
        std::cout << "push_tuple_impl" << std::endl;
        // Push each element of the tuple onto the Lua stack
        (..., (amount += sol::stack::push(L, std::get<Is>(tuple))));
        return amount;
    }

    /*
        ** Function to push a tuple onto the Lua stack

        ** Template parameters:
        ** - Tuple is the type of the tuple

        ** Function parameters:
        ** lua_State* L is the Lua state
        ** const Tuple& tuple is the tuple to push

        ** - std::make_index_sequence<num_params> is used to generate a sequence of indices, in this case 0, 1, 2, ...,
       num_params - 1
    */
    template <typename Tuple>
    static int push_tuple(lua_State *L, const Tuple &tuple)
    {
        std::cout << "push_tuple" << std::endl;
        return push_tuple_impl(L, tuple, std::make_index_sequence<num_params> {});

        /* int amount = 0;
        // Push each element of the tuple onto the Lua stack
        std::apply([&](const auto&... elements) {
            (..., (amount += sol::stack::push(L, elements)));
        }, tuple);
        return amount;
        */
    }
};

// LuaApi class for handling Lua interaction
class LuaApi
{
public:
    LuaApi() { lua.open_libraries(sol::lib::base, sol::lib::package); }

    // Register a C++ type for use in Lua
    template <typename T>
    void registerType(const std::string &name)
    {
        lua.new_usertype<T>(name.c_str(), sol::constructors<T(int, int)>(), "to_tuple", &T::to_tuple, "from_tuple",
                            &T::from_tuple);
    }

    // Call a Lua function and return the result as a tuple
    template <typename... Ts>
    std::tuple<Ts...> callLuaFunction(const std::string &functionName, const Ts &...args)
    {
        sol::function f = lua[functionName];

        std::cout << "callLuaFunction" << std::endl;

        // Debug args
        std::cout << "args: " << std::endl;
        (std::cout << ... << args) << std::endl;
        std::cout << "tolo" << std::endl;
        // Use operator() to call the Lua function and handle errors
        std::cout << "----------------" << std::endl;
        auto result = f(args...);
        std::cout << "----------------" << std::endl;

        if (result.valid()) {

            return result.template get<std::tuple<Ts...>>();

            // return result.get<std::tuple<Ts...>>();
        } else {
            sol::error err = result;
            throw std::runtime_error("Lua function call error: " + std::string(err.what()));
        }
    }

    sol::state lua;

private:
};

struct two_things {
    int a;
    bool b;
};

template <typename Handler>
bool sol_lua_check(sol::types<two_things>, lua_State *L, int index, Handler &&handler, sol::stack::record &tracking)
{
    // indices can be negative to count backwards from the top of the stack,
    // rather than the bottom up
    // to deal with this, we adjust the index to
    // its absolute position using the lua_absindex function

    std::cout << "sol_lua_check" << std::endl;

    int absolute_index = lua_absindex(L, index);
    // Check first and second second index for being the proper types
    bool success =
        sol::stack::check<int>(L, absolute_index, handler) && sol::stack::check<bool>(L, absolute_index + 1, handler);
    tracking.use(2);
    return success;
}

two_things sol_lua_get(sol::types<two_things>, lua_State *L, int index, sol::stack::record &tracking)
{

    std::cout << "sol_lua_get" << std::endl;
    int absolute_index = lua_absindex(L, index);
    // Get the first element
    int a = sol::stack::get<int>(L, absolute_index);
    // Get the second element,
    // in the +1 position from the first
    bool b = sol::stack::get<bool>(L, absolute_index + 1);
    // we use 2 slots, each of the previous takes 1
    tracking.use(2);
    return two_things {a, b};
}

int sol_lua_push(lua_State *L, const two_things &things)
{

    std::cout << "sol_lua_push" << std::endl;
    int amount = sol::stack::push(L, things.a);
    // amount will be 1: int pushes 1 item
    amount += sol::stack::push(L, things.b);
    // amount 2 now, since bool pushes a single item
    // Return 2 things
    return amount;
}

int main()
{
    // Create an instance of LuaApi
    LuaApi luaApi;

    // Register the C++ type 'position' for use in Lua
    luaApi.registerType<position>("position");

    // Define a Lua function 'f' that takes a 'position' as an argument print content and returns it
    luaApi.lua.script("function f(a, b) print(a) return a,b end");

    // Call the Lua function 'f' with a 'position' argument
    auto result_tuple = luaApi.callLuaFunction<position>("f", position {1, 2});

    // Extract the position from the tuple
    position result = std::get<0>(result_tuple);

    // Print the result
    std::cout << "Result: " << result.x << ", " << result.y << std::endl;

    return 0;
}
