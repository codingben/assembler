mkdir:
	mkdir -p bin

compile:
	gcc -ansi -pedantic -Wall src/assembler.c src/line/line.c src/scanner/analyzer.c src/parser/parser.c src/utils/file.c -o bin/assembler

clean:
	rm -rf bin