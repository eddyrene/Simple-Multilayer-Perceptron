#ifndef NETWORK_H
#define NETWORK_H
#include "layer.h"
#include "weight.h"
#include <cmath>

class Network
{
private:
    vector<Layer*> * vectLayer;
    Weight * vectWeight;
    int numCapas;
    int numOcultas, numSalidas, numEntradas;
    vector<double> VectOrders;
    vector<double> Y;
    //vector<double> E;
    double threshold;
    double ratioL;

public:
    Network();
    Network(int capas, int entradas, int tamcapa,  int salida );
    void fill();
    void init(vector<double> input, double expected , double err);
    mat * derVectNeuron(vector<Neuron *> * v );
    void printVector(string a, vector<double> t);
    void printMat(string a, vector<vector<double> > M);
    void forward();
    void forwardBias();
    void backpropagation();
    void backpropagationBias();
    void createWeights();
    void printAll();
    vector<double> getVectorOrders();
    vector<Layer*> * getVectorLayers();
    mat * vectNeurontoMatrix( vector<Neuron *> * v );
    void matrixtoVectNeuron(mat *c, vector<Neuron *> * v);
    void printWeight();
    double sumSquareError();
    double getThreshold(){return threshold;}
    int getNumEntradas(){return numEntradas;}
    int getNumSalidas(){return numSalidas;}
    void testSet(vector<double>  I, vector<double> O);
};

#endif // NETWORK_H
