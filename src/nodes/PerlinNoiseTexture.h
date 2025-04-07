#pragma once
#include <vector>
#include <random>
class PerlinNoiseTexture
{
public:
    PerlinNoiseTexture(unsigned int seed = std::default_random_engine::default_seed);
   
    double noise(double x, double y, double z);

private:
    std::vector<int> p;

    double fade(double t);

    double lerp(double t, double a, double b);

    double grad(int hash, double x, double y, double z);

};

