#include <QCoreApplication>
#include "network.h"
#include <algorithm>

using namespace std;

int main()
{
   Network * my_net = new Network(5,784,15,10); // numcapas, numInput, numHidden, numOutput
   my_net->printVector("imprimiendo pesos", my_net->getVectorOrders());
   //vector< vector<double >> imputs, outputs;

   int Es =100;
   vector< vector<double >> inputs, outputs;

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

   ifstream file("training2.txt");
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
   vector< vector<double >> I, O;

   I.resize(Test);
   for(int i = 0 ; i< Test ;i++)
       I[i].resize(my_net->getNumEntradas()-1);

   O.resize(Test);
   for(int i = 0 ; i< Test ;i++)
       O[i].resize(my_net->getNumSalidas()-1);

  // cout<<"imput de prueba "<<I.size()<<endl;
  // cout<<"output de prueba "<<O.size()<<endl;

   string line1;
   ifstream file1("test2.txt");
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

  // my_net->printMat("\n Entrada: \n", I);
  // my_net->printMat("\n Entrada: \n", O);

}
    /*int Es =120;
    vector< vector<double >> inputs, outputs;

    inputs.resize(Es);
    for(int i = 0 ; i< Es ;i++)
        inputs[i].resize(my_net->getNumEntradas()-1);

    outputs.resize(Es);
    for(int i = 0 ; i< Es ;i++)
        outputs[i].resize(my_net->getNumSalidas()-1);

    cout<<"imput"<<inputs.size()<<endl;
    cout<<"output"<<outputs.size()<<endl;
    float e1, e2,e3,e4;
    string s1;

    ifstream file("iris.txt");
    int m=0;
    while(!file.eof())
    {
        file>>e1>>e2>>e3>>e4>>s1;
        if(s1=="") break;
        inputs[m][0]= e1;
        inputs[m][1]= e2;
        inputs[m][2]= e3;
        inputs[m][3]= e4;
        for(int i =0 ;i<s1.size();i++)
        {
            outputs[m][i]=s1[i]-'0';
        }
        m++;
        //cout<<m<<endl;
    }
    my_net->printMat("\n Training: \n", inputs);
    my_net->printMat("\n Expected: \n", outputs);
    cout<<"leyo"<<endl;
    vector<double> FinalErrors;

    int times=0;
   while(times<100)
   {
       cout<<"###########################"<< times <<"#################################"""<<endl;
        for(int i=0 ;i<Es; i++)
        {
            my_net->init(inputs[i],outputs[i], 0.01);
            double delta=2;
            int era=0;
            cout<<"threashold: "<<my_net->getThreshold()<<endl;
            my_net->printVector("\n entrada \n ",inputs[i]);
            my_net->printVector("\ Valor esperado \n", outputs[i]);
            {
                for(int t =0 ; t<1;t++)
                {
                    era++;
                    cout<<"entrada:  "<< i << "   ****  era ***  "<<era<<endl;
                    my_net->forward();
                    delta=my_net->sumSquareError();
                    //cout<<"el error es :"<<delta<<endl;
                    FinalErrors.push_back(delta);
                    if(delta>my_net->getThreshold())
                        my_net->backpropagation();
                }
            }
        }
        times++;
    }
    cout<<"%%%%%%%%%%%%%%  Probando %%%%%%%%%%%%%%"<<endl;

    int Test =30;
    vector< vector<double >> I, O;

    I.resize(Test);
    for(int i = 0 ; i< Test ;i++)
        I[i].resize(my_net->getNumEntradas()-1);

    O.resize(Test);
    for(int i = 0 ; i< Test ;i++)
        O[i].resize(my_net->getNumSalidas()-1);

    cout<<"imput de prueba "<<I.size()<<endl;
    cout<<"output de prueba "<<O.size()<<endl;


    float e11, e12,e13,e14;
    string s11;

    ifstream file1("test.txt");
    int mm=0;
    while(!file1.eof())
    {
        file1>>e11>>e12>>e13>>e14>>s11;
        if(s11=="") break;
        I[mm][0]= e11;
        I[mm][1]= e12;
        I[mm][2]= e13;
        I[mm][3]= e14;
        for(int i =0 ;i<s11.size();i++)
        {
            O[mm][i]=s11[i]-'0';
        }
        mm++;
      //cout<<m<<endl;
    }
    my_net->printMat("\n Entrada: \n", I);
    my_net->printMat("\n Entrada: \n", O);

   // for(int i=0 ;i<Test; i++)
   // {
        //my_net->testSet(I[0],O[0]);
     my_net->init(I[20],O[20], 0.01);
    my_net->forward();
        //my_net->printMat("\n Espeard: \n", O[i]);
  //  }
    return 0;
}
*/
/*string sin, sout ;
ifstream file("numeros.txt");
int m=0;
while(!file.eof())
{
    file>>sin>>sout;
    if(sin=="") break;
    for(int i =0 ;i< sin.size();i++)
    {
        inputs[m][i]=sin[i]-'0';
    }
    for(int i =0 ;i< sout.size();i++)
    {
        outputs[m][i]=sout[i]-'0';
    }
    m++;
}*/




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


