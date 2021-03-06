#include "hdf5.h"
#define FILE        "SDS.h5"
#define DATASETNAME "IntArray" 
#define NX     5                      /* dataset dimensions */
#define NY     6
#define NZ     4
#define RANK   3

int
main (void)
{
  hid_t       file, dataset;         /* file and dataset handles */
  hid_t       datatype, dataspace;   /* handles */
  hsize_t     dimsf[RANK];              /* dataset dimensions */
  herr_t      status;                             
  int         data[NX][NY][NZ];          /* data to write */
  int         i, j, k;

  /* 
   * Data  and output buffer initialization. 
   */
  for (j = 0; j < NX; j++) {
    for (i = 0; i < NY; i++){
      for (k = 0; k < NZ; k++)
	data[j][i][k] = 100*j + 10*i + k;
    }
  }     
  /*
   * Create a new file using H5F_ACC_TRUNC access,
   * default file creation properties, and default file
   * access properties.
   */
  file = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  /*
   * Describe the size of the array and create the data space for fixed
   * size dataset. 
   */
  dimsf[0] = NX;
  dimsf[1] = NY;
  dimsf[2] = NZ;
  dataspace = H5Screate_simple(RANK, dimsf, NULL); 

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
  dataset = H5Dcreate(file, DATASETNAME, datatype, dataspace, H5P_DEFAULT);

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
 
  return 0;
}     
