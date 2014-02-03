#include <stdlib.h>
#include <stdio.h>
#include "hdf5.h"


void main(){

  hid_t       file, dataset;         /* file and dataset handles */
  hid_t       datatype, dataspace;   /* handles */
  hsize_t     dimsf[2];              /* dataset dimensions */
  herr_t      status;                             
  //  int**    data = (int**)malloc(2*sizeof(int*)); /* data to write */
  //  int *datat[2];
  /* from experience so far, it seems that 
     int *data[2] is used to let data[0]=vec1
     int (*data)[2] is used to let data[0]=d0[0]
     UPDATE: the following is more believable
     int *data[2] 2 int pointers in an array
     int (*data)[2] 1 pointer points to a int any[2] array
  */
  int length = 4;
  int i,j;
  char   filename[16]="t2d.h5", dsetname[16]="name";
  int *datt[2];
  int *data[2];
  int vec1[4];
  int vec2[4];

  //  int vec3[4];
  //int arr1[4][1];
  //int arr2[4][1];
  /* 
   * Data  and output buffer initialization. 
  */

  for(i=0;i<length;i++){
    *(vec1+i)=10+i;
    *(vec2+i)=20+i;
    //    *(vec3+i)=30+i;
  }
  *(data+0) = (int*)vec1;
  *(data+1) = (int*)vec2;
  

  /*
  for(i=0;i<length;i++){
    *(*(datad+0)+i) = vec1[i];
    *(*(datad+1)+i) = vec2[i];
  }
  */
  printf("data[i][j] address searching:\n");
  for(i=0;i<2;i++){
    for(j=0;j<length;j++)
      printf("%3d ",data[i][j]);
    printf("\n");
  }
  
  printf("*((int*)data + length*i + j) address searching:\n");
  for(i=0;i<4;i++){
    for(j=0;j<length;j++)
      printf("%3d ",*((int*)data + length*i + j) );
    printf("\n");
  }


  *(datt+0) = (int*)vec1 + length;
  *(datt+1) = (int*)vec1 + length*2;
  printf("*((int*)datt + length*i + j) address searching:\n");
  for(i=0;i<2;i++){
    for(j=0;j<length;j++)
      printf("%3d ",*((int*)datt + length*i + j) );
    printf("\n");
  }





  /* C cannot read data[][] as I hope
     try send data[][] back to fortran
  */


  /*
   * Create a new file using H5F_ACC_TRUNC access,
   * default file creation properties, and default file
   * access properties.
   */
  file = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  /*
   * Describe the size of the array and create the data space for fixed
   * size dataset. 
   */
  dimsf[0] = 2;//3;
  dimsf[1] = length;
  dataspace = H5Screate_simple(2, dimsf, NULL); 

  /* 
   * Define datatype for the data in the file.
   * We will store little endian INT numbers.
   */
  datatype = H5Tcopy(H5T_NATIVE_INT);
  status = H5Tset_order(datatype, H5T_ORDER_LE);

  /*
   * Create a new dataset within the file using defined dataspace and
   * datatype and default dataset creation properties.
   */
  dataset = H5Dcreate(file, dsetname, datatype, dataspace, H5P_DEFAULT);

  /*
   * Write the data to the dataset using default transfer properties.
   */
  status = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

  /*
   * Close/release resources.
   */
  H5Sclose(dataspace);
  H5Tclose(datatype);
  H5Dclose(dataset);
  H5Fclose(file);

  return;
}
