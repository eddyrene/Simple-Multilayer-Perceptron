#include <iostream>
#include <vector>
#include <string>


using namespace std;

int num_entradas= 4;

int correct( float a[], float b[])
{
	for (int j=0; j< num_entradas;j++)
		if(a[j]!= b[j])
			return j;
		return -1;
}

int main()
{

	
	int elem_entrada = 3;
	float t_apre = 0.5;

	float  pesos[elem_entrada];
	float t[elem_entrada];
	float y [num_entradas];

	float ** entradas = new float*[num_entradas];

	for (int i=0; i< num_entradas;i++)
	{	
		entradas[i]= new float[elem_entrada]; 
	}
	//llenando 

	entradas[0][0] =1;
	entradas[0][1] =0;
	entradas[0][2] =0;

	entradas[1][0]= 1;
	entradas[1][1]= 0;
	entradas[1][2]= 1;

	entradas[2][0]= 1;
	entradas[2][1]= 1;
	entradas[2][2]= 0;

	entradas[3][0]= 1;
	entradas[3][1]= 1;
	entradas[3][2]= 1;

	t[0]=0;
	t[1]=0;
	t[2]=0;
	t[3]=1;


	pesos[0]=0.0;
	pesos[1]=0.0;
	pesos[2]=0.0;
		//print 
	for (int i=0; i< num_entradas;i++)
	{
		for (int j=0; j< elem_entrada;j++)
			cout<<entradas[i][j];
		cout<<endl;
	}	

	/* multiplicacion matriz - vector */

	for (int i =0 ;i< num_entradas ; i++)
	{
		y[i]=0;
		for (int j=0; j< elem_entrada;j++)
		{
			y[i]+= entradas[i][j]*pesos[j];	
		}
	}

	for (int j=0; j< num_entradas;j++){		
			cout<<y[j]<<endl;
		//cout<<endl;
	}	
	//compáracio 
	int index = correct(y,t);
	cout<<correct<<endl;
	while (index > 0)
	{

		for (int i=0; i< elem_entrada;i++)
		{
				pesos[i] = t_apre*(t[index]-y[index])*entradas[index][i];
			cout<<pesos[i]<<endl;
		}

		for (int i =0 ;i< num_entradas ; i++)
		{
			//y[i]=0.0;
			for (int j=0; j< elem_entrada;j++)
			{
				y[i]+= entradas[i][j]*pesos[j];	
				if(y[i]!=t[i])
				{
					for (int i=0; i< elem_entrada;i++)
					{
						pesos[i] = t_apre*(t[index]-y[index])*entradas[index][i];
						cout<<pesos[i]<<endl;
						//cout<<"se realizo"<<endl;
					}
			
				}

			}
		}
		index = correct(y,t);
		cout<<"se realizo"<<endl;
		//cout<<"sale"<<endl;*/
	} 

	cout<<"termno"<<endl;

	for(int i =0;i<3;i++)
		cout<<pesos[i]<<endl;	

	return 0;
}