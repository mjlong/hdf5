hdf5
====
test examples


========================
h5writer.c
can be called by C or Fortran to write 2D hdf5 file. 
It accepts array pointer with no restriction of the 2 lengths. 
However, the 2D array must be a continuous block in RAM no matter it is a 2D array or long vector. 
