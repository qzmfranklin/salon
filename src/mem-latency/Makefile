ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/mem-latency# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/mem-latency/rules.mk
-include ${ROOT}/utils/rules.mk
-include ${DEP}

.PHONY: all asm clean
all: ${OBJ}
asm: ${ASM}
clean:
	rm -f *.exe ${OBJ} ${DEP} ${ASM}
time_walk.exe: ${d}/time_walk.o ${d}/array_walk.o ${d}/latency_utils.o 
table_latency.exe: ${d}/table_latency.o ${d}/latency.o ${d}/dummy.o ${d}/latency_utils.o	\
	${ROOT}/utils/utils.o ${ROOT}/utils/Table.o
