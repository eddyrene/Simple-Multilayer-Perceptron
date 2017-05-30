#ifndef LAYER_H
#define LAYER_H
#include <vector>

#include<armadillo>
#include<iostream>

using namespace std;
using namespace arma;
class Layer
{
    private:
        //vector<Neuron *> * vectNeuron;
        mat * vectdNeuron;
        mat * pMat;
        int size;
        int mfil,mcol;
        mat * matError;
        mat * weightBias;
    public:
        Layer();
        Layer(int tam);
        int getSize();
        void sigmod();
        void sigmod2();
        mat * getMat();
        void setMat(mat &m);
        void  update(int a , int b);
        mat * getMatError();
        void setMatError(mat *m);
        mat * getWeightBias();
        void binarizacion();
        mat * getVectNeuron();
};

#endif // LAYER_H
