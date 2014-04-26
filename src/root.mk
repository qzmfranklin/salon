#	PROJECT-WIDE COMMON COMPILING FLAGS 
CC		:=icpc
CFLAGS 		:=-O3 -Wall -restrict -openmp -DNDEBUG \
	`pkg-config --cflags gtk+-3.0`

CXX		:=${CC}
CXXFLAGS	:=${CFLAGS}
#       PROJECT-WIDE DEFAULT LINKING LIBRARIES AND INCLUDE DIRECTORIES
INCS		:=-iquote ${ROOT}
LIBS		:=-lfftw3_omp -lfftw3 -mkl \
	`pkg-config --libs gtk+-3.0`


#	INTERNAL VARIABLES
OBJ		:=# .o files
DEP		:=# .d files
ASM		:=# .s files
DEPFLAGS	:=-MMD -MP# preprocessor generates .d files
ASMFLAGS	:=-S -fsource-asm# source code commented assembly code 
.SUFFIXES:
