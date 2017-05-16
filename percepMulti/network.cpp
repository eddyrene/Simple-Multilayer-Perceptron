#include "network.h"

Network::Network()
{

}

Network::Network(int capas, int entradas, int ocultas, int salidas)
{
    numCapas= capas;
    numOcultas= ocultas;
    numEntradas= entradas;
    numSalidas= salidas;
    vectLayer = new vector<Layer *>();
    //capa de entrada
    Layer * e = new Layer(entradas);
    Layer * l =new Layer(salidas);
    vectLayer->push_back(e);
    VectOrders.push_back(entradas);
    //capas intermedias
    for(int i =1 ;i<capas-1; i++ )
    {
        Layer * m = new Layer(ocultas);
        //cout<<"hidden"<<endl;
        vectLayer->push_back(m);
        VectOrders.push_back(ocultas);
    }
    // capa salida
    vectLayer->push_back(l);
    VectOrders.push_back(salidas);
    fill();
    createWeights();
    ratioL=0.5;
}

void Network::fill()
{
     Layer * in= vectLayer->at(0);
     Layer * out= vectLayer->at(numCapas-1);
    for(int i =0; i< numEntradas ; i++)
    {
        Neuron * n = new Neuron(rand() % 2);
        in->getVectNeuron()->at(i)= n;
        //cout<<"##"<<in->getVectNeuron()->at(i)->getVal()<<endl;
    }
    for(int i =0; i< numSalidas ; i++)
    {
        Neuron * n = new Neuron(rand() % 2);
        out->getVectNeuron()->at(i)=n;
       // cout<<"**"<<out->getVectNeuron()->at(i)->getVal()<<endl;
    }
    for(int i =1 ; i< numCapas-1 ; i++)
    {
       // cout<<"capa: "<<i<<endl;
        //Layer * hidden = vectLayer->at(i);
        for(int j=0; j < numOcultas ; j++)
        {
            Neuron * n = new Neuron(0);
            vectLayer->at(i)->getVectNeuron()->at(j)=n;
          //  cout<<"%%%%%"<<vectLayer->at(i)->getVectNeuron()->at(j)->getVal()<<endl;
        }
    }
}

void Network::init(vector<double> input, vector<double> expected, double err)
{
    Y.clear();
    for(int i =0; i< numEntradas ; i++)
    {
        vectLayer->at(0)->getVectNeuron()->at(i)->setVal(input[i]);
    }

    for(int i =0; i< numSalidas ; i++)
    {
        Y.push_back(expected[i]);
    }
    threshold=err;

}


void Network::printVector(string a, vector<double> t)
{
    cout<<a<<endl;
    for(auto y : t)
        cout<<" "<<y<<endl;
}

void Network::forward()
{
    cout<<"\n \n  ############### Forward ##############   \n \n"<<endl;
    mat * r;
    for(int i =0; i< vectLayer->size()-1; i++)
    {
        if(i!=0)
        {
            matrixtoVectNeuron(r,vectLayer->at(i)->getVectNeuron());
            vectLayer->at(i)->sigmod();
            cout<<"\n se activo"<<endl;
        }

        mat * neu=  vectNeurontoMatrix( vectLayer->at(i)->getVectNeuron());
        mat * wght =  vectLayer->at(i)->getMat();
        //cout<<"i ones \n"<<*wght<<endl;
        //cout<<"dimensiones A"<<neu->n_rows<<" "<<neu->n_cols<<endl;
        //cout<<"dimensiones B"<<wght->n_rows<<" "<<wght->n_cols<<endl;
        r = new mat((*neu)*(*wght));
       // cout<<"\nla entrada \n "<<*neu<<"\n los pesos \n "<<*wght<<"\n resultado \n "<<*r<<endl;
    }

    matrixtoVectNeuron(r,vectLayer->at(vectLayer->size()-1)->getVectNeuron());
    vectLayer->at(vectLayer->size()-1)->sigmod();
    cout<<"\n se activo"<<endl;

}

