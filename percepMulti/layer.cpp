#include "layer.h"

Layer::Layer()
{
       vectNeuron = NULL;
}

Layer::Layer(int tam)
{
    //pWeight= new Weight();
    size=tam;
    vectNeuron = new vector<Neuron *> ();
    //cout<<"tam : "<<tam<<endl;
    vectNeuron->resize(size);
    pMat = new mat(0,0,fill::zeros);
    mcol=mfil=0;
    matError = new mat(1,size,fill::zeros);
}

int Layer::getSize()
{
    return size;
}

void Layer::sigmod()
{
    for(auto n: *vectNeuron)
    {
        float exp_value;
        float return_value;

           double x = n->getVal();
            exp_value = exp((double) -x);
            /*** Final sigmoid value ***/
            return_value = 1 / (1 + exp_value);
            n->setVal(return_value);
            cout<<n->getVal()<<" "<<endl;
    }
}

mat * Layer::getMat()
{
    return pMat;
}

void Layer::setMat(mat &m)
{
    cout<<"se deberia guardar"<<endl;
    pMat= &m;
    cout<<&m<<endl;
}

void Layer::update(int a, int b)
{
    mfil=a; mcol=b;
    pMat = new mat(mfil,mcol,fill::zeros);
}

mat *Layer::getMatError()
{
    return matError;
}

void Layer::setMatError(mat * m)
{
    matError = m;
}
vector<Neuron *> *Layer::getVectNeuron()
{
    return vectNeuron;
}
