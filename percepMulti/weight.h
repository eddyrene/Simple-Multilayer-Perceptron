#ifndef WEIGHT_H
#define WEIGHT_H
#include<armadillo>
#include<iostream>

using namespace std;
using namespace arma;

class Weight
{
private:
    int fil;
    int col;
    mat * matrix;
public:
    Weight();
   /* Weight(int f, int c);
    int getSize();
    vector<double> * getVectWeight();*/
};

#endif // WEIGHT_H
