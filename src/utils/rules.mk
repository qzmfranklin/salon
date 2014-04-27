#  THIS DIRECTORY
DIR00014:=${ROOT}/utils
#  ALL C/C++ FILES IN THIS DIRECTORY (WITHOUT PATHNAME)
${DIR00014}C:=
${DIR00014}CPP:=test_timestat.cpp test_table.cpp test_stat.cpp utils.cpp Table.cpp 
#  DIRECTORY-SPECIFIC COMPILING FLAGS AND INCLUDE DIRECTORIES
${DIR00014}CFLAGS:=${CFLAGS}
${DIR00014}CXXFLAGS:=${CXXFLAGS}
${DIR00014}INCS:=${INCS}
${DIR00014}LIBS:=${LIBS}

DEP+=${${DIR00014}CPP:%.cpp=${DIR00014}/%.d} ${${DIR00014}C:%.c=${DIR00014}/%.d} 
OBJ+=${${DIR00014}CPP:%.cpp=${DIR00014}/%.o} ${${DIR00014}C:%.c=${DIR00014}/%.o} 
ASM+=${${DIR00014}CPP:%.cpp=${DIR00014}/%.s} ${${DIR00014}C:%.c=${DIR00014}/%.s} 

${DIR00014}/%.o: ${DIR00014}/%.c
	${CC} -o $@ -c $< ${DEPFLAGS} ${${DIR00014}CFLAGS} ${${DIR00014}INCS}
${DIR00014}/%.s: ${DIR00014}/%.c
	${CC} -o $@ $< ${ASMFLAGS} ${${DIR00014}CFLAGS} ${${DIR00014}INCS}

${DIR00014}/%.o: ${DIR00014}/%.cpp
	${CXX} -o $@ -c $< ${DEPFLAGS} ${${DIR00014}CXXFLAGS} ${${DIR00014}INCS}
${DIR00014}/%.s: ${DIR00014}/%.cpp
	${CXX} -o $@ $< ${ASMFLAGS} ${${DIR00014}CXXFLAGS} ${${DIR00014}INCS}

# Linking pattern rule for this directory
%.exe: ${DIR00014}/%.o
	${CXX} -o $@ $^ ${${DIR00014}LIBS}
