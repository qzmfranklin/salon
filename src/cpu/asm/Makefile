ROOT    :=/media/qzmfranklin/data/git/salon/src
d       :=${ROOT}/cpu/asm# this directory
-include ${ROOT}/root.mk
-include ${ROOT}/cpu/asm/rules.mk
-include ${DEP}

cpuid.exe: ${d}/cpuid.o

addmany.exe: addmany.s
	${CC} -o $@ $<

addtwo.exe: addtwo.s
	${CC} -o $@ $<
