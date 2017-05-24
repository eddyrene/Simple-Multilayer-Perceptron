//#include <QCoreApplication>
#include "network.h"
#include "layer.h"
#include <algorithm>

using namespace std;

int main()
{
   
   Network* my_net = new Network(5,784,15,10); // numcapas, numInput, numHidden, numOutput
   my_net->printVector("imprimiendo pesos", my_net->getVectorOrders());
   //vector< vector<double >> imputs, outputs;

   /*
   int Es =100;
   vector< vector<double > > inputs, outputs;

   inputs.resize(Es);
   for(int i = 0 ; i< Es ;i++)
       inputs[i].resize(my_net->getNumEntradas()-1);
   outputs.resize(Es);
   for(int i = 0 ; i< Es ;i++)
       outputs[i].resize(my_net->getNumSalidas()-1);
   for(int i=0;i<outputs.size();i++)
       for(int j=0; j<outputs[i].size();j++)
       {
           outputs[i][j]=0;
       }
   cout<<"imput  "<<inputs.size()<<endl;
   cout<<"output  "<<outputs.size()<<endl;

   ifstream file("dataset/training2.txt");
   int m=0;
   string line;

   while(getline(file,line) )
   {
       int n=0;
       bool flag= false;
       std::stringstream   linestream(line);
       std::string         value;
       //cout<<"entro"<<endl;
       while(getline(linestream,value,','))
       {
           double v = atoi(value.c_str());
           double vv=v/255;
           //double vv= v;
            if(!flag)
            {
                outputs[m][v]=1;
                flag=true;
            }
            else
            {
                cout<<"float "<<vv<<endl;
                inputs[m][n]=vv;
                n++;
            }

       }
      // std::cout << "Line Finished" << std::endl;
    m++;
   }
   my_net->printMat("\n Training: \n", inputs);
   my_net->printMat("\n Expected: \n", outputs);
   cout<<"leyo"<<endl;
   vector<double> FinalErrors;
   int times=0;
   bool flag =true;

  while(flag)
  {
     // cout<<"###########################"<< times <<"#################################"""<<endl;
      FinalErrors.clear();
      int era=0;
      for(int i=0 ;i<Es; i++)
       {
           double t=0.1;
           my_net->init(inputs[i],outputs[i], t);
           double delta=2;

          // cout<<"threashold: "<<my_net->getThreshold()<<endl;
           //my_net->printVector("\n entrada primera segunda \n ",inputs[i]);
         //  cout<<"\n Valor esperado \n" << outputs[i]<<endl;

                   //cout<<"entrada:  "<< i << "   ****  era ***  "<<era<<endl;
                   my_net->forward();
                   delta=my_net->sumSquareError();
                   if(delta>0.1)
                       my_net->backpropagation();
                   //cout<<"el error es :"<<delta/2<<endl;
                   //my_net->forward();
                   //cout<<"i "<<i<<" u  "<<delta<<endl;
                   FinalErrors.push_back(delta);
                   era++;
                   //cout<<"delta"<<delta;
       }
       //cout<<"Final"<<endl;
     // cout<<"errores calculados esta entrando.............           "<<FinalErrors.size()<<endl;
       double sum=0;
      for(int qw =0; qw<FinalErrors.size();qw++)
       {
          // cout<<"  -  "<<FinalErrors[qw]<<endl;
           sum+=FinalErrors[qw];
       }
       //cout<<"====primer sum"<< sum <<endl;
       sum = sum / FinalErrors.size();
       if(sum < 0.5)
           flag=false;
       cout<<"*********acumulado MENOR AL FLAG **** \n "<<sum<<endl;
       times++;
   }
    cout<<"%%%%%%%%%%%%%%%%%%  Probando %%%%%%%%%%%%%%"<<endl;

   int Test =10;
   vector< vector<double > > I, O;

   I.resize(Test);
   for(int i = 0 ; i< Test ;i++)
       I[i].resize(my_net->getNumEntradas()-1);

   O.resize(Test);
   for(int i = 0 ; i< Test ;i++)
       O[i].resize(my_net->getNumSalidas()-1);

  // cout<<"imput de prueba "<<I.size()<<endl;
  // cout<<"output de prueba "<<O.size()<<endl;

   string line1;
   ifstream file1("dataset/test2.txt");
   int mm=0;
   while(getline(file1,line1) )
   {
       int nn=0;
       bool flag= false;
       std::stringstream   linestream(line1);
       std::string         value;
       //cout<<"entro"<<endl;
       while(getline(linestream,value,','))
       {
           double v = atoi(value.c_str());
           double vv=v/255;
            if(!flag)
            {
                O[mm][v]=1;
                flag=true;
            }
            else
            {
                I[mm][nn]=vv;
                nn++;
            }
       }
       //std::cout << "Line Finished" << std::endl;
    mm++;
   }
    //my_net->printMat("\n Entrada: \n", I);
    my_net->printMat("\n Salidas: \n", O);
   for(int i=0 ;i<Test; i++)
   {
        // my_net->testSet(I[0],O[0]);
      my_net->init(I[i],O[i], 0.1);
      my_net->forward2();
       //my_net->forward();
       //cout<<"\n Espeardo:     "<< [i]<<endl;
   }
   */
  // my_net->printMat("\n Entrada: \n", I);
  // my_net->printMat("\n Entrada: \n", O);

   return 0;
}
    
