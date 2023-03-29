#include <stdio.h>
int main () {
  unsigned int array[5];
  array[2] = 99;


  unsigned int *pointer;
  pointer = &array[0]; 
  *(pointer+2) = 99; //apunta 2 posiciones mas a la derecha de &array[0] osea que esta modificando el valor de array[2] a 99

  pointer = array; //hace lo mismo que linea 8

}