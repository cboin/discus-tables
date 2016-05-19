AUXFILES := LICENSE README.md Makefile

OBJFILES := tables.o main.o

.PHONY: all clean mrproper

CC := clang
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	-Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -g -std=c99 $(WARNINGS)

all: main

main.o: main.c tables.c tables.h
	$(CC) $(CFLAGS) -o $@ $<

tables.o: table.c tables.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(EXEC))

