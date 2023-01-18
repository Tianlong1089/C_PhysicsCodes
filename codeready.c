//Carlos Rubén Carrera Padilla
//Código Runge Kutta 4 para 3 variables 
//Código particular para sistema de Lorenz
#include <stdio.h>     //librerias
#include <math.h>
#include <stdlib.h>
//Constantes del problema
float sig=10.0;
float b=(8/3);
float r=24.78;     //valor a variar RAZON DE RAYLEIGH
//FUNCIONES 
double Fx(double x1,double y1,double z1,double t){ 
  double var=0.0;
  var= sig*(y1-x1);
  return var; 
  }
  double Fy(double x1,double y1,double z1,double t){//FUNCION PARA Y
  double var=0.0;
  var= (r*x1)-y1-(x1*z1);
  return var;
}
double Fz(double x1,double y1,double z1,double t){ //FUNCION PARA Z
  double var=0.0;
  var=(x1*y1)-(b*z1);
  return var ;
}
//INICIO DE APLICACIÓN
int main()
{
int i;

double x1j,y1j,z1j;      //POSICIÓN
double x1j1,y1j1,z1j1;   // NUEVA POSICIÓN
double k1xj,k1yj,k1zj,k2xj,k2yj,k2zj,k3xj,k3yj,k3zj,k4xj,k4yj,k4zj; //variables Rk
double t,h;              

h = M_PI/100;  // TAMAÑO DE PASO
i = 0;           

// Condiciones Inciales
x1j=-1;
y1j=-3;
z1j=3;

FILE *arch = fopen("data1.txt","w");  //archivo a imprimir
//For para evolución de la solción
for(i=0;i<=6000;i++){
  t = h*i; // Tiempo 
  //RUNGE KUTTA 4 PARA 3 VARIABLES + TIEMPO
  k1xj = h*Fx(x1j,y1j,z1j,t);
  k1yj = h*Fy(x1j,y1j,z1j,t);
  k1zj = h*Fz(x1j,y1j,z1j,t);

  k2xj=h*Fx(x1j+0.5*k1xj,y1j+0.5*k1yj,z1j+0.5*k1zj,t+0.5*h);
  k2yj=h*Fy(x1j+0.5*k1xj,y1j+0.5*k1yj,z1j+0.5*k1zj,t+0.5*h);
  k2zj=h*Fz(x1j+0.5*k1xj,y1j+0.5*k1yj,z1j+0.5*k1zj,t+0.5*h);

  k3xj=h*Fx(x1j+0.5*k2xj,y1j+0.5*k2yj,z1j+0.5*k2zj,t+0.5*h);
  k3yj=h*Fy(x1j+0.5*k2xj,y1j+0.5*k2yj,z1j+0.5*k2zj,t+0.5*h);
  k3zj=h*Fz(x1j+0.5*k2xj,y1j+0.5*k2yj,z1j+0.5*k2zj,t+0.5*h);

  k4xj=h*Fx(x1j+k3xj,y1j+k3yj,z1j+k3zj,t+h);
  k4yj=h*Fy(x1j+k3xj,y1j+k3yj,z1j+k3zj,t+h);
  k4zj=h*Fz(x1j+k3xj,y1j+k3yj,z1j+k3zj,t+h);

  x1j1 = x1j + (1.0/6.0)*(k1xj + 2*k2xj + 2*k3xj + k4xj);
  y1j1 = y1j + (1.0/6.0)*(k1yj + 2*k2yj + 2*k3yj + k4yj);
  z1j1 = z1j + (1.0/6.0)*(k1zj + 2*k2zj + 2*k3zj + k4zj);

  fprintf(arch,"%lf %lf %lf %lf \n",x1j1,y1j1,z1j1,t); //Impresión
//renombremiento de puntos iniciales 
x1j=x1j1; 
y1j=y1j1;
z1j=z1j1;
}
fclose(arch);
}
