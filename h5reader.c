#include "stdlib.h"
#include "hdf5.h"

void readh5_(char* filename, char* dsetname, double* vec){

  hid_t       file_id, dataset_id;  /* identifiers */
  herr_t      status;

  file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
  dataset_id = H5Dopen(file_id, dsetname, H5P_DEFAULT);
  status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, (double*)vec);
  status = H5Dclose(dataset_id);
  status = H5Fclose(file_id);



}
