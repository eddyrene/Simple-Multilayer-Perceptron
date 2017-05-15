#include <QCoreApplication>
#include "network.h"

int main()
{
    //QCoreApplication a(argc, argv);
/*
    mat * A= new mat(1,5,fill::ones);
    *A *= 3;


    mat * C = new mat(1,5,fill::ones);
    *C *= 4;
    mat * D = new mat((*A) % (*C));
    cout<<*(D)<<endl;
*/

    Network * my_net = new Network(3,7,5,4); // numcapas, numInput, numHidden, numOutput
    my_net->printVector("imprimiendo pesos", my_net->getVectorOrders());
    //  my_net->printWeight();
    //my_net->printAll();
    vector<double> x;
    x.push_back(0);
    x.push_back(1);
    x.push_back(1);
    x.push_back(1);
    x.push_back(0);
    x.push_back(1);
    x.push_back(1);

    vector<double> y;
    y.push_back(0);
    y.push_back(1);
    y.push_back(0);
    y.push_back(1);

    my_net->init(x,y,0.1);

    double delta=10;
    int era=0;
    cout<<"threashold: "<<my_net->getThreshold()<<endl;
    my_net->printVector("\n entrada \n ", x);
    my_net->printVector("\ Valor esperado \n", y);

    //while(my_net->getThreshold() <  delta)
    int t=0;
    while(t<5)
    {
        t++;
        cout<<"*******  era  *****"<<t<<endl;
        my_net->forward();
        //cout<<"++++++++++++++++"<<endl;
        delta=my_net->sumSquareError();
        my_net->backpropagation();

        my_net->forward();

        cout<<"el error es :"<<delta<<endl;
    }
    return 0;
}

