SRC:=abs.tex \
	sec1.tex sec2.tex sec3.tex sec4.tex sec5.tex sec6.tex\
	app1.tex \
	bib1.tex
DVI:=main.dvi $(SRC:%.tex=%.dvi)
PDF:=out.pdf

all: ${PDF}

clean:
	rm -f *.aux *.dvi *.log *.toc *.out log
cleanxx: clean
	rm -f ${PDF}

${PDF}: main.dvi ${DVI}
	@dvipdf $< $@

main.dvi: main.tex ${SRC}
	@latex $< $@ >log
	@latex $< $@ >log
	@latex $< $@ >log

%.dvi: %.tex
	@latex $< $@ >log
	@latex $< $@ >log
	@latex $< $@ >log
