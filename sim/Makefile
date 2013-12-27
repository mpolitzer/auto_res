CPATH=-I.

# .c, .h, .S
RESOURCES=main.c \
	layer1.c layer1.h \
	layer2.c layer2.h \
	layer3.c layer3.h

SRC=$(filter %.c, ${RESOURCES})
HDR=$(filter %.h, ${RESOURCES})
OBJ=${SRC:.c=.o}

CFLAGS=-march=native -O2 -Wall -g $(CPATH)
LDFLAGS=-O2 -lm
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
