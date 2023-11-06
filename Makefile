# -*- Makefile -*-

# aggiunto per compilare tutto il progetto in un colpo solo. Ivan.
all: csv2bin pricat emacalc

emacalc: emacalc.o
	gcc emacalc.o strtoepoch.o -o emacalc

emacalc.o: emacalc.c
	gcc -c emacalc.c

csv2bin: csv2bin.o strtoepoch.o
	gcc csv2bin.o strtoepoch.o -o csv2bin

strtoepoch.o: strtoepoch.c strtoepoch.h
	gcc -c strtoepoch.c

csv2bin.o: csv2bin.c
	gcc -c csv2bin.c

clean:
	rm -f *.o csv2bin pricat date2epoch emacalc

pricat: pricat.o strtoepoch.o
	gcc pricat.o strtoepoch.o -o pricat

pricat.o: pricat.c
	gcc -c pricat.c
