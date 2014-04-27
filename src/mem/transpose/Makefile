ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/mem/transpose# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/mem/transpose/rules.mk
-include ${ROOT}/utils/rules.mk
-include ${DEP}

.PHONY: all asm clean
all: ${OBJ}
asm: ${ASM}
clean:
	rm -f *.exe ${OBJ} ${DEP} ${ASM}

test_transpose.exe: ${d}/test_transpose.o ${d}/transpose.o

time_transpose.exe: ${d}/time_transpose.o ${d}/transpose.o \
	${ROOT}/utils/Table.o
