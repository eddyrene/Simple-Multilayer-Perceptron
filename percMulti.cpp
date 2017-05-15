/* Reconocimiento de digitos */ 
/* Eddy Rene Caceres Huacarpuma*/

#include <iostream>
#include <vector>
#include <string>


using namespace std;


//Entrada

typedef struct {
int num_entradas= 10;
int size_entrada = 8;
float ** mat;	
}entradas;


//Salida
typedef struct {
float ** mat;
int num_salidas= 10;
int size_salida = 4;
}salidas;

typedef struct {
//Pesos01
int num_pesos01= 8;
int size_pesos01 = 6;

//Pesos12
int num_pesos12= 6;
int size_pesos12 = 4;

float ** theta01;
float ** theta12;

}pesos;

const float t_apre = 0.5;


entradas A;
salidas Y;
pesos W;

void createEntradas()
{
	A.mat = new float*[A.num_entradas];
	for(int i =0;i<A.num_entradas;i++)
		A.mat[i]= new float[A.size_entrada];

	A.mat[0][0] =1;
	A.mat[0][1] =1;
	A.mat[0][2] =1;
	A.mat[0][3] =1;
	A.mat[0][4]= 0;
	A.mat[0][5]= 1;
	A.mat[0][6]= 1;
	A.mat[0][7]= 1;

	A.mat[1][0] =1;
	A.mat[1][1] =1;
	A.mat[1][2] =0;
	A.mat[1][3] =0;
	A.mat[1][4]= 0;
	A.mat[1][5]= 0;
	A.mat[1][6]= 0;
	A.mat[1][7]= 1;

	A.mat[2][0] =1;
	A.mat[2][1] =1;
	A.mat[2][2] =1;
	A.mat[2][3] =0;
	A.mat[2][4]= 1;
	A.mat[2][5]= 1;
	A.mat[2][6]= 1;
	A.mat[2][7]= 0;

	A.mat[3][0] =1;
	A.mat[3][1] =1;
	A.mat[3][2] =1;
	A.mat[3][3] =0;
	A.mat[3][4]= 1;
	A.mat[3][5]= 0;
	A.mat[3][6]= 1;
	A.mat[3][7]= 1;

	A.mat[4][0] =1;
	A.mat[4][1] =1;
	A.mat[4][2] =0;
	A.mat[4][3] =1;
	A.mat[4][4]= 1;
	A.mat[4][5]= 0;
	A.mat[4][6]= 0;
	A.mat[4][7]= 1;

	A.mat[5][0] =1;
	A.mat[5][1] =0;
	A.mat[5][2] =1;
	A.mat[5][3] =1;
	A.mat[5][4]= 1;
	A.mat[5][5]= 0;
	A.mat[5][6]= 1;
	A.mat[5][7]= 1;


	A.mat[4][0] =1;
	A.mat[6][1] =0;
	A.mat[6][2] =1;
	A.mat[6][3] =1;
	A.mat[6][4]= 1;
	A.mat[6][5]= 1;
	A.mat[6][6]= 1;
	A.mat[6][7]= 1;

	A.mat[7][0] =1;
	A.mat[7][1] =1;
	A.mat[7][2] =1;
	A.mat[7][3] =0;
	A.mat[7][4]= 0;
	A.mat[7][5]= 0;
	A.mat[7][6]= 0;
	A.mat[7][7]= 1;

	A.mat[8][0] =1;
	A.mat[8][1] =1;
	A.mat[8][2] =1;
	A.mat[8][3] =1;
	A.mat[8][4]= 1;
	A.mat[8][5]= 1;
	A.mat[8][6]= 1;
	A.mat[8][7]= 1;

	A.mat[9][0] =1;
	A.mat[9][1] =1;
	A.mat[9][2] =1;
	A.mat[9][3] =1;
	A.mat[9][4]= 1;
	A.mat[9][5]= 0;
	A.mat[9][6]= 1;
	A.mat[9][7]= 1;

	

}

