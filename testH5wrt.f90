PROGRAM main

!  use h5writer

  IMPLICIT NONE
  
  character(LEN=10) :: filename, dname
  real(8), target, dimension(11) :: vec1, vec2, vec3, data
  real(8), pointer               :: pnt(3)
  

  filename = "th5writer.h5"
  dname = "name"
  data = (/0,1,2,3,4,5,6,7,8,9,10/)*0.1*3.14*2
  vec1 = data
  vec2 = sin(data)
  vec3 = cos(data)
  pnt(1) => vec1
  pnt(2) => vec2
  pnt(3) => vec3
!  call writeh5(filename, dname, pnt)


end PROGRAM main
