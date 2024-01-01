#ifndef LUA_CONFIG_HPP
#define LUA_CONFIG_HPP

namespace Domodhoro
{
    class Lua_Config final
    {
    public:
        Lua_Config() :
            L(luaL_newstate())
        {
            if (!L)
            {
                throw Game_Exception("Failed to create Lua state.", __FILE__, __LINE__);
            }

            luaL_openlibs(L);
        }

        ~Lua_Config()
        {
            if (L)
            {
                lua_close(L);
            }
        }

        void load(const std::string& file_path)
        {
            if (luaL_dofile(L, file_path.c_str()) != 0)
            {
                const char* message = lua_tostring(L, -1);

                throw Game_Exception(message, __FILE__, __LINE__);
            }
        }
    private:
        lua_State* L;
    };
}

#endif