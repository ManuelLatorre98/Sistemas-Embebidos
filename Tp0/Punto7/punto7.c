#include <stdio.h>
int main () {

	int x[3]; //Crea arreglo de 3 elems
	int *ptr; //Crea puntero llamado ptr

	char a;
	char *b; //Crea puntero llamado b

        x[0] = 1024; 
        x[1] = 32;
        x[2] = -1;
	ptr = &x[0]; //ptr apunta la direccion de x[0]
	ptr++; //Se mueve una direccion osea a x[1]
	ptr++; //Se mueve una segunda direccion osea a x[2]

	a = 5;
	b = &a; //b apunta la direccion de a
	printf ("a=%i, lo apuntado por b=%i, el contenido de b=%X, y la direccion de b=%X \n", a, *b, b, &b);
  *b = 21;
  /* 
  lo apuntado por b=%i: imprime el valor de la direccion apuntada por b osea el valor de a=5
  el contenido de b=%X: imprime la direccion de a porque es el valor que tiene guardado (apuntando) b
  la direccion de b=%X: b es una variable puntero por lo que tiene su propia direccion justo despues de a que fue la ultima variable declarada


  Si al comenzar el programa el sistema asignó la dirección 0xFFA00004 al
arreglo x[], 
	¿Cuál es el valor final del contenido de ptr al finalizar la
	ejecución del programa?
  ptr = 0xFFA00006 (se desplaza dos posiciones), si se imprime el valor de lo guardado en la direccion apuntada imprimiria -1

	¿Cuál es el valor final del contenido de la variable 'a' al 
	finalizar el programa? 
  a = 21 porque *b=21 modifica el valor de la direccion apuntada por b que era la dir de a
	¿Cuál es la dirección de la variable x[2]?
  0xFFA00006
  */  
	
}