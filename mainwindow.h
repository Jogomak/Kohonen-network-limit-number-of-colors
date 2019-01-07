#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"
#include "neuron.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int nodes_horizontally;
    int nodes_vertically;
    int nodes_amount;
    int image_width;
    int image_height;
    int image_pixels_amount;
    int learning_rounds;

    QImage *image_input;
    QImage *image_output;

    unsigned char *image_input_bits;
    unsigned char *image_output_bits;

    Neuron **neurons;

    void initialize_neurons();
    void learn_neurons();
    void repaint_image();

private slots:
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
