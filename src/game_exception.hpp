#ifndef GAME_EXCEPTION_HPP
#define GAME_EXCEPTION_HPP

namespace Domodhoro
{
    class Game_Exception final : public std::exception
    {
    public:
        Game_Exception(const char* error_message, const std::string& file, const int line)
        {
            message = "File: " + file + "\nLine: " + std::to_string(line) + "\nError message: " + error_message;
        }

        const char* what() const noexcept override
        {
            return message.c_str();
        }
    private:
        std::string message;
    };
}

#endif
