#ifndef NOISE_HPP
#define NOISE_HPP

namespace Domodhoro
{

class Noise final
{
public:
    Noise(const int seed) :
        noise(fnlCreateState())
    {
        noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
        noise.seed = seed;
    }

    float get(const int x, const int y)
    {
        return fnlGetNoise2D(&noise, x, y);
    }
private:
    fnl_state noise;
};

}

#endif