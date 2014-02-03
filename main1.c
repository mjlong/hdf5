#include <stdlib.h>
#include <stdio.h>
#include "hdf5.h"


void main(){

  hid_t       file, dataset;         /* file and dataset handles */
  hid_t       datatype, dataspace;   /* handles */
  hsize_t     dimsf[2];              /* dataset dimensions */
  herr_t      status;                             
  //  int**    data = (int**)malloc(2*sizeof(int*)); /* data to write */
  int *data[2];
  int datad[2][4];
  /* from experience so far, it seems that 
     int *data[2] is used to let data[0]=vec1
     int (*data)[2] is used to let data[0]=d0[0]
  */
  char   filename[16]="t2d.h5", dsetname[16]="name";
  int vec1[4];
  int vec2[4];
  int length = 4;
  int i,j;
  /* 
   * Data  and output buffer initialization. 
  */

  for(i=0;i<4;i++){
    *(vec1+i)=10+i;
    *(vec2+i)=20+i;
  }
  *(data-1) = vec1;
  *(data+0) = vec2;
  //  *(data+2) = vec2;


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
