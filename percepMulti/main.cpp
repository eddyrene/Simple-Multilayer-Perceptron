#include <QCoreApplication>
#include "network.h"
#include <algorithm>

using namespace std;

int main()
{
    Network * my_net = new Network(3,4,8,3); // numcapas, numInput, numHidden, numOutput
    my_net->printVector("imprimiendo pesos", my_net->getVectorOrders());
    vector< vector<double >> inputs, outputs;
    int Es=90;
    my_net->loadDataFlowers("irisN.txt", Es, inputs, outputs);
    vector<double> FinalErrors;
    int times=0;
    bool flag =true;
    while((flag==true) && (times <10000))
    {
        cout<<"###########################"<< times <<"#################################"""<<endl;
        FinalErrors.clear();
        int era=0;
        double delta=1000;
        for(int i=0 ;i<Es; i++)
        {
            double t=0.00001;
            my_net->init(inputs[i],outputs[i], t);
            //cout<<"entrada:  "<< i << "   ****  era ***  "<<era<<endl;
            my_net->forward();
            delta=my_net->sumSquareError();
            //cout<<"SumsquareError de la capa:"<<delta<<endl;
            if(delta>0.000001)
                my_net->backpropagation();
            //my_net->forward();
            //cout<<"i "<<i<<" u  "<<delta<<endl;
            FinalErrors.push_back(delta);
            era++;
        }
        double sum=0;
        for(int qw =0; qw<FinalErrors.size();qw++)
        {
            // cout<<"  -  "<<FinalErrors[qw]<<endl;
            sum+=FinalErrors[qw];
        }
        //cout<<" solo la sumatoria  "<< sum <<" El tamño del vector"<<FinalErrors.size()<<endl;
        sum = sum / FinalErrors.size();
        if(sum < 0.001)
            flag=false;
        cout<<"*********acumulado MENOR AL FLAG **** \n "<<sum<<endl;
        times++;
   }
    cout<<"%%%%%%%%%%%%%%%%%% TEST %%%%%%%%%%%%%%"<<endl;
    int Test =60;
    vector< vector<double >> I, O;
    my_net->loadDataFlowers("testIrisN.txt", Test, I, O);
    my_net->printMat("\n Entrada: \n", I);
    my_net->printMat("\n Salidas: \n", O);
    for(int i=0 ;i<Test; i++)
    {
         my_net->testSet(I[i],O[i]);
    }
}


// ************************************* XOR *******************************************

/* Network * my_net = new Network(3,2,2,1); // numcapas, numInput, numHidden, numOutput
 my_net->printVector("imprimiendo pesos", my_net->getVectorOrders());
 vector< vector<double >> imputs;
 vector<double > outputs;

 int Es=4;
 imputs.resize(Es);
 for(int i = 0 ; i< Es ;i++)
     imputs[i].resize(my_net->getNumEntradas()-1);

 imputs[0][0]=1;
 imputs[0][1]=1;
 imputs[1][0]=0;
 imputs[1][1]=1;
 imputs[2][0]=1;
 imputs[2][1]=0;
 imputs[3][0]=0;
 imputs[3][1]=0;

 outputs.push_back(0);
 outputs.push_back(1);
 outputs.push_back(1);
 outputs.push_back(0);


 my_net->printMat("\n Training: \n", imputs);
 my_net->printVector("\n Expected: \n", outputs);
 cout<<"leyo"<<endl;
 vector<double> FinalErrors;

 int times=0;
 bool flag =true;
 double sum=0;
while(flag)
{
    cout<<"###########################"<< times <<"#################################"""<<endl;
    for(int i=0 ;i<Es; i++)
     {
         //int i =2 ;
         my_net->init(imputs[i],outputs[i], 0.1);
         double delta=2;
         int era=0;
         cout<<"threashold: "<<my_net->getThreshold()<<endl;
         my_net->printVector("\n entrada \n ",imputs[i]);
         cout<<"\n Valor esperado \n" << outputs[i]<<endl;
         {
             for(int t =0 ; t<1;t++)
             {
                 era++;
                 cout<<"entrada:  "<< i << "   ****  era ***  "<<era<<endl;
                 my_net->forward();
                 //cout<<"el error es :"<<delta<<endl;
                 delta=my_net->sumSquareError();
                 //if(delta>my_net->getThreshold())
                 my_net->backpropagation();
                 //my_net->forward();
                 FinalErrors.push_back(delta);
                 cout<<"delta"<<delta;
             }
         }
     }
     //cout<<"Final"<<endl;
   //  cout<<"esta entrando.............           "<<FinalErrors.size()<<endl;
     for(int qw =0; qw<FinalErrors.size();qw++)
     {
        // cout<<"  -  "<<FinalErrors[qw]<<endl;
         sum+=FinalErrors[qw];
     }
     //cout<<"====primer sum"<< sum <<endl;
     sum = sum / FinalErrors.size();
     if(sum < 0.1)
         flag=false;
     cout<<"*********acumulado**** \n "<<sum<<endl;
     times++;
 }
cout<<"%%%%%%%%%%%%%%  Probando %%%%%%%%%%%%%%"<<endl;

for(int i=0 ;i<4; i++)
{
        //my_net->testSet(I[0],O[0]);
    my_net->init(imputs[i],outputs[i], 0.01);
    my_net->forward();
    cout<<"\n Espeardo:     "<< outputs[i]<<endl;
}*/


/************ MAtriz Armadillo ************************/

//QCoreApplication a(argc, argv);
/*
mat * A= new mat(1,5,fill::ones);
*A *= 3;


mat * C = new mat(1,5,fill::ones);
*C *= 4;
mat * D = new mat((*A) % (*C));
cout<<*(D)<<endl;
*/


