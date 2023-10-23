# -*- Makefile -*-

# aggiunto per compilare tutto il progetto in un colpo solo. Ivan.
all: csv2bin csv2bin_elia pricat

csv2bin: csv2bin.o strtoepoch.o
	gcc csv2bin.o strtoepoch.o -o csv2bin

# E' corretto che il target abbia lo stesso nome del file generato. Ivan.
csv2bin_elia: csv2bin_elia.o strtoepoch.o
	gcc csv2bin_elia.o strtoepoch.o -o csv2bin_elia

strtoepoch.o: strtoepoch.c strtoepoch.h
	gcc -c strtoepoch.c

csv2bin.o: csv2bin.c
	gcc -c csv2bin.c

csv2bin_elia.o: csv2bin.c
	gcc -c csv2bin_elia.c

clean:
	rm -f *.o csv2bin csv2bin_elia pricat

# Non e' perfetto. lasciare il file csv2bin intatto quando si cancellano tutti
# files oggetto e' poco pulito. conviene lasciare solo clean e cancellare
# entrambi gli eseguibili. Ivan.
cleane:
	rm -f *.o csv2bin_elia

pricat: pricat.o strtoepoch.o
	gcc pricat.o strtoepoch.o -o pricat

pricat.o: pricat.c
	gcc -c pricat.c
