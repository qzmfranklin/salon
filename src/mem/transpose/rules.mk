#  THIS DIRECTORY
DIR:=${ROOT}/mem/transpose
#  ALL C/C++ FILES IN THIS DIRECTORY (WITHOUT PATHNAME)
${DIR}C:=
${DIR}CPP:=transpose.cpp test_transpose.cpp time_transpose.cpp
#  DIRECTORY-SPECIFIC COMPILING FLAGS AND INCLUDE DIRECTORIES
${DIR}CFLAGS:=${CFLAGS}
${DIR}CXXFLAGS:=${CXXFLAGS}
${DIR}INCS:=${INCS}
${DIR}LIBS:=${LIBS}

DEP+=${${DIR}CPP:%.cpp=${DIR}/%.d} ${${DIR}C:%.c=${DIR}/%.d} 
OBJ+=${${DIR}CPP:%.cpp=${DIR}/%.o} ${${DIR}C:%.c=${DIR}/%.o} 
ASM+=${${DIR}CPP:%.cpp=${DIR}/%.s} ${${DIR}C:%.c=${DIR}/%.s} 

${DIR}/%.o: ${DIR}/%.c
	${CC} -o $@ -c $< ${DEPFLAGS} ${${DIR}CFLAGS} ${${DIR}INCS}
${DIR}/%.s: ${DIR}/%.c
	${CC} -o $@ $< ${ASMFLAGS} ${${DIR}CFLAGS} ${${DIR}INCS}

${DIR}/%.o: ${DIR}/%.cpp
	${CXX} -o $@ -c $< ${DEPFLAGS} ${${DIR}CXXFLAGS} ${${DIR}INCS}
${DIR}/%.s: ${DIR}/%.cpp
	${CXX} -o $@ $< ${ASMFLAGS} ${${DIR}CXXFLAGS} ${${DIR}INCS}

# Linking pattern rule for this directory
%.exe: ${DIR}/%.o
	${CXX} -o $@ $^ ${${DIR}LIBS}
