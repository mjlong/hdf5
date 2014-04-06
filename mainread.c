#include "stdio.h"
#include "stdlib.h"
#include "hdf5.h"


void main(){
  int * array = malloc(5*6*4*sizeof(int));
  double * xy = malloc(50*2*sizeof(double)); 
  readh5_("SDS.h5", "/IntArray", array);
  printf("array(2,1,2)=%2d\n", array[6*4*2+4*1+2]);

  readh5_("results.h5","/xypair",xy);
  printf("xy(10,1)=%g\n", xy[10]);
}

