#include "stdio.h"
#include "stdlib.h"
#include "hdf5.h"


void main(){
  int * array = malloc(5*6*4*sizeof(int));
  readh5_("SDS.h5", "/IntArray", array);
  printf("array(2,1,2)=%2d", array[6*4*2+4*1+2]);
}
