/* Carlos Rubén Carrera Padilla
Código que utiliza diferencias finitas y método de potencias inversas para hallar
los valores propios de un oscilador armónico con una perturbación debido a un campo
electrico en función de la posición.
Potencial V(x)= 1/2 mw²x² - qEx               m=w=1 ; q=1 ; E=5
*/
#include<stdio.h>           //Librerias
#include<stdlib.h>
#include<math.h>
#define CE  15.55           //constante de Campo electrico
#define POT(x) (((x)*(x))/2) - (CE*x)   //Potencial a utilizar
//Código Función LU para diagonales de matrices y sus vectores asociados.
void LU(double a[], double b[], double c[], double e[], double x[], int N)
{
int i;
i = 0;
double w[N];
double u[N];
double y[N];
w[0] = a[0];
y[0] = b[0]/w[0];

for(i = 1;i <= N-1;i++)
  {
  u[i-1] = e[i-1]/w[i-1];
  w[i] = a[i] - u[i-1]*c[i];
  y[i] = (b[i] - c[i]*y[i-1])/w[i];
  }
u[N-1] = e[N-1]/w[N-1];
x[N-1] = y[N-1];

for(i = N-2;i >= 0;i--)
  {
  x[i] = y[i] - u[i]*x[i+1];
  }
}
//inicia función
void main(){
  //variables
	int i,j,k,n;                  //contadores
	double aux,energia,h,tol,dif,qi,qii,Qi,Qii,A1,aux1;
  double val1,val2,Q1,Q2;     //valores y normas

	A1=5.0;     //tamaño
  dif=100;    //diferencia inicial  (break)
  h=0.01;     //paso a utilizar
	tol=1E-6;  //tolerancia

  n= 2*A1/h+1; //número de particiones
//Valor porpio a aproximar

	printf("Valor de la Energia cercana E:\n");
	scanf("%lf",&energia);
	aux=2*energia;

  FILE *arch=fopen("data.txt","w"); //impresión

	double a[n-1],c[n-1],e[n-1]; // Diagonales de matriz tridiagonal
  double x[n-1],b[n-1];        //VEctor función y resultado
  double y1[n-1],y2[n-1];      //Vectores auxiliares
 //Se construye la matriz
	for ( i = 0; i <= n-2; i++)
	{
		a[i]=2.0*(1/pow(h,2)+POT(-A1*i*h))-aux;    //DIagonal central
		c[i]=-1.0/pow(h,2);
		e[i]=-1.0/pow(h,2);
		b[i]=1.0/sqrt(n-1);
		x[i]=0.0;
	}

	c[0]=0;  //Extremos para que función se vaya a cero
	e[n-2]=0;

	while(fabs(dif) >= tol)	{ // break para diferenica entra normas
		k++; //contador

    Qi=0; //PRIMERA NORMA
		for ( i = 0; i <= n-2; i++) {
			Qi+=x[i]*x[i];		}
    qi=sqrt(Qi);

		LU(a,b,c,e,x,n-1); //Aplicamos Lu para nuestro vector X[]

    Qii=0;  //SEGUNDA NORMA
		for ( i = 0; i <= n-2; i++) {
			Qii+= x[i]*x[i];		}
		qii=sqrt(Qii);

		for ( i = 0; i <= n-2; i++) {  //Nuevo vector b[]
		b[i]= x[i]/qii;
    }

dif = 1.0/qi - 1.0/qii; // para break
}

	val1=(1.0/qii);  //valores propios
	val2=-(1.0/qii);

	for ( i = 0; i <= n-2; i++)
	{ //se construyen nuevos vectores apartir de cada valor
		y1[i]=(c[i]*x[i-1]+a[i]*x[i]+e[i]*x[i+1])-val1*x[i];
		y2[i]=(c[i]*x[i-1]+a[i]*x[i]+e[i]*x[i+1])-val2*x[i];
	}

	Q1=0;  //Se saca la norma de cada vector nuevo para derterminar el valor mánimo
	Q2=0;
	for ( i = 0; i <=n-2; ++i)	{
		Q1 += y1[i]*y2[i];
		Q2 += y2[i]*y2[i];
	}
// impresión
	for ( i = 0; i <= n-2; ++i){
		fprintf(arch, "%lf\t%lf\n",i*h,x[i] );
	}
	fclose(arch);

	if(Q1<Q2) { //Se deterina el dominante VAlor propio
		printf("El valor Propio más cercano es :%lf\n",(aux+val1)/2 );
		printf("Número de iteraciones:%d\n",k );
    aux1=(aux+val1)/2;
	}
	else	{
		printf("El valor Propio más cercano es :%lf\n",(aux+val2)/2 ); //quiza es menos
		printf("Número de iteraciones:%d\n",k );
    aux1=(aux+val2)/2;
	}
  printf("SE HA CREADO ARCHIVO 'data.txt' CON LOS DATOS [iteracion, solucion]\n");
  //impresión para gnuplot
  FILE *gnuplot = popen("gnuplot -persistent","w");
  fprintf(gnuplot, "set grid \n");
  fprintf(gnuplot, "set multiplot layout 1,1 title  'EigenFunción para Energia %.2lf  resultado %lf ' \n",energia,aux1);
  fprintf(gnuplot, "set xlabel 'X' \n");
  fprintf(gnuplot, "set ylabel 'Y' \n");
  fprintf(gnuplot, "plot 'data.txt' using 1:2 w l \n");
}

