//CARLOS RUBÉN CARRERA PADILLA
/*Código que dibuja lineas equipotenciales para una distibución de carga
triangular entre dos placas cargadas.
Métilizado SOR para  Ecuación de POISSON
Encuentra lineas equipotenciales en una distribución de carga dada.

Parametro  p= 1.9401
*/
#include<stdio.h>
#include<math.h>

int main() {

  int  DIM=500;
  double phi[DIM][DIM],rho[DIM][DIM];  //matrices a ocupar
  double T,h,x0,y0;
  double max,ph,aux,p;
  int i,j,n,k,l,m,m1;   //contadores
  int x,y,x1;              //auxiliares
//valores
  h=0.01;            //paso
  T=1E-6;          //tolerancia
  n=1/h;             //malla
  k=0;
  p=1.941;            // variable método

  FILE*arch=fopen("data.txt","w");  //Archivo a imprimir

//Inicialización
  for(i=0;i<=n;i++){
    for(j=0;j<=n;j++){
      rho[i][j]=0.0;
    }}
    //Triangulo
    //continuo en malla de cargas para superficie cargada
    for(i=0;i<=20;i=i+1){
    rho[30+i][39+2*i]=1000.0;
    rho[70-i][39+2*i]=1000.0;
    rho[30+2*i][39]=1000.0;
    //rho[80-3*i][20+i]=10000.0;
    //rho[30+i][50]=10000.0;
    }

    /**/
    //Circulo de particulas
    //Carga en lugares especificos

    for(i=0;i<=40;i=i+10){
      rho[10+i][50+i]=10000.0 ;
      rho[50+i][90-i]=10000.0 ;
      rho[90-i][50-i]=10000.0 ;
      rho[50-i][10+i]=10000.0 ;
    }
    rho[10][50]=0.0;
    rho[17][50]=10000.0;

    rho[90][50]=0.0;
    rho[83][50]=10000.0;

    rho[50][10]=00.0 ;
    rho[50][17]=10000.0;

    rho[50][90]=00.0 ;
    rho[50][83]=10000.0 ;
  //Distribucion de Carga
//Caras Paralelas
/*
  for(i=0;i<=1/h;i++){
  rho[i][98]=20000.0;
  }
  for(i=0;i<=1/h;i++){
  rho[i][2]=20000.0;
  }
  for(i=4;i<=0.96/h;i++){
  rho[2][i]=20000.0;
  }
  for(i=4;i<=0.96/h;i++){
  rho[98][i]=20000.0;
}
*/
 //Particulas
/*
  x=round(0.20/h);
  y=round(0.20/h);
  rho[x][y]=10000.0;
  rho[x][y+20]=10000.0;
  rho[x][y+40]=10000.0;
  rho[x][y+60]=10000.0;
  x1=round(0.80/h);
  rho[x1][y]=10000.0;
  rho[x1][y+20]=10000.0;
  rho[x1][y+40]=10000.0;
  rho[x1][y+60]=10000.0;
*/
//Cuadrados paralelos
/*
for(i=0;i<=10;i=i+1){
rho[70+2*i][40]=10000.0;
rho[70+2*i][60]=10000.0;
rho[70][40+2*i]=10000.0;
rho[90][60-2*i]=10000.0;
}
for(i=0;i<=10;i=i+1){
rho[10+2*i][40]=5000.0;
rho[10+2*i][60]=5000.0;
rho[10][40+2*i]=5000.0;
rho[30][60-2*i]=5000.0;
}
for(i=0;i<=50;i=i+1){
  rho[50][2*i]=5000.0;
}
//
*/
  max=100;

  while (max>=T) {
    max=0;
    k++;
    for (i=1;i<=(n-1);i++) {
      for (j=1;j<=(n-1);j++) {
        ph=phi[i][j];
        phi[i][j]=(1.0/4.0)*(phi[i-1][j]+phi[i+1][j]+phi[i][j-1]+phi[i][j+1]+(h*h)*rho[i][j]);
        phi[i][j]=(1-p)*ph+p*phi[i][j];
        aux=fabs(phi[i][j]-ph);
        if(aux>max){
         max=aux;
        }
      }
    }
  }

  for (i=0;i<=n;i++) {
    for(j=0;j<=n;j++){
      fprintf(arch, "%lf %lf %lf \n",i*h,j*h,phi[i][j]);
    }
    fprintf(arch,"\n");
  }
  printf("%d \n",k);
  fclose(arch);

  fclose(arch);
  printf("SE HA CREADO ARCHIVO 'data.txt' CON LOS DATOS [x,y,F(X,Y)] A %.2lf\n",p);
  printf("Numero de pasos realizados %d \n\n",k);

  FILE *gnuplot = popen("gnuplot -persistent","w");
  fprintf(gnuplot, "set grid \n");
  fprintf(gnuplot, "set multiplot layout 1,1 title 'Lineas equipotenciales con parametro relajación %.2lf' \n",p);

  fprintf(gnuplot, "set title 'X vs. Y a %d pasos' \n",k);
  fprintf(gnuplot, "set xlabel 'Posicion X' \n");
  fprintf(gnuplot, "set ylabel 'Posicion Y' \n");

  fprintf(gnuplot, "set pm3d map \n");
  fprintf(gnuplot, "set contour\n");
  fprintf(gnuplot, "set cntrparam levels 25\n");
  fprintf(gnuplot, "splot 'data.txt' using 1:2:3  \n");

}
