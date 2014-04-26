ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/mem/bw# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/mem/bw/rules.mk
-include ${ROOT}/utils/rules.mk
-include ${DEP}

.PHONY: all asm clean
all: ${OBJ}
asm: ${ASM}
clean:
	rm -f *.exe ${OBJ} ${DEP} ${ASM}

test_sumcopy.exe: ${d}/test_sumcopy.o ${d}/sumcopy.o
time_sumcopy.exe: ${d}/time_sumcopy.o ${d}/sumcopy.o			\
	${ROOT}/utils/utils.o ${ROOT}/utils/Table.o
