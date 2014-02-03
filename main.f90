program main
  implicit none
!  real(8), dimension(:), allocatable :: array1
!  real(8), dimension(:), allocatable :: array2
  real(8), dimension(4,2)            :: array
  real(8), dimension(8)              :: longArray
  real(8), dimension(4)              :: vec1, vec2
  integer                            :: nrow, ncol
  integer                            :: i,j
  character(LEN=16)                  :: filename, dsetname

  filename="fcc.h5"
  filename(7:7)=char(0)
  dsetname="fcc"
  dsetname(4:4)=char(0)
  nrow = 2
  ncol = 4
!  allocate(array1(ncol))
!  allocate(array2(ncol))

!  do j = 1, ncol
!     array1(j) = 10.0_8 + j
!     array2(j) = 20.0_8 + j
!  end do

  do i = 1, nrow
     do j = 1, ncol
        array(j,i) = 300 + 10*i + j
     end do
  end do
  vec1(:) = array(:,1)
  vec2(:) = array(:,2)
  longArray(:) = 4
  vec1(:) = longArray(1:4)
  vec2(:) = longArray(5:8)

!  do i = 1, ncol
!     vec1(i) = 10*i + 1
!     vec2(i) = 10*i + 2
!  end do

  call writeh5_nxm(filename, dsetname, array, nrow, ncol)
  call writeh5_nxm(filename, dsetname, longArray, nrow, ncol)  
end program main
