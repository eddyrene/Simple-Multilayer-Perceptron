#include <QCoreApplication>
#include "network.h"
#include <fstream>

int main()
{
    //QCoreApplication a(argc, argv);
/*
    mat * A= new mat(1,5,fill::ones);
    *A *= 3;

    mat A(1,5,fill::ones);
    mat B = A;
    mat C = B*A


    mat * C = new mat(1,5,fill::ones);
    *C *= 4;
    mat * D = new mat((*A) % (*C));
    cout<<*(D)<<endl;
*/

    Network * my_net = new Network(3,7,5,4); // numcapas, numInput, numHidden, numOutput
    my_net->printVector("imprimiendo pesos", my_net->getVectorOrders());

    int Es =10;

    vector< vector<double >> imputs, outputs;

    imputs.resize(Es);
    for(int i = 0 ; i< Es ;i++)
        imputs[i].resize(my_net->getNumEntradas());

    outputs.resize(Es);
    for(int i = 0 ; i< Es ;i++)
        outputs[i].resize(my_net->getNumSalidas());

    cout<<"imput"<<imputs.size()<<endl;
    cout<<"output"<<outputs.size()<<endl;
    string sin, sout ;
    ifstream file("numeros.txt");
    int m=0;
    while(!file.eof())
    {
        file>>sin>>sout;
        if(sin=="") break;
        for(int i =0 ;i< sin.size();i++)
        {
            imputs[m][i]=sin[i]-'0';
        }
        for(int i =0 ;i< sout.size();i++)
        {
            outputs[m][i]=sout[i]-'0';
        }
        m++;
    }


    for(int i =0 ; i< imputs.size(); i++)
    {
        for(int j =0 ;j< imputs[i].size();j++)
        {
            cout<<imputs[i][j];
        }
        cout<<endl;
    }

    cout <<endl ;
    for(int i =0 ; i< outputs.size(); i++)
    {
        for(int j =0 ;j< outputs[i].size();j++)
        {
            cout<<outputs[i][j];
        }
        cout<<endl;
    }


    cout<<"leyo"<<endl;
    //int i=1;

    for(int i=0 ;i<Es; i++)
    {

        my_net->init(imputs[i],outputs[i], 0.01);
        double delta=2;
        int era=0;
        cout<<"threashold: "<<my_net->getThreshold()<<endl;
        my_net->printVector("\n entrada \n ", imputs[i]);
        my_net->printVector("\ Valor esperado \n", outputs[i]);
        int t=0;
        while(my_net->getThreshold() < delta)
        {
            t++;
            cout<<"entrada:  "<<i<<"*  ***  era ***  "<<t<<endl;
            my_net->forward();
            delta=my_net->sumSquareError();
            cout<<"el error es :"<<delta<<endl;
            if(delta>my_net->getThreshold())
                my_net->backpropagation();

        }
     }

    /**/
    return 0;
}


/*    vector<double> x;
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
    y.push_back(1);*/
