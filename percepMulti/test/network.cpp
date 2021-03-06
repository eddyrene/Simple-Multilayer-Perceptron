#include "network.h"

Network::Network()
{

}

Network::Network(int capas, int entradas, int ocultas, int salidas)
{
    numCapas= capas;
    numEntradas = entradas+1;
    numOcultas  = ocultas +1;
    numSalidas  = salidas +1;

    vectLayer = new vector< Layer* >();
    //capa de entrada
    Layer* e = new Layer(numEntradas);
    Layer* l = new Layer(numSalidas);
    vectLayer->push_back(e);
    VectOrders.push_back(numEntradas);
    //capas intermedias
    for(int i=1 ;i<capas-1; i++ )
    {
        Layer* m = new Layer(numOcultas);
        //cout<<"hidden"<<endl;
        vectLayer->push_back(m);
        VectOrders.push_back(numOcultas);
    }
    // capa salida
    vectLayer->push_back(l);
    VectOrders.push_back(numSalidas);
    fill();
    createWeights();
    ratioL=0.5;
}

void Network::fill()
{
     Layer* in  = vectLayer->at(0);
     //cout<<" s:"<< in->getVectNeuron()->size() << " ca: " << numEntradas<<endl;
     Layer* out = vectLayer->at(numCapas-1);

    for(int i =0; i< numEntradas ; i++)
    {
        Neuron* n = new Neuron(1);
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
            Neuron * n = new Neuron(1);
            vectLayer->at(i)->getVectNeuron()->at(j)=n;
          //  cout<<"%%%%%"<<vectLayer->at(i)->getVectNeuron()->at(j)->getVal()<<endl;
        }
    }
}

void Network::init(vector<double> input, vector<double> expected, double err)
{
    //vectLayer->at(0)->getVectNeuron()->at(0)->setVal(1);

    for(int i =0; i< numEntradas-1 ; i++)
    {
        vectLayer->at(0)->getVectNeuron()->at(i+1)->setVal(input[i]);
    }
    Y.clear();
   // Y.push_back(1);
    for(int i =0; i< numSalidas -1; i++)
    {
        //Y.push_back(expected);
        Y.push_back(expected[i]);
    }
    threshold=err;

}

void Network::init2(vector<double> input, double expected, double err)
{
    //vectLayer->at(0)->getVectNeuron()->at(0)->setVal(1);

    for(int i =0; i< numEntradas-1 ; i++)
    {
        vectLayer->at(0)->getVectNeuron()->at(i+1)->setVal(input[i]);
    }

    Y.clear();
   // Y.push_back(1);
    for(int i =0; i< numSalidas -1; i++)
    {
        Y.push_back(expected);
        //Y.push_back(expected[i]);
    }
    threshold=err;

}

void Network::printVector(string a, vector< double > t)
{
    cout<<a<<endl;
    
    for(auto y : t)
        cout<<" "<<y;
    cout<<endl;
    

    /*
    vector<double>::iterator it;
    for(it=t.begin();it<t.end();it++){
    	cout<<" "<<*it;
    }
    cout<<endl;
    */
    
}

