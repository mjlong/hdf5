module h5writer

  implicit none

  interface writeh5
     module procedure writeh5_1d
     module procedure writeh5_2d
     module procedure writeh5_3d
  end interface writeh5


Contains

  subroutine writeh5_2d_t(filename, dsetname, vec1, vec2)
    character(LEN=*), intent(in)      :: filename, dsetname
    integer                           :: length, num


    do i = 1, num
       dset_data(:,i) = pnt(i)
    end do
    
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
