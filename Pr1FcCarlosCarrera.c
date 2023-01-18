//Carlos  Rubén Carrera Padilla
//raiz entre [2.3,2.4]
//raiz =2.3605 
#include<stdio.h>                  //librerias 
#include<math.h>
//#define f1(x)  (x*x*x)-1                    //Funciones Prueba
//#define f3(x) 11*(x*x*x*x*x*x*x*x*x*x*x)-1
//#define f4(x) (x*x*x)+1
//#define f5(x)  (x*x*x)-2*x-5
#define alp   1090              // Constantes Necesarias
#define rho   0.33
#define Ecu   14.4
#define Der(x)  ( Ecu /(x*x))-(((alp)/(rho))*exp((- x/(rho))))    //Funcion   Potencial
int main() {
double a,b, c,T,fa,fb,fc,dc,m;                      //Variables  tipo Double  

int it = 0;                                           //Variable Iteraciones 
int M = 0;                                           // Variable  de  Metodo
printf("Carlos  Ruben Carrera Padilla \n Programa para encontrar distancia Minima en potencial NaCl con algoritmo Regula Falsi en alguno de los metodos siguientes: \n Inicio \n ");
printf("DEFINE EXTREMOS EN ESTE ORDEN INTERVALO [a, b] Recomendación(2,3)\n");// Guardar datos 
scanf("%lf  %lf",&a,&b);   
printf("TOLERANCIA T \n");
scanf("%lf",&T);             // Guardar datos 
printf("METODO DESEADO Pegasus [1]; Phi4 : [2] ; Anderson & Bjork :[3] \n");
scanf("%i",&M);             // Guardar datos           

fa = Der(a);                                          //Evaluaciones
fb = Der(b);

c = b;                                                //Otro punto 
fc = fb;
dc = -fc/(fb-fa)*(b-a);                               // Interpolación

while( fabs(dc)> T) {                               //loop + condición 

//printf(" c:%lf  dc:%lf  fc:%lf \n",c,dc,fc);
//printf(" fa:%lf  fb:%lf   \n \n",fa,fb);

dc=-fc/(fb-fa)*(b-a);             // diferencia para un nuevo punto

c=c+dc;
fc=Der(c);

if(fb*fc<0) {                             //Condición  modificación de  extremo  1
  a = b;
  fa = fb;
}
else {                                   // Modificación extremo 2
	
	switch ( M )                        //Switch de  Metodo
   {
    case 1 : 
           fa = ((fa*fb)/(fb+fc));            //Metodo Pegasus
	
    
    case 2 :
    	 fa = ((fa-fc)/((1+(fc/fb))*(1+(fc/fb))));           //Metodo phi4
	
    
    case 3 :
		m =  (1-(fc/fb));                //Metodo Anderson Bjork   
	if(m>0) {
		fa = m*fa;
	}
	else {
		fa = fa*1/2;
	}
	
   }

}
    b=c;
    fb=fc;
    it=it+1;
    
//printf(" cf:%lf  dcf:%lf  fcf:%lf \n",c,dc,fc);
//printf(" faf:%lf  fbf:%lf  iterF:%i \n \n \n",fa,fb,it);
//printf("a: %lf\tb: %lf\tf(a): %lf\tf(b): %lf\tf(c): %lf\n",a,b,fa,fb,fc);

}//fin while 1
printf("pasos: %i  en metodo %i    Distancia  Mínima : %0.15lf \n ",it,M,c);
}

