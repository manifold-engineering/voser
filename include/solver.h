#ifndef SOLVER_H
#define SOLVER_H

#include "source.h"
#include "solution.h"

#include <vector>
#include <cmath>
#include <list>

//just to represent magnitude and phase of a single wave
struct wave{
    double magnitude;
    double phase;
};

//just to make computing code shorter
double square(double a);

//sum two waves
wave sumTwoWaves(wave a, wave b);
//sum multiple waves
wave sumWaves(std::list<wave> waves);


double p_to_dB (double);
double dB_to_p (double);

class MultisubSolver
{
private:
    std::vector<double> coords_x, coords_y;
    std::vector<Source> sources;

public:
    MultisubSolver(){};
    Solution solve (double frequency);
    Solution solve(std::vector<double> x, std::vector<double> y, std::vector<Source> sources, double frequency);
};

#endif // SOLVER_H
