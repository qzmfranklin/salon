#	PROJECT-WIDE COMMON COMPILING FLAGS 
CC		:=icpc
CFLAGS 		:=-O3 -Wall -restrict -openmp

CXX		:=${CC}
CXXFLAGS	:=${CFLAGS}
#       PROJECT-WIDE DEFAULT LINKING LIBRARIES AND INCLUDE DIRECTORIES
INCS		:=-iquote ${ROOT}
LIBS		:=

#	INTERNAL VARIABLES
OBJ		:=# .o files
DEP		:=# .d files
ASM		:=# .s files
DEPFLAGS	:=-MMD -MP# preprocessor generates .d files
ASMFLAGS	:=-S -fsource-asm# source code commented assembly code 
.SUFFIXES:
