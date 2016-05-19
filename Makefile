AUXFILES := LICENSE README.md Makefile

SRCFILES := $(wildcard *.c)
HDRFILES := $(wildcard *.h)

OBJFILES := $(patsubst %.c, %.o, $(SRCFILES))

EXEC := main

.PHONY: all clean mrproper

CC := clang
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	-Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -g -std=c99 $(WARNINGS)

all: $(EXEC)

$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(EXEC))

