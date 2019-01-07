#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    image_width = 222;
    image_height = 374;
    image_pixels_amount = image_width * image_height;
    this->setMinimumSize(image_width * 2 + 5, image_height);


    image_input = new QImage(":/dogo.png", "PNG");
    image_output = new QImage(image_width, image_height, QImage::Format_ARGB32);
    image_input_bits = image_input->bits();
    image_output_bits = image_output->bits();


    nodes_horizontally = 50;
    nodes_vertically = 50; //graph of size (nodes_horizontally x nodes_vertically), multiplication give number of neurons
    nodes_amount = nodes_horizontally * nodes_vertically;
    learning_rounds = image_pixels_amount * 5;

    initialize_neurons();
    learn_neurons();
    repaint_image();
}

MainWindow::~MainWindow(){
    for(int i = 0; i < nodes_amount; i++){
        delete neurons[i];
    }
    delete [] neurons;

    delete image_output;
    delete image_input;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);

    painter.drawImage(0, 0, *image_input);
    painter.drawImage(image_width + 5, 0, *image_output);
}

void MainWindow::initialize_neurons(){
    neurons = new Neuron*[nodes_amount];

    for(int i = 0; i < nodes_amount; i++){
        neurons[i] = new Neuron();
    }
}

void MainWindow::learn_neurons(){
    double change_rate = 1;
    int sample;
    double min_distance;
    int nearest_node;
    double distance;

    for(int i = 0; i < learning_rounds; i++){
        //sample = 0; //it works :O, but give worse quality
        sample = rand() % image_pixels_amount;
        min_distance = neurons[0]->get_distance(&image_input_bits[sample * 4]);
        nearest_node = 0;

        for(int j = 1; j < nodes_amount; j++){
            distance = neurons[j]->get_distance(&image_input_bits[sample * 4]);
            if(distance <= min_distance){
                min_distance = distance;
                nearest_node = j;
            }
        }

        neurons[nearest_node]->update_weights(&image_input_bits[sample * 4], change_rate);

        if((nearest_node + 1) % nodes_horizontally != 0){
            neurons[nearest_node + 1]->update_weights(&image_input_bits[sample * 4], change_rate);
        }

        if(nearest_node % nodes_horizontally != 0){
            neurons[nearest_node - 1]->update_weights(&image_input_bits[sample * 4], change_rate);
        }

        if(nearest_node - nodes_horizontally >= 0){
            neurons[nearest_node - nodes_horizontally]->update_weights(&image_input_bits[sample * 4], change_rate);
        }

        if(nearest_node + nodes_horizontally < nodes_amount){
            neurons[nearest_node + nodes_horizontally]->update_weights(&image_input_bits[sample * 4], change_rate);
        }

        change_rate = 1 - static_cast<double>(i) / learning_rounds / 1.5;
    }
}

void MainWindow::repaint_image(){
    double min_distance;
    double distance;
    int nearest_node;

    for(int i = 0; i < image_pixels_amount; i++){
        min_distance = neurons[0]->get_distance(&image_input_bits[i * 4]);
        nearest_node = 0;

        for(int j = 1; j < nodes_amount; j++){
            distance = neurons[j]->get_distance(&image_input_bits[i * 4]);
            if(distance <= min_distance){
                min_distance = distance;
                nearest_node = j;
            }
        }

        image_output_bits[i * 4] = static_cast<unsigned char>(round(neurons[nearest_node]->weights[0]));
        image_output_bits[i * 4 + 1] = static_cast<unsigned char>(round(neurons[nearest_node]->weights[1]));
        image_output_bits[i * 4 + 2] = static_cast<unsigned char>(round(neurons[nearest_node]->weights[2]));
        image_output_bits[i * 4 + 3] = 255;
    }

    update();
}
