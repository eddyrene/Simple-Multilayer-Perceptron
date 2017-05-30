#include "layer.h"

Layer::Layer()
{
       vectdNeuron = NULL;
}

Layer::Layer(int tam)
{
    //pWeight= new Weight();
    size=tam;
    //vectNeuron = new vector<Neuron *> ();
    vectdNeuron = new mat(1,size,fill::ones);
    //cout<<"tam : "<<tam<<endl;
    //vectNeuron->resize(size);
    pMat = new mat(0,0,fill::randu);
    mcol=mfil=0;
    matError = new mat(1,size-1,fill::zeros);
    weightBias = new mat(1,size,fill::zeros);
}

int Layer::getSize()
{
    return size;
}

void Layer::sigmod()
{
    //cout<<"\n se activo \n "<<endl;
    vectdNeuron->at(0) =1;
    for(int i=1 ; i<vectdNeuron->n_cols;i++)
    {
        float exp_value;
        float return_value;
        double x = vectdNeuron->at(i);
        exp_value = exp((double) -x);
        return_value = 1 / (1 + exp_value);
        vectdNeuron->at(i) = return_value;
    }
}
void Layer::binarizacion()
{
    for(int i =0; i<vectdNeuron->n_cols;i++ )
    {
        double x = vectdNeuron->at(i);
        if(x>= 0.5)
            vectdNeuron->at(i)=1;
        else
            vectdNeuron->at(i)=0;
        cout<<vectdNeuron->at(i)<<"  ";
    }
    cout<<"se binarizo"<<endl;
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
    pMat = new mat(mfil,mcol,fill::randu);
}

mat *Layer::getMatError()
{
    return matError;
}

void Layer::setMatError(mat * m)
{
    matError = m;
}

mat *Layer::getWeightBias()
{
    return weightBias;
}

mat *Layer::getVectNeuron()
{
    return vectdNeuron;
}
