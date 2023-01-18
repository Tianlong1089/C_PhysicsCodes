#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define g 1.0
#define q 2.0
#define omega_D (2.0/3.0)
#define g_1 0.9
double g1(double y1, double y2, double t);
double g1(double y1, double y2, double t)
{
  double result;
  result = y2;
  return result;
}
double g2(double y1, double y2, double t);
double g2(double y1, double y2, double t)
{
  double result;
  result = -(y2/q) - g*sin(y1) + g_1*cos(omega_D*t);
  return result;
}

int main()
{
int i,j,n,m,k;
double y1i,y2i,y1ii,y2ii,k11,k12,k21,k22,k31,k32,k41,k42,t,h;

h = M_PI/100;
i = 0;
n = (2*M_PI)/(omega_D*h); //Número de pasos por ciclo.
m = 10000; //Número de ciclos.
k = 20; //Número de ciclos del transitorio.
printf("Dame la posición inicial, por favor. \n");
scanf("%lf",&y1i);
printf("Dame la velocidad inicial, por favor. \n");
scanf("%lf",&y2i);

FILE *arch = fopen("Poincare.txt","w");
//fprintf(arch,"%lf %lf %lf \n",0.0,y1i,y2i);
for(i=0;i<=n*m;i++)
  {
  t = h*i;
  k11 = h*g1(y1i,y2i,t);
  k12 = h*g2(y1i,y2i,t);
  k21 = h*g1(y1i + 0.5*k11,y2i + 0.5*k12,t + 0.5*h);
  k22 = h*g2(y1i + 0.5*k11,y2i + 0.5*k12,t + 0.5*h);
  k31 = h*g1(y1i + 0.5*k21,y2i + 0.5*k22,t + 0.5*h);
  k32 = h*g2(y1i + 0.5*k21,y2i + 0.5*k22,t + 0.5*h);
  k41 = h*g1(y1i + k31,y2i + k32,t + h);
  k42 = h*g2(y1i + k31,y2i + k32,t + h);
  y1ii = y1i + (1.0/6.0)*(k11 + 2*k21 + 2*k31 + k41);
  y2ii = y2i + (1.0/6.0)*(k12 + 2*k22 + 2*k32 + k42);
  if(y1ii > 0)
    {
    j = y1ii/(2*M_PI) + 0.5;
    }
  else
    {
    j = y1ii/(2*M_PI) - 0.5;
    }
  y1ii = y1ii - 2*M_PI*j;
  if(i > k*n && i%n == 0)
    {
    fprintf(arch,"%lf %lf %lf \n",t,y1ii,y2ii);
    }
  y1i = y1ii;
  y2i = y2ii;
  }
fclose(arch);

FILE *gnuplot = popen("gnuplot -persistent","w");
fprintf(gnuplot, "set grid \n");
//fprintf(gnuplot, "set multiplot layout 2,2 title 'Péndulo' \n");

/*fprintf(gnuplot, "set title 'theta vs. t' \n");
fprintf(gnuplot, "set xlabel 'tiempo' \n");
fprintf(gnuplot, "set ylabel 'theta' \n");
fprintf(gnuplot, "unset key \n");
fprintf(gnuplot, "plot 'Poincare.txt' using 1:2 with lines \n");

fprintf(gnuplot, "set title 'vel. angular vs. t' \n");
fprintf(gnuplot, "set xlabel 'tiempo' \n");
fprintf(gnuplot, "set ylabel 'vel. angular' \n");
fprintf(gnuplot, "unset key \n");
fprintf(gnuplot, "plot 'Poincare.txt' using 1:3 with lines \n");*/

fprintf(gnuplot, "set title 'vel. angular vs. theta' \n");
fprintf(gnuplot, "set xlabel 'vel. angular' \n");
fprintf(gnuplot, "set ylabel 'theta' \n");
fprintf(gnuplot, "unset key \n");
fprintf(gnuplot, "plot 'Poincare.txt' using 2:3 with dots \n");
}
