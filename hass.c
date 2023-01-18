/*EDOS-PVI
metodo v elocity verlet con la modificacion de tomar la velocidad como otra funcion (estilo runge kutta)
ni idea si esta correcto, solo lo hice para ver que pasaba
dado que no maneja predictores ni correctores como el rk4, dudo que sea optima la modificacion
 marque las modificaciones donde si las quitan queda el velocity verlet usual
*/
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define k 1

#define alpha  5.0
#define epsilon  0.5
#define beta  (-5/3)
#define gamma  (-5/6)
#define f0(x,v) (v) //modificacion
#define f(x,v) ((-alpha*(x))-(beta*((x)*(x)))-(gamma*((x)*(x)*(x)))-(epsilon*((v)*(v))))

int main(){
  double x0,x1,v,v0,v1,x,F,h,t;
  int i;

  x0=1;
  h=M_PI/100;
  v0=0;

FILE *file=fopen("vet1.txt","w");

  for(i=0;i<600;i++){
    t=i*h;
    x=x0 + v0*h + 0.5* f(x0,v0)*h*h;
  F=v0 + v0*h + 0.5*f0(x0,v0)*h*h; //modificacion
  v= v0 + 0.5*h*(f(x0,v0)+f(x,v));
  v1= v0 + 0.5*h*(f0(x0,v0)+f0(x,F)); //modificacion
  v0=v;
  x0=x;
 fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x,v,v1,t); //aqui solo quiten el que imprime v1
 if(t>=(10)){
 printf("%lf \n",t);
 break;
 }
}
fclose(file);
}
