mkdir:
	mkdir -p bin

compile:
	gcc -ansi -pedantic -Wall -o bin/assembler \
	src/assembler.c \
	src/line/line.c \
	src/line/validator.c \
	src/scanner/analyzer.c \
	src/parser/parser.c \
	src/utils/file.c

clean:
	rm -rf bin