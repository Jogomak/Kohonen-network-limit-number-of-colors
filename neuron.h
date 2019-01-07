#ifndef NEURON_H
#define NEURON_H

#include"include.h"

class Neuron
{
public:
    Neuron();
    ~Neuron();

    double weights[3]; //position

    double get_distance(unsigned char *point);
    void update_weights(unsigned char *point, double change_rate);
};

#endif // NEURON_H
