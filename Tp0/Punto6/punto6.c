#include <stdio.h>
int main(){
   char i = 'a'; //1100001
   char j = 77; //1001101
   char k = 0x4D; //1001101
   unsigned char m = 'a'; //1100001
   unsigned char n = 0x4d; //1001101
   unsigned char p = 'A'; //1000001
  printf("i = %i\n",i);
  printf("j = %i\n",j);
  printf("k = %i\n",k);
  printf("m = %i\n",m);
  printf("n = %i\n",n);
  printf("p = %i\n",p);
  if(i==m){
    printf("HOLA");
  }else{
    printf("EYYY");
  }
  //char tiene un rango de [-128,127] por lo que necesita un bit para representar el signo por eso i!=m
  //j,k,m se inicializan con el mismo valor, i=m, p distinto al resto
  return 0;
}