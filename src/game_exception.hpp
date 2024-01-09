#ifndef GAME_EXCEPTION_HPP
#define GAME_EXCEPTION_HPP

namespace Domodhoro
{
    // A classe Game_Exception é uma exceção personalizada que herda de std::exception.
    class Game_Exception final : public std::exception
    {
    public:
        // Construtor da exceção que aceita uma mensagem de erro, o nome do arquivo e o número da linha.
        Game_Exception(const char* error_message, const std::string& file, const int line)
        {
            // Constrói a mensagem de erro formatada com informações sobre o arquivo, linha e mensagem de erro original.
            message = "File: " + file + "\nLine: " + std::to_string(line) + "\nError message: " + error_message;
        }

        // Sobrescreve a função 'what' da classe base para fornecer a mensagem de erro quando a exceção é lançada.
        const char* what() const noexcept override
        {
            return message.c_str();
        }

    private:
        // Armazena a mensagem de erro.
        std::string message;
    };
}

#endif // GAME_EXCEPTION_HPP