#include "hdf5.h"

void writeh5_nx2_t_(char *filename, char *dsetname, double *vec1, int *num_vec, int *length){

  hid_t       file, dataset;         /* file and dataset handles */
  hid_t       datatype, dataspace;   /* handles */
  hsize_t     dimsf[2];              /* dataset dimensions */
  herr_t      status;                             
  //  double**    data = (double**)malloc(2*sizeof(double*)); /* data to write */
  int i,j; 

  /* 
   * Data  and output buffer initialization. 
  */
  printf("*((int*)vec1 + length*i + j) address searching:\n");
  for(i=0;i<*num_vec;i++){
    for(j=0;j<*length;j++)
      printf("%3.1f ",*((double*)vec1 + *length*i + j) );
    printf("\n");
  }
  



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
  dimsf[0] = *num_vec;
  dimsf[1] = *length;
  dataspace = H5Screate_simple(2, dimsf, NULL); 

  /* 
   * Define datatype for the data in the file.
   * We will store little endian INT numbers.
   */
  datatype = H5Tcopy(H5T_NATIVE_DOUBLE);
  status = H5Tset_order(datatype, H5T_ORDER_LE);

  /*
   * Create a new dataset within the file using defined dataspace and
   * datatype and default dataset creation properties.
   */
  dataset = H5Dcreate(file, dsetname, datatype, dataspace, H5P_DEFAULT);

  /*
   * Write the data to the dataset using default transfer properties.
   */
  status = H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, (double*)vec1);

  /*
   * Close/release resources.
   */
  H5Sclose(dataspace);
  H5Tclose(datatype);
  H5Dclose(dataset);
  H5Fclose(file);

  return;
}