void Network::backpropagation()
{

    cout<<"\n \n  %%%%%%%%%%%%%%%% backpropagation %%%%%%%%%%%%%%%%\n \n"<<endl;
    for(int i =numCapas-1; i>= 0;i--)
    {
        vector<Neuron *> * VN= vectLayer->at(i)->getVectNeuron();
        //E = new mat(1,VN->size());
        //cout<<"i->: "<<i<<endl;
        if(i==numCapas-1 )
        {
            //cout<<"ggggggg"<<endl;
            mat * E = vectLayer->at(i)->getMatError();
            //cout<<"llllllll"<<endl;
            //cout<<"size 1 "<<Y.size()<<endl;
            //cout<<"size 2 "<<VN->size()<<endl;
            //cout<<"E"<< vectLayer->at(i)->getMatError()<<"  "<<*E<<endl;
            for(int j =0 ;j < VN->size(); j++)
            {
              //  cout<<"y "<<Y[j]<<endl;
                //cout<<"s "<<(VN->at(j)->getVal())* VN->at(j)->getVal()*( 1 - VN->at(j)->getVal())<<endl;
                E->at(j)=(Y[j]-(VN->at(j)->getVal())* VN->at(j)->getVal()*( 1 - VN->at(j)->getVal()));
                //cout<<"tttttttttttt"<<endl;
            }
          //  cout<<"\n primer error calculado \n "<<*E<<endl;

        }
        else
        {
            //cout<<"else"<<endl;
            mat * E = vectLayer->at(i+1)->getMatError();
          // cout<<"\n Este error debe coincidir con el anterior \n "<<*E<<endl;
            mat * weight = vectLayer->at(i)->getMat();
          // cout<<"\n Los pesos actuales \n "<<*weight<<endl;
            mat * X = vectNeurontoMatrix( vectLayer->at(i)->getVectNeuron());
         //  cout<<"\n Las neruronas actuales \n "<<*X<<endl;
            //cout<<"X -- \n"<<(*X)<<" "<<trans(*X)<<" "<<X<<endl;
            //cout<<"E -- \n"<<*E<<" "<<E<<endl;
            //cout<<"W -- \n"<<*weight<<" "<<weight<<endl;
            *(weight) += ratioL*trans(*X)*(*E);
         //  cout<<"\n Los nuevos pesos \n "<<*weight<<endl;
            mat * R = new mat((*E)*(trans(*weight)));
            //cout<<"R --\n"<< *R<<R<<endl;
            mat * D = derVectNeuron(VN);
            //cout<<"D --\n"<< *D<<D<<endl;
            mat * S  = new mat((*D)%(*R));
            //cout<<"S -- \n"<< *S<<S<<endl;
            vectLayer->at(i)->setMatError(S);
            E=S;
            cout<<"\n EL nuevo error: \n "<<*E<<endl;

        }
    }
}

void Network::createWeights()
{
    for(int i=0 ; i<vectLayer->size()-1 ; i++ )
    {
        vectLayer->at(i)->update(VectOrders[i],VectOrders[i+1]);
    }
}

void Network::printWeight()
{
    for(int i=0 ; i<vectLayer->size()-1 ; i++ )
    {
        cout<<"\n pesitos \n "<<*(vectLayer->at(i)->getMat())<<endl;
    }
}

double Network::sumSquareError()
{
    double r=0;
    for(int i =0;i< Y.size();i++ )
    {
        r += pow(Y.at(i)- vectLayer->at(numCapas-1)->getVectNeuron()->at(i)->getVal(),2);
    }
    return r/2;
}
void Network::printAll()
{
    cout<<"imprimiendo todo "<<endl;
    for(int i=0 ; i<vectLayer->size(); i++ )
    {
        for(int j=0; j< vectLayer->at(i)->getVectNeuron()->size(); j++)
        {
            cout<<vectLayer->at(i)->getVectNeuron()->at(j)->getVal()<<endl;
        }
        cout<<endl;
    }
}
vector<double> Network::getVectorOrders()
{
    return VectOrders;
}

vector<Layer*> * Network::getVectorLayers()
{
    return vectLayer;
}

mat *Network::vectNeurontoMatrix(vector<Neuron *> *v)
{
    mat * result;
    result= new mat(1,v->size());
    for(int i =0 ; i< v->size(); i++)
    {
        result->at(i) = v->at(i)->getVal();
    }
    //cout<<"impriendo transformada \n "<<*result<<endl;
    return result;
}
mat *Network::derVectNeuron(vector<Neuron *> *v)
{
    mat * result;
    result= new mat(1,v->size());
    for(int i =0 ; i< v->size(); i++)
    {
        double a1 = v->at(i)->getVal();
        result->at(i) = (1-a1)*a1;
    }
    //cout<<"impriendo transformada \n "<<*result<<endl;
    return result;
}

void Network::matrixtoVectNeuron(mat *c, vector<Neuron *> * v)
{
    //cout<<"rango \n"<<c->n_cols<<"vector"<<v->size()<<endl;
    for(int i =0; i< c->n_cols; i++)
    {
            v->at(i)->setVal(c->at((i)));
    }
    //cout<<"valores actualizados"<<endl;
}
