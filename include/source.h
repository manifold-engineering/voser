#ifndef SOURCE_H
#define SOURCE_H

struct Source{
    double x = 0;
    double y = 0;

    bool invert = false;
    double gain = 0;
    double delay = 0;

    bool active = true;

};

#endif // SOURCE_H
