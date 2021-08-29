# Assembler

> (c) Ben Ukhanov (Aug 29, 2021)

Assembler is a program written in C programming language for study purposes.

NOTE: This is the documentation of the project.

## Introduction

The assembler has only 5 steps to complete the job:

1. Validate (Validating the assembly file)
2. Analyze (Scanning the assembly file)
3. Parse (Parsing the scanned syntax)
4. Translate (Translating the instructions)
5. Generate (Generating the output files, e.g. test.ob, test.ext, and test.ent)

## Project Structure

The project has more than 1000 lines of code! A lof of effort put to keep the code clean as possible.

```
├── src
│   ├── constants (common code, e.g. logger, messages, etc)
│   ├── generator (output files generator, e.g. test.ob, test.ext, and test.ent)
│   ├── line (linked list of the lines, and validators of the line)
│   ├── parser (syntax parsing of the assembly file)
│   ├── scanner (reader of the assmebly file)
│   ├── symbol (symbol table, called as linked symbol because used as linked list)
│   ├── translator (the translator of the instructions)
│   └── utils (helpers for dealing with the line and files)
└── tests (assembly test files)
```

## Quickstart

To run the assembler, use this command:

```
./run.sh
```

For example, this is how it's done in `run.sh`:

```
./bin/assembler ./tests/test.as
```

There's an option to use the Makefile directly as well:

```
make mkdir

make compile

make clean
```

## Example

```
╰─$ ./run.sh
rm -rf bin
mkdir -p bin
#---------------------------------------------------#
# Build Assembler
#---------------------------------------------------#
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
#---------------------------------------------------#
# Run Assembler
#---------------------------------------------------#
# File: ./tests/test.as
# Validating...
# Analyzing...
# Parsing...
# Translating...
# Generating...
# Generated.
```

## Missing Features

1. Not validating the operands data (only registers validated).
2. Data image must be written after code image (except .extern/.entry).
3. No warnings about commas before or after operands (but it works!).

## Challenges

1. How to keep the solution simple and readable as much as possible.
2. How to keep the project structure simple and not complicated.
3. How to keep the good practices while working with C programming language (memory management, etc).

## What I Learned

I spent 2 months on working on this project in my spare time on evenings and weekends after work.

I learned a lot:

1. About compilers and syntax parsing.
2. About assembly language.
3. About C programming language.

# License

[MIT](https://choosealicense.com/licenses/mit/)
