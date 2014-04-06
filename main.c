#include<stdio.h>
#define ROW 2
#define COL 4

void main(){
  double vec0[COL+COL];
  double* vec1;
  double* vec2;
  double array[ROW][COL];
  int i,j, nrow, ncol;
  vec1 = vec0;
  vec2 = vec0 + COL;
  nrow = ROW;
  ncol = COL;
  for(i=0; i<ROW; i++)
    for(j=0; j<COL; j++)
      array[i][j]=210 + 10*i+j;
  
  for(i=0; i<COL; i++){
    vec1[i]=10 + i;
    vec2[i]=20 + i;
  }
  writeh5_nxm_("t2d.h5", "one 2D", (double*)array[0], &nrow, &ncol);
  writeh5_nxm_("t2v.h5", "two 1D", (double*)vec0,     &nrow, &ncol);

}
