#ifndef GAME_EXCEPTION_HPP
#define GAME_EXCEPTION_HPP

namespace Domodhoro
{

class Game_Exception final : public std::exception
{
public:
    Game_Exception(const std::string& message, const std::string& file, const int line) :
        message(message),
        file(file),
        line(line)
    {
        std::cout << "Descrição interna (SDL) do erro: " << SDL_GetError() << std::endl;
    }

    const char* what() const noexcept override
    {
        error_message = "File    : " + file                 + "\n"
                        "Line    : " + std::to_string(line) + "\n"
                        "Message : " + message              + "\n";
        
        return error_message.c_str();
    }
private:
    std::string message;
    std::string file;

    int line;

    mutable std::string error_message;
};

}

#endif