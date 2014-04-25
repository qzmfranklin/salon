ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/cpu# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/cpu/rules.mk
-include ${ROOT}/utils/rules.mk
-include ${DEP}

.PHONY: all asm clean
all: ${OBJ}
asm: ${ASM}
clean:
	rm -f *.exe ${OBJ} ${DEP} ${ASM}

allis.exe: ${d}/allis.o
sin.exe: ${d}/sin.o ${ROOT}/utils/Table.o
fft.exe: ${d}/fft.o ${ROOT}/utils/Table.o
