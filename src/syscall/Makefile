ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/syscall# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/syscall/rules.mk
-include ${DEP}

.PHONY: all asm clean
all: ${OBJ}
asm: ${ASM}
clean:
	rm -f *.exe ${OBJ} ${DEP} ${ASM}

syscall.exe: ${d}/syscall.o
