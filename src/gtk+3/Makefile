ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/gtk+3# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/gtk+3/rules.mk
-include ${ROOT}/utils/rules.mk
-include ${DEP}

.PHONY: all asm clean
all: ${OBJ}
asm: ${ASM}
clean:
	rm -f *.exe ${OBJ} ${DEP} ${ASM}

basic.exe: ${d}/basic.o
packbuttun.exe: ${d}/packbuttun.o
drawing.exe: ${d}/drawing.o
