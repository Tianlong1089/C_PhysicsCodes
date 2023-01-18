//CARLOS RUBEN CARRERA PADILLA
// Código que resuelve la ecuación de avección  dt(U)+vdx(U)=0
//Métedo Euler Forward.
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define Fi(x) (exp(-(0.5)*x*x));
//inicia funcion

int main(){

  double k,rho=0.5,a=-10,ti=0,b=5,T=5,v=1;
  double DT,DX;
  int m,n,j,i;
  int aux;

  DT= 0.1;
  DX= DT/rho;

  m = fabs(b-a)/DX; //ITERCIONES
  n = fabs(T)/DT;  //PUNTOS


  double malla[m][n],x[m] ;// la malla
  //CONDICIONES INICIALES
  for (i =0; i < m; i++) {
    x[i]=a+i*DX; //VECTOR
      malla[i][0]=Fi(x[i]); //PRIMER NIVEL
      }
//Siguente NIVEL
aux=1;
T=T/DT;  // iteraciones tiempo
for (int i = 0; i < T-1; i++) {
  for (int j = aux; j < m-aux; j++) {
  malla[j][i+1]=malla[j][i] - (0.5*v*DT/DX)*(malla[j+1][i]-malla[j-1][i]);
}
malla[j][i]=malla[j][i+1];
 aux=aux+1;
}
//Impresion
FILE *file=fopen("adata.txt","w");
if(file != NULL)
{
aux=1;
for (int  i = 0; i < T-1; i++)
  {
    for (int j = aux; j < m-aux; j++) {
      fprintf(file, "%lf \t %lf \n", x[j], malla[j][i]);
    }
  aux=aux+1;
  fprintf(file, "\n \n" );
  }
  fclose(file);
}

FILE *gnuplot = popen("gnuplot -persistent","w");
fprintf(gnuplot, "set grid \n");
fprintf(gnuplot, "set multiplot layout 1,1 title 'Evolucion con Metedo Euler FORWARD' \n");

fprintf(gnuplot, "set title 'METODO EULER FORWARD' \n");
fprintf(gnuplot, "set xlabel 'Posicion X' \n");
fprintf(gnuplot, "set ylabel 'Posicion U n+1' \n");
fprintf(gnuplot, "unset key \n");
fprintf(gnuplot, "plot 'adata.txt' using 1:2 with lines lt 6  \n");
}
