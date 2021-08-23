mkdir:
	mkdir -p bin

compile:
	gcc -ansi -pedantic -Wall -o bin/assembler \
	src/assembler.c \
	src/line/line.c \
	src/line/validator.c \
	src/scanner/analyzer.c \
	src/parser/parser.c \
	src/symbol/symbol.c \
	src/translator/translator.c \
	src/generator/generator.c \
	src/utils/file_helper.c \
	src/utils/line_helper.c

clean:
	rm -rf bin
