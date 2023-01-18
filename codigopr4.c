/*
Carlos Rubén Carrera Padilla
Código Crank Nicolson para ecuación de Calor en una barra
Ecuación  D²x(T) = Dt(T) donde T(x,t)
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//Función para matriz realizada en clase
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
// Condiciones
  double g1(double t)  //Condiciones dirichlet g1(1,t)= e¹*(1-t²)
    {
    double aux;
    aux=(exp(1)*(1-pow(t,2)));
    return aux;
    }

  double U1(double t)   //Condiciones Neumann g'(x,0)= 1
    {
    double aux;
    aux = 1;
    return aux;
    }
  double U(double x)  //Condicion Inicial
    {
    double aux;
     aux = exp(x);
    return aux;
    }
//Función Crank Nicolson
int main()
{

int i,j,N,M;  // i,j contadores; M,N valores limite
double Tiempo,longitud,gamma,v;
double dx,dt;

FILE *arch = fopen("cal.txt","w");

longitud=1.0;  //Longitud de varilla
Tiempo = 1.0;    //Longitud en Timpo
v=1.0;          //velocidad de propagacion

dx = 0.01;     //diferencia x, tamaño de paso espacio
dt = 0.01;     //diferencia t, tamaño de paso en tiempo
N = (longitud/dx);        //tamaño de arreglo
M = Tiempo/dt;               //pasos temporales
gamma = (v*v*dt)/(dx*dx);   //gamma parametro Courant

//Creamos Vectores mismo tamaño que nuestra malla
double a[N],c[N],e[N]; //Vectores de la matriz tri-diagonal
double x[N],b[N];        //vectores de multiplicación y resultado

for(i=0;i<=N-1;i++)
  {
  a[i] = 2*(gamma + 1);    //diagonal central
  c[i] = -gamma;           //diagonal superior e inferior
  e[i] = -gamma;
  //b[i] = gamma*(f(h*(i+1)) + f(h*(i-1))) + 2.0*(1.0-gamma)*f(h*i);
  x[i] = U(dx*(i+1));  //vecto Inicial
  }
e[0]=-2*gamma; //TErmino en la Matriz para condicion de Neumann

//fprintf(arch,"%lf %lf %lf \n",0.0,0.0,0.0);

//Crank Nicolson
for(j=0;j<=M;j++)
  {
  for(i=1;i<=N-1;i++)
    {
    b[i] = gamma*(x[i+1] + x[i-1]) + 2.0*(1 - gamma)*x[i];  //parte central
    }
  for(i=0;i<=N-1;i++){
    fprintf(arch,"%lf %lf %lf \n ",(i+1)*dx,j*dt,x[i]);
    }
  fprintf(arch,"\n ");
  //Fronteras Neumann y dirichlet respectivamente
  b[1] = 2*(1-gamma)*x[0]+2*gamma*x[1]-2*gamma*dx*U1((j+1)*dt)-2*gamma*dx*U1(j*dt);//(g((j+1)*k)+g(j*k));
  b[N-1] = 2*(1-gamma)*x[N-1]+gamma*x[N-2]+gamma*(g1((j+1)*dt)+g1(j*dt));
  LU(a,b,c,e,x,N);
  }
fclose(arch);


//Gif
FILE *gp = popen("gnuplot ","w");
fprintf(gp, "set term gif animate \n");
fprintf(gp, "set output 'calorgif.gif' \n");
fprintf(gp, "reset \n");
fprintf(gp, "clear \n");

fprintf(gp , "set title 'Ecuacion de Calor ' \n");
fprintf(gp , "set xlabel 'Posicion x' \n");
fprintf(gp , "set ylabel 'Tiempo t' \n");
fprintf(gp , "set zlabel 'Temperatura ' \n");
//fprintf(gp, "set xrange[0:1] \n");
//fprintf(gp, "set zrange[0:5] \n");
//fprintf(gp, "set pm3d at st\n" );
// fprintf(gp, "set pm3d nohidden3d\n" );
  //     fprintf(gp, "set contour\n" );
////      fprintf(gp, "set contour surface\n" );
    //    fprintf(gp, "set cntrparam levels 30\n" );

fprintf(gp, "do for[ii=1:99]{splot \"cal.txt\" every ::1::ii w l ls 6} \n");
fprintf(gp, "quit \n");
fclose(gp);
printf("SE HA CREADO ARCHIVO 'data1.txt' CON LOS DATOS [x,y,z,t]\n\n");
FILE *gnuplot = popen("gnuplot -persistent","w");
fprintf(gnuplot, "set grid \n");
fprintf(gnuplot, "set multiplot layout 1,1 title 'Ecuacion De Calor (Crank Nicolson)' \n");

fprintf(gnuplot, "set title 'Ecuacion de Calor ' \n");
fprintf(gnuplot, "set xlabel 'Posicion X' \n");
fprintf(gnuplot, "set xlabel 'Tiempo t' \n");
fprintf(gnuplot, "set ylabel 'Temperatura' \n");
fprintf(gnuplot, "unset key \n");

fprintf(gnuplot, "set pm3d at st\n" );
fprintf(gnuplot, "set pm3d \n");
fprintf(gnuplot, "set pm3d nohidden3d\n" );
fprintf(gnuplot, "set contour\n" );
//fprintf(gnuplot, "set contour surface\n" );
fprintf(gnuplot, "set cntrparam levels 30\n" );

fprintf(gnuplot, "splot 'cal.txt' using 1:2:3 with lines\n");
}
