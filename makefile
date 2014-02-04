#========options========================
apptype=fortran
CC=h5cc
FC=h5fc


ifeq ($(apptype),fortran)
  MC=$(FC)
  LFLAGS=
endif
ifeq ($(apptype),C)
  MC=$(CC)
  LFLAGS=-lgfortran
endif


FFLAGS = -c
CFLAGS = -c

EXEC = sample
EXEF = samplf
CSRC = h5writer.c
COBJ = $(CSRC:.c=.o)
FMSRC = main.f90
CMSRC = main.c
FMOBJ = $(FMSRC:.f90=.o)
CMOBJ = $(CMSRC: .c=.o)

all: $(EXEC) $(EXEF)

$(EXEC): $(CMOBJ) $(COBJ) 
	$(MC) $(LFLAGS)  $^ -o $@ $(LFLAGS)
$(CMOBJ):$(CMSRC)
	$(CC) $(CFLAGS)  $^ -o $@
$(EXEF): $(FMOBJ) $(COBJ)
	$(MC) $(LFLAGS)  $^ -o $@ $(LFLAGS)
$(FMOBJ):$(FMSRC)
	$(FC) $(FFLAGS)  $^ -o $@
$(COBJ): $(CSRC)
	$(CC) $(CFLAGS)  $^ -o $@
clean:
	rm -rf $(EXE) *.o *.mod *~
