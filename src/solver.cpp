#include "solver.h"
//#include "globalconfig.h"

#include <iostream>
#include <cmath>
#include <numeric>
#include <limits>
#include <list>

extern double p_0;
extern double frequency;
extern double sound_velocity;
extern double base_SPL;
extern double minimal_distance;
extern double reference_distance;
extern double pi;

double square(double a){
    return a*a;
}

//sum two waves
wave sumTwoWaves(wave a, wave b){
    wave result;
    result.magnitude = sqrt(
        square(a.magnitude * cos(a.phase)
              +b.magnitude * cos(b.phase))
       +square(a.magnitude * sin(a.phase)
              +b.magnitude * sin(b.phase))
        );

    result.phase = atan2(a.magnitude * sin(a.phase)
                        +b.magnitude * sin(b.phase),
                         a.magnitude * cos(a.phase)
                        +b.magnitude * cos(b.phase));
    return result;
}

wave sumWaves(std::vector<wave> waves){
    wave result;
    result.magnitude = 0;
    result.phase = 0;

    for (wave w:waves){
        result = sumTwoWaves(result, w);
    }

    return result;
}



Solution MultisubSolver::solve(double frequency)
{
    /*
     *this method computes magnitude for specified points
     *uses previosly stored vectors of coordinates
     *accepts angular frequency - radians per second
     */
    for (Source s : sources){
        //  std::cout << "zdroj - x: " << s.x << ", y: " << s.y << std::endl;   //early debug
    }
    Solution result (coords_x.size(), coords_y.size());

    std::vector<wave>waves(sources.size());

    result.xMin = coords_x.front();
    result.xMax = coords_x.back();
    result.yMin = coords_y.front();
    result.yMax = coords_y.back();

    for(int x_index = 0; x_index < coords_x.size(); ++x_index){
        double x = coords_x[x_index];
        for(int y_index = 0; y_index < coords_y.size(); ++y_index){
            double y = coords_y[y_index];

            bool too_close = false;
            for (unsigned int i = 0; i<sources.size(); ++i){
                double distance = sqrt(square(x - sources[i].x)
                                      +square(y - sources[i].y));
                if (distance < minimal_distance){
                    too_close = true;
                    break;
                }
                waves[i].magnitude = (reference_distance/distance)
                                    * dB_to_p(base_SPL + sources[i].gain);
                waves[i].phase = frequency * distance / sound_velocity;
                waves[i].phase += frequency * (sources[i].delay/1000);
                if (sources[i].invert)
                    waves[i].phase += pi;


            }
            result(x_index, y_index) = too_close?
                           nan("") :
                           p_to_dB(sumWaves(waves).magnitude);

        }
    }



    return result;
}

Solution MultisubSolver::solve(std::vector<double> x, std::vector<double> y, std::vector<Source> sources, double frequency)
{
    this->coords_x = x;
    this->coords_y = y;
    this->sources = sources;

    return solve(frequency);
}

double p_to_dB(double p)
{
    return 20*log10(p/(p_0));
}

double dB_to_p(double db)
{
    return p_0 * pow(10., db/20.);
}
