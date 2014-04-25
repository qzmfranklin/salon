ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/magic3# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/magic3/rules.mk
-include ${ROOT}/utils/rules.mk
-include ${DEP}

.PHONY: all asm clean
all: ${OBJ}
asm: ${ASM}
clean:
	rm -f *.exe ${OBJ} ${DEP} ${ASM}

test_magic3.exe: ${d}/test_magic3.o ${d}/magic3.o
