#include "neuron.h"

Neuron::Neuron(){
    weights[0] = rand() % 255;
    weights[1] = rand() % 255;
    weights[2] = rand() % 255;
}

Neuron::~Neuron(){

}

double Neuron::get_distance(unsigned char *point){
    double distance = sqrt(pow(weights[0] - static_cast<double>(point[0]), 2) + pow(weights[1] - static_cast<double>(point[1]), 2) + pow(weights[2] - static_cast<double>(point[2]), 2));

    return distance;
}

void Neuron::update_weights(unsigned char *point, double change_rate){
    weights[0] = weights[0] + change_rate * (point[0] - weights[0]);
    weights[1] = weights[1] + change_rate * (point[1] - weights[1]);
    weights[2] = weights[2] + change_rate * (point[2] - weights[2]);
}
