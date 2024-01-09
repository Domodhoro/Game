#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace Domodhoro
{
    // Classe responsável por gerenciar o estado do teclado.
	class Keyboard final
    {
    public:
        // Atualiza o estado do teclado e manipula eventos relevantes.
       	void update(bool& running)
    	{
    		while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    // Para sair do jogo.
                    running = false;

                    break;

                case SDL_KEYDOWN:
                    // Tecla pressionada.
                    handle_key_down(event.key.keysym.scancode);

                    break;

                case SDL_KEYUP:
                    // Tecla não pressionada.
                    handle_key_up(event.key.keysym.scancode);

                    break;
                }
            }
    	}

        // Retorna o estado da tecla.
        Entity::DIRECTION get_direction_from_key(const int key) const
        {
            // Procura a direção correspondente à tecla no mapeamento de teclas.
            const auto it = key_mappings.find(static_cast<int>(key));

            return (it != key_mappings.end()) ? it->second : Entity::DIRECTION::NONE;
        }

        // Obtém o conjunto de teclas atualmente pressionadas.
    	const std::unordered_set<SDL_Scancode>& get_keys() const
    	{
    		return keys;
    	}
    private:
        // Estrutura de evento SDL para capturar eventos.
        SDL_Event event;

        // Conjunto de teclas atualmente pressionadas.
    	std::unordered_set<SDL_Scancode> keys;

        // Mapeamento entre códigos de tecla e direções associadas.
    	std::map<int, Entity::DIRECTION> key_mappings = 
        {
            {SDL_SCANCODE_SPACE, Entity::DIRECTION::UP},
            {SDL_SCANCODE_A, Entity::DIRECTION::LEFT},
            {SDL_SCANCODE_D, Entity::DIRECTION::RIGHT}
        };

        // Manipula o evento de pressionar uma tecla.
        void handle_key_down(SDL_Scancode scancode)
        {
            keys.insert(scancode);
        }

        // Manipula o evento de soltar uma tecla.
        void handle_key_up(SDL_Scancode scancode)
        {
            keys.erase(scancode);
        }
    };
}

#endif // KEYBOARD_HPP