void createSalidas()
{
	Y.mat = new float*[Y.size_salida];
	for(int i =0;i<Y.size_salida;i++)
		Y.mat[i]= new float[Y.num_salidas];

	Y.mat[0][0]=0;
	Y.mat[0][1]=0;
	Y.mat[0][2]=0;
	Y.mat[0][3]=0;
	Y.mat[0][4]=0;
	Y.mat[0][5]=0;
	Y.mat[0][6]=0;
	Y.mat[0][7]=0;
	Y.mat[0][8]=1;
	Y.mat[0][9]=1;

	Y.mat[1][0]=0;
	Y.mat[1][1]=0;
	Y.mat[1][2]=0;
	Y.mat[1][3]=0;
	Y.mat[1][4]=1;
	Y.mat[1][5]=1;
	Y.mat[1][6]=1;
	Y.mat[1][7]=1;
	Y.mat[1][8]=0;
	Y.mat[1][9]=0;

	Y.mat[2][0]=0;
	Y.mat[2][1]=0;
	Y.mat[2][2]=1;
	Y.mat[2][3]=1;
	Y.mat[2][4]=0;
	Y.mat[2][5]=0;
	Y.mat[2][6]=1;
	Y.mat[2][7]=1;
	Y.mat[2][8]=0;
	Y.mat[2][9]=0;

	Y.mat[3][0]=0;
	Y.mat[3][1]=1;
	Y.mat[3][2]=0;
	Y.mat[3][3]=1;
	Y.mat[3][4]=0;
	Y.mat[3][5]=1;
	Y.mat[3][6]=0;
	Y.mat[3][7]=1;
	Y.mat[3][8]=0;
	Y.mat[3][9]=1;

}

void createPesos()
{
	W.theta01 = new float*[W.num_pesos01];
	for(int i =0;i<W.num_pesos01;i++)
		W.theta01[i]= new float[W.size_pesos01];

	
	for(int i=0; i<W.num_pesos01;i++ )
		for(int j=0;j<W.size_pesos01;j++)
				W.theta01[i][j]=0;

	W.theta12 = new float*[W.num_pesos12];
	for(int i =0;i<W.num_pesos12;i++)
		W.theta12[i]= new float[W.size_pesos12];
	
	for(int i=0; i<W.num_pesos12;i++ )
		for(int j=0;j<W.size_pesos12;j++)
				W.theta12[i][j]=0;

}

float ** fw01(int ** e, float ** t)
{
	float ** a01;
	a01 = new float*[W.size_pesos12];
	for(int i =0;i<W.size_pesos12;i++)
		a01[i]= new float[W.num_pesos12];

}

float sigmod(float f)
{
	if(f<0.5)
		return 0.0;
	else
		return 1.0;
}

float**  activation(float ** A,float ** B , int a , int b , int c )
{
	float ** C;
	C = new float*[a];
		for(int i =0;i<a;i++)
			C[i]= new float[c];

	//llenando de ceros
	
	/*for(int i=0; i<a;i++ )
		for(int j=0;j<c;j++)
				C[i][j]=0;	*/

	for(int i=0;i<a;i++)
	{
		for(int j=0;j<c;j++)
		{
			C[i][j]=0;
			for(int k=0;k<b;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
				//cout<<"entra"<<endl;
			}
			if(i==0)
				C[i][j]=1;		
			C[i][j]=sigmod(C[i][j]);	
			//float a=sigmod(C[i][j]);
			//C[i][j]=sigmod(C[i][j]);	
		}
	}
	return C;
	//cout<<"se termino con exito"<<endl;		
}

void printMat(string ch, float ** M, int f, int c)
{
	cout<<ch<<endl;
	for(int i =0 ;i < f; i++)
	{
		for(int j =0 ;j < c;j++)
			cout<<M[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}

float ** error(float ** A, float ** B, int c, int f)
{
	float ** T;
	T = new float*[c];
		for(int i =0;i<c;i++)
			T[i]= new float[f];

	for(int i=0; i<c;i++ )
		for(int j=0;j<f;j++)
				T[i][j]=A[j][i]-B[i][j];

	return T;
}
int main()
{
	createEntradas();
	printMat("imprimiendo entradas\n",A.mat,A.num_entradas,A.size_entrada);
	createSalidas();
	printMat("imprimiendo salidas\n",Y.mat,Y.size_salida,Y.num_salidas);
	createPesos();

	entradas A01, A12;
	float ** R1= activation(A.mat,W.theta01, A.num_entradas, A.size_entrada, W.size_pesos01);
	
	A01.mat= R1;
	A01.num_entradas=A.num_entradas;
	A01.size_entrada=W.size_pesos01;
	
	printMat("Activacion capa 1 \n",A01.mat,A01.num_entradas,A01.size_entrada);	
	
	float ** R2 = activation(A01.mat,W.theta12, A01.num_entradas, A01.size_entrada, W.size_pesos12);
	A12.mat= R2;
	A12.num_entradas=A01.num_entradas;
	A12.size_entrada=W.size_pesos12;

	printMat("Acticacion capa 2:\n",A12.mat,A12.num_entradas,A12.size_entrada);	
	
	printMat("Resultado esperado: \n", Y.mat, Y.size_salida , Y.num_salidas);

	//cout<<"num "<<A12.num_entradas<<endl;
	//cout<<"size "<<A12.size_entrada<<endl;

	float ** E = error(Y.mat, A12.mat, Y.num_salidas, Y.size_salida);

	printMat("Error : \n", E, Y.num_salidas , Y.size_salida);	
	return 0;
}