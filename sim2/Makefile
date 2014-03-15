CPATH=-I.

# .c, .h, .S
RESOURCES=main.c \
	  l1.c l1.h \
	  l2.c l2.h \
	  l3.c l3.h \
	  report.c report.h \
	  cli.c cli.h cliconf.h

SRC=$(filter %.c, ${RESOURCES})
HDR=$(filter %.h, ${RESOURCES})
OBJ=${SRC:.c=.o}

CFLAGS=-march=native -std=c99 -O0 -Wall -g $(CPATH)
LDFLAGS=-O0 -lm
EXE=main

.PHONY: all clean
all: .depend.mk $(EXE)
zip: Makefile $(SRC) $(HDR)
	zip -r mypackage.zip $^

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(EXE)
$(OBJ): %.o: %.c
.depend.mk: $(RESOURCES) Makefile
	$(CC) -MM $(CFLAGS) $(SRC) > .depend.mk
clean:
	rm -f $(EXE) $(OBJ)
-include .depend.mk
