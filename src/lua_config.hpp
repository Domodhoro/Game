#ifndef LUA_CONFIG_HPP
#define LUA_CONFIG_HPP

namespace Domodhoro
{
    // Classe responsável por carregar e gerenciar configurações do jogo usando Lua.
    class Lua_Config final
    {
    public:
        // Construtor que cria um novo estado Lua e carrega o arquivo de configuração.
        Lua_Config(const std::string& file_path) :
            L(luaL_newstate())
        {
            // Verifica se o estado Lua foi criado com sucesso.
            if (!L)
            {
                // Em caso de falha.
                throw Game_Exception("Failed to create Lua state.", __FILE__, __LINE__);
            }

            // Abre as bibliotecas padrão do Lua.
            luaL_openlibs(L);

            // Tenta executar o arquivo de configuração Lua.
            if (luaL_dofile(L, file_path.c_str()) != 0)
            {
                const char* message = lua_tostring(L, -1);

                // Em caso de falha, lança uma exceção com a mensagem de erro do Lua.
                throw Game_Exception(message, __FILE__, __LINE__);
            }
        }

        // Destrutor que fecha o estado Lua quando a instância é destruída.
        ~Lua_Config()
        {
            // Verifica se o estado Lua é válido antes de fechá-lo.
            if (L)
            {
                lua_close(L);
            }
        }
    private:
        // Ponteiro para o estado Lua.
        lua_State* L;
    };
}

#endif // LUA_CONFIG_HPP