void Network::printMat(string a, vector<vector<double> > M)
{
    cout<<a<<endl;
    for(int i =0 ; i< M.size();i++)
    {
        for(int j=0;j<M[i].size();j++)
            cout<<M[i][j]<<" ";
        cout<<endl;
    }
}
void Network::forward()
{
    mat * r;
    for(int i =0; i< vectLayer->size()-1; i++)
    {
        if(i!=0)
        {
            matrixtoVectNeuron(r,vectLayer->at(i)->getVectNeuron());
            vectLayer->at(i)->sigmod();
            // vectLayer->at(i)->binarizacion();
        }
        mat * neu=  vectNeurontoMatrix( vectLayer->at(i)->getVectNeuron());
        mat * wght =  vectLayer->at(i)->getMat();
        //cout<<"i ones \n"<<*wght<<endl;
       // cout<<"dimensiones A \n"<<neu->n_rows<<" "<<neu->n_cols<<endl;
       // cout<<"dimensiones B \n"<<wght->n_rows<<" "<<wght->n_cols<<endl;
        r = new mat((*neu)*(*wght));
      //  cout<<"\nla entrada \n "<<*neu<<"\n los pesos \n "<<*wght<<"\n resultado \n "<<*r<<endl;
    }
    matrixtoVectNeuron(r,vectLayer->at(vectLayer->size()-1)->getVectNeuron());
    vectLayer->at(vectLayer->size()-1)->sigmod();
    //vectLayer->at(vectLayer->size()-1)->binarizacion();
}
void Network::forward2()
{
    mat * r;
    for(int i =0; i< vectLayer->size()-1; i++)
    {
        if(i!=0)
        {
            matrixtoVectNeuron(r,vectLayer->at(i)->getVectNeuron());
            vectLayer->at(i)->sigmod();
            // vectLayer->at(i)->binarizacion();
        }
        mat * neu=  vectNeurontoMatrix( vectLayer->at(i)->getVectNeuron());
        mat * wght =  vectLayer->at(i)->getMat();
        //cout<<"i ones \n"<<*wght<<endl;
       // cout<<"dimensiones A \n"<<neu->n_rows<<" "<<neu->n_cols<<endl;
       // cout<<"dimensiones B \n"<<wght->n_rows<<" "<<wght->n_cols<<endl;
        r = new mat((*neu)*(*wght));
      //  cout<<"\nla entrada \n "<<*neu<<"\n los pesos \n "<<*wght<<"\n resultado \n "<<*r<<endl;
        //cout<<"\n resultado \n"<<*r<<endl;
    }
    matrixtoVectNeuron(r,vectLayer->at(vectLayer->size()-1)->getVectNeuron());
    vectLayer->at(vectLayer->size()-1)->sigmod2();
    //vectLayer->at(vectLayer->size()-1)->binarizacion();
}

void Network::backpropagation()
{
   // cout<<"\n \n backpropagation \n \n"<<endl;
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
          //  cout<<"E:  "<< vectLayer->at(i)->getMatError()<<"  "<<*E<<endl;
            //E->at(0)=0;
            for(int j =0 ;j < Y.size(); j++)
            {
              //  cout<<"y "<<Y[j]<<endl;
                //cout<<"s "<<(VN->at(j)->getVal())* VN->at(j)->getVal()*( 1 - VN->at(j)->getVal())<<endl;
                double a1= VN->at(j+1)->getVal();
                //cout<<"a1:      "<<a1<<endl;
                E->at(j)=(Y[j]-a1)*a1*(1-a1);
                //E->at(j)=(Y[j]-a1);
               // cout<<"Y"<<Y[j]<<endl;
            }
          //  cout<<"\n primer error calculado \n "<<*E<<endl;
        }
        else
        {
            //cout<<"else"<<endl;
            mat * E = vectLayer->at(i+1)->getMatError();
         //  cout<<"\n Este error debe coincidir con el anterior \n "<<*E<<endl;
            mat * weight = vectLayer->at(i)->getMat();
         //  cout<<"\n Los pesos actuales \n "<<*weight<<endl;
            mat * X = vectNeurontoMatrix( vectLayer->at(i)->getVectNeuron());
        //   cout<<"\n Las neruronas actuales \n "<<*X<<endl;
            //cout<<"X -- \n"<<(*X)<<" "<<trans(*X)<<" "<<X<<endl;
            //cout<<"E -- \n"<<*E<<" "<<E<<endl;
            //cout<<"W -- \n"<<*weight<<" "<<weight<<endl;
            *(weight) += ratioL*trans(*X)*(*E);
         //    cout<<"\n Los nuevos pesos \n "<<*weight<<endl;
            if(i!=0)
            {
               //cout<<"\n Los nuevos pesos \n "<<*weight<<endl;
                mat * R = new mat((*E)*(trans(*weight)));
              // cout<<"R --\n"<< *R<<R<<endl;
                mat * D = derVectNeuron(VN);
              //  cout<<"D --\n"<< *D<<D<<endl;
                mat * S  = new mat((*D)%(*R));
              // cout<<"S recortado -- \n"<< *S<<S<<endl;
                E=vectLayer->at(i)->getMatError();
                for(int j = 0 ; j<E->n_cols ; j++)
                    E->at(j)= S->at(j+1);
              // cout<<"\n EL nuevo error: \n "<<*E<<endl;
            }
        }
    }
}

