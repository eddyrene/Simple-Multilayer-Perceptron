#include <iostream>
#include <vector>
#include <string>


using namespace std;

const int num_entradas= 4;
const int size_entrada = 3;
const float t_apre = 0.5;

float * pesos=  new float[size_entrada];
float * t = new float[size_entrada];
float *y = new float[num_entradas];
bool flag= false;
float ** entradas;

bool correct( float a, float b)
{
		if(a!= b)
			return false;
		return true;
}
void actualizar_pesos(int index)
{
	for (int i=0; i< size_entrada;i++)
		{
			//cout<<"index:"<<index<<endl;
			pesos[i] += t_apre*(t[index]-y[index])*entradas[index][i];		}
}
int sigmod(float f)
{
	if(f<0.5)
		return 0;
	else
		return 1;
}
void multiplicacion(float *pesos, float ** entradas)
{
	flag=true;
	for (int i =0 ;i< num_entradas ; i++)
	{
		y[i]=0;
		for (int j=0; j< size_entrada;j++)
		{
			y[i]+= entradas[i][j]*pesos[j];
		}
		y[i]=sigmod(y[i]);
		if(y[i]!=t[i])
		{
			int g= i;
			flag =false;
			actualizar_pesos(g);
		}
	}
	
}

void create()
{
	entradas = new float*[num_entradas];
	for(int i =0;i<num_entradas;i++)
		entradas[i]= new float[size_entrada];
}

void imprimir_vector(float *a, int tam)
{
	for (int j=0; j< tam;j++){		
			cout<<a[j]<<" ";
	}
	cout<<endl;	
}

void imprimir_matriz(float ** b)
{
	for (int i=0; i< num_entradas;i++)
	{
		for (int j=0; j< size_entrada;j++)
			cout<<b[i][j];
		cout<<endl;
	}	
}

int main()
{
	create();
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

	pesos[0]=0;
	pesos[1]=0;
	pesos[2]=0;

	cout<<"entradas"<<endl;
	
	imprimir_matriz(entradas);


	cout<<"esperados"<<endl;
	
		imprimir_vector(t,num_entradas);
	cout<<"pesos"<<endl;
		imprimir_vector(pesos,size_entrada);
		
	cout<<"result:"<<endl;
		imprimir_vector(y,num_entradas);
		flag=false;

	int gh =0;
	while (!flag)
	{
		
		cout<<"era: "<<gh<<endl;
		multiplicacion(pesos,entradas);
		cout<<"     nuevos pesos"<<endl;
		imprimir_vector(pesos,size_entrada);
		gh++;
	} 
	cout<<"result:"<<endl;
		imprimir_vector(y,num_entradas);
	//cout<<"termno"<<endl;
	return 0;
}