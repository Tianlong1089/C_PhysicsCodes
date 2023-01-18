/*Carlos Rubén Carrera Padilla
Programa que genera gif para el desplazamiento de una función en el ejeX*/
#include<stdio.h>  // Librerias a utlizar
#include<math.h>
#include<stdlib.h>

int main() { //inicio

int i,j;     //variables para contadores
double x,t;  //variables posición=x y tiempo=t

FILE *arch=fopen("datos.txt","w");   //Archivo donde guardar datos

for(i=0;i<200;i++) {  //contador tiempo

t=i*0.1;           // avanzar en el tiempo

for(j=0;j<200;j++) { // contador desplazamiento

x=2.*M_PI* j/100;    //desplazamiento en x

fprintf(arch, "%lf %lf \n",x,5.0*(1.0 + cos(x*t)));   //imprime en el archivo

} //termina el loop y cierra el archivo
fprintf(arch,"\n\n");
}
fclose(arch);  //termina el loop y cierra el archivo

FILE *gp=popen("gnuplot","w");     //Manda a llamar a gnuplot para hacer gif
fprintf(gp,"set term gif animate\n");
fprintf(gp,"set output \"animado4.gif\"\n");
fprintf(gp,"set xlabel \"x\"\n");
fprintf(gp,"set ylabel \"y\"\n");
for(i=0;i<100;i++){   // grafica datos desde el archivo
fprintf(gp,"plot \"datos.txt\"index %d \n",i);
}
fprintf(gp,"quit \n");
fclose(gp);
}
