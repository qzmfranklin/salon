#  THIS DIRECTORY
DIR00004:=${ROOT}/gtk+3
#  ALL C/C++ FILES IN THIS DIRECTORY (WITHOUT PATHNAME)
${DIR00004}C:=
${DIR00004}CPP:=packbuttun.cpp drawing.cpp basic.cpp 
#  DIRECTORY-SPECIFIC COMPILING FLAGS AND INCLUDE DIRECTORIES
${DIR00004}CFLAGS:=${CFLAGS}
${DIR00004}CXXFLAGS:=${CXXFLAGS}
${DIR00004}INCS:=${INCS} `pkg-config --cflags gtk+-3.0`
${DIR00004}LIBS:=${LIBS} `pkg-config --libs gtk+-3.0`

DEP+=${${DIR00004}CPP:%.cpp=${DIR00004}/%.d} ${${DIR00004}C:%.c=${DIR00004}/%.d} 
OBJ+=${${DIR00004}CPP:%.cpp=${DIR00004}/%.o} ${${DIR00004}C:%.c=${DIR00004}/%.o} 
ASM+=${${DIR00004}CPP:%.cpp=${DIR00004}/%.s} ${${DIR00004}C:%.c=${DIR00004}/%.s} 

${DIR00004}/%.o: ${DIR00004}/%.c
	${CC} -o $@ -c $< ${DEPFLAGS} ${${DIR00004}CFLAGS} ${${DIR00004}INCS}
${DIR00004}/%.s: ${DIR00004}/%.c
	${CC} -o $@ $< ${ASMFLAGS} ${${DIR00004}CFLAGS} ${${DIR00004}INCS}

${DIR00004}/%.o: ${DIR00004}/%.cpp
	${CXX} -o $@ -c $< ${DEPFLAGS} ${${DIR00004}CXXFLAGS} ${${DIR00004}INCS}
${DIR00004}/%.s: ${DIR00004}/%.cpp
	${CXX} -o $@ $< ${ASMFLAGS} ${${DIR00004}CXXFLAGS} ${${DIR00004}INCS}

# Linking pattern rule for this directory
%.exe: ${DIR00004}/%.o
	${CXX} -o $@ $^ ${${DIR00004}LIBS}