void Network::createWeights()
{
    for(int i=0 ; i<vectLayer->size()-1 ; i++ )
    {
        vectLayer->at(i)->update(VectOrders[i],VectOrders[i+1]-1);
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
       // cout<<"Y"<<Y.at(i)<<" salida"<<vectLayer->at(numCapas-1)->getVectNeuron()->at(i+1)->getVal()<<endl;
        r += Y.at(i)-vectLayer->at(numCapas-1)->getVectNeuron()->at(i+1)->getVal();
        r= pow(r,2);
    }
    //printVector("La salida esperada es : \n ",Y);
   return r;
}

void Network::testSet(vector<double>  I, vector<double> O)
{

    for(int i =0; i< numEntradas-1 ; i++)
    {
        vectLayer->at(0)->getVectNeuron()->at(i+1)->setVal(I[i]);
    }
   /* cout<<"\n La entrada  \n "<<endl;
    for(auto k : *(vectLayer->at(0)->getVectNeuron()))
    {
        cout<<k->getVal()<<" ";
    }*/
    Y.clear();
    Y.push_back(1);
    for(int i =0; i< numSalidas -1; i++)
    {
        Y.push_back(O[i]);
    }

    mat * r;
    for(int i =0; i< vectLayer->size()-1; i++)
    {
        if(i!=0)
        {
            matrixtoVectNeuron(r,vectLayer->at(i)->getVectNeuron());
            vectLayer->at(i)->sigmod();
            // vectLayer->at(i)->binarizacion();
        }

        mat * neu=  vectNeurontoMatrix( vectLayer->at(i)->getVectNeuron());
        mat * wght =  vectLayer->at(i)->getMat();
        //cout<<"i ones \n"<<*wght<<endl;
       // cout<<"dimensiones A \n"<<neu->n_rows<<" "<<neu->n_cols<<endl;
       // cout<<"dimensiones B \n"<<wght->n_rows<<" "<<wght->n_cols<<endl;
        r = new mat((*neu)*(*wght));

       /// cout<<"\nla entrada \n "<<*neu<<"\n los pesos \n "<<*wght<<"\n resultado \n "<<*r<<endl;
    }
    matrixtoVectNeuron(r,vectLayer->at(vectLayer->size()-1)->getVectNeuron());
    int pos =vectLayer->size()-1;
    vectLayer->at(pos)->sigmod();

    cout<<"imprimiendo salida"<<endl;
    for(auto k : *(vectLayer->at(pos)->getVectNeuron()))
    {
        cout<<k->getVal()<<" ";
    }
    printVector("\n lo que debe salir \n",Y);
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
    mat * res;
    res= new mat(1,v->size(),fill::zeros);
    //cout<<"zeros \n "<<*res<<endl;
    //cout<<"tamano   "<<res->n_cols<<endl;
    for(int i =0 ; i< v->size(); i++)
    {
        double a = v->at(i)->getVal();
        //cout<< "a" << a <<endl;
        (*res)[i] =a;
        //cout<< "b" << (*res)[i] <<endl;
    }

    /*for(int i =0 ; i< v->size(); i++)
        cout<<(*res)[i]<<" ";*/

    //res->print();
    //cout<<*res<<endl;
    return res;
}
mat *Network::derVectNeuron(vector<Neuron *> *v)
{
    mat * result;
    result= new mat(1,v->size());
    //cout<<"tam del vector a derivar "<<v->size()<<endl;
    for(int i =0 ; i< result->size(); i++)
    {
        double a1 = v->at(i)->getVal();
        result->at(i)= (1-a1)*a1;
    }
    //cout<<"impriendo transformada \n "<<*result<<endl;
    //result
    return result;
}

void Network::matrixtoVectNeuron(mat *c, vector<Neuron *> * v)
{
    //cout<<"rango \n"<<c->n_cols<<"vector"<<v->size()<<endl;
    for(int i =0; i< c->n_cols; i++)
    {
            v->at(i+1)->setVal(c->at((i)));
    }
    //cout<<"valores actualizados"<<endl;
}
