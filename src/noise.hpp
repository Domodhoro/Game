#ifndef NOISE_HPP
#define NOISE_HPP

namespace Domodhoro
{
    // Classe responsável por gerar ruído usando a biblioteca FastNoiseLite.
    class Noise final
    {
    public:
        // Construtor que inicializa a instância do gerador de ruído com uma semente.
        Noise(const int seed) :
            noise(fnlCreateState())
        {
            // Configura o tipo de ruído e a semente.
            noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
            noise.seed = seed;
        }

        // Obtém o valor de ruído para as coordenadas especificadas.
        float get(const int x, const int y)
        {
            return fnlGetNoise2D(&noise, x, y);
        }
    private:
        // Estrutura que mantém o estado do gerador de ruído.
        fnl_state noise;
    };
}

#endif // NOISE_HPP