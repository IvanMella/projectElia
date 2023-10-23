# Set di programmi per il calcolo dell'EMA

### csv2bin:

Converte i files CSV in files Binari adatti alle sucessive elaborazioni (da rinominare in csvtopri)

Parametri:

- File csv in ingresso
- file pri in uscita

Sintassi:

	csvtopri file.csv [file.pri]

### pricat
Stampa sullo stdout il contenuto di un file binario primario cioe che ha 1 data e 5 campi double

Parametri:

- File pri in ingresso

Sintassi:

	pricat file.pri
	pricat file.pri --ema [int]...
---scusa per int si intende intero o intervallo???--


## TODO:

### emacat
Stampa sullo stdout il contenuto di un file binario che contiene l'ema cioe che ha 1 data e 6 campi double

Parametri:

- File pri in ingresso

Sintassi:

	emacat file.ema

### emacalc
Calcola l'ema partendo da un file binario primario.

Parametri:

- File pri in ingresso
- File ema in uscita

Sintassi:

	emacalc file.pri [file.ema]


## estensioni dei files:

* .csv: comma separated text values
* .pri: Files binari primari
* .ema: Files secondari con l'ema

[Guida di Markdown] (https://www.markdownguide.org).

*Ivan Mella 10/2023.*


