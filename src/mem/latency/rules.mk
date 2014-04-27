#  THIS DIRECTORY
DIR00006:=${ROOT}/mem/latency
#  ALL C/C++ FILES IN THIS DIRECTORY (WITHOUT PATHNAME)
${DIR00006}C:=
${DIR00006}CPP:=array_walk.cpp latency_utils.cpp latency.cpp table_latency.cpp time_walk.cpp hist_latency.cpp dummy.cpp 
#  DIRECTORY-SPECIFIC COMPILING FLAGS AND INCLUDE DIRECTORIES
${DIR00006}CFLAGS:=${CFLAGS}
${DIR00006}CXXFLAGS:=${CXXFLAGS}
${DIR00006}INCS:=${INCS}
${DIR00006}LIBS:=${LIBS}

DEP+=${${DIR00006}CPP:%.cpp=${DIR00006}/%.d} ${${DIR00006}C:%.c=${DIR00006}/%.d} 
OBJ+=${${DIR00006}CPP:%.cpp=${DIR00006}/%.o} ${${DIR00006}C:%.c=${DIR00006}/%.o} 
ASM+=${${DIR00006}CPP:%.cpp=${DIR00006}/%.s} ${${DIR00006}C:%.c=${DIR00006}/%.s} 

${DIR00006}/%.o: ${DIR00006}/%.c
	${CC} -o $@ -c $< ${DEPFLAGS} ${${DIR00006}CFLAGS} ${${DIR00006}INCS}
${DIR00006}/%.s: ${DIR00006}/%.c
	${CC} -o $@ $< ${ASMFLAGS} ${${DIR00006}CFLAGS} ${${DIR00006}INCS}

${DIR00006}/%.o: ${DIR00006}/%.cpp
	${CXX} -o $@ -c $< ${DEPFLAGS} ${${DIR00006}CXXFLAGS} ${${DIR00006}INCS}
${DIR00006}/%.s: ${DIR00006}/%.cpp
	${CXX} -o $@ $< ${ASMFLAGS} ${${DIR00006}CXXFLAGS} ${${DIR00006}INCS}

# Linking pattern rule for this directory
%.exe: ${DIR00006}/%.o
	${CXX} -o $@ $^ ${${DIR00006}LIBS}
