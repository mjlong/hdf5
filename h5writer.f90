module h5writer

  use HDF5
  implicit none
Contains

  subroutine writeh5(filename, dsetname, vec1, dname1, vec2, dname2, vec3, dname3)
    character(LEN=*), intent(in)      :: filename, dsetname
    real(8), dimension(:), intent(in) :: vec1
    character(LEN=*), intent(in)      :: dname1
    real(8), dimension(:), intent(in),&
                             optional :: vec2, vec3
    character(LEN=*), intent(in),& 
                             optional :: dname2, dname3
    integer                           :: length, num
!===============================================================================
!HDF5 API arguments
    integer, parameter:: RANK = 2
    real(8), allocatable              :: dset_data(:,:)
    INTEGER(HID_T) :: file_id       ! File identifier
    INTEGER(HID_T) :: dset_id       ! Dataset identifier
    integer(HID_T) :: dspace_id
    INTEGER(HSIZE_T), DIMENSION(RANK) :: data_dims
    INTEGER     ::   error ! Error flag
    INTEGER     ::  i, j

    length  = size(vec1)
    num = 1
    if(present(vec2).and.present(dname2)) num = num + 1
    if(present(vec3).and.present(dname3)) num = num + 1

    allocate(dset_data(length,num))
    
    !
    ! Initialize FORTRAN interface.
    !
    CALL h5open_f(error)

  
    !
    ! Create a new file using default properties.
    !
    CALL h5fcreate_f(filename, H5F_ACC_TRUNC_F, file_id, error)

    !
    ! Create the dataspace.
    !
    CALL h5screate_simple_f(RANK, data_dims, dspace_id, error)
  
    !
    ! Create the dataset with default properties.
    !
    CALL h5dcreate_f(file_id, dsetname, H5T_NATIVE_INTEGER, dspace_id, &
         dset_id, error)

    !
    ! Write the dataset.
    !
    data_dims(1) = length
    data_dims(2) = num
    CALL h5dwrite_f(dset_id, H5T_NATIVE_INTEGER, dset_data, data_dims, error)

    !
    ! Close the dataset.
    !
    CALL h5dclose_f(dset_id, error)
  
    !
    ! Terminate access to the data space.
    !
    CALL h5sclose_f(dspace_id, error)

    !
    ! Close the file.
    !
    CALL h5fclose_f(file_id, error)
  
    !
    ! Close FORTRAN interface.
    !
    CALL h5close_f(error)

  end subroutine writeh5
  
end module h5writer
