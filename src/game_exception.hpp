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
            
        }

        const char* what() const noexcept override
        {
            error_message = "Error : " + message              + "\n"
                            "File  : " + file                 + "\n"
                            "Line  : " + std::to_string(line) + "\n";
            
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