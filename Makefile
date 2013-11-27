PREFIX=msp430-
mcu=msp430f2121

CC=$(PREFIX)gcc
OBJCOPY=$(PREFIX)objcopy
SIZE=$(PREFIX)size

CPATH=-I.
RESOURCES=main.c $(mcu)/irqs.c

SRC=$(filter %.c, ${RESOURCES})
HDR=$(filter %.h, ${RESOURCES})
OBJ=${SRC:.c=.o}

CFLAGS=-O2 -Wall -g $(CPATH) -mmcu=$(mcu)
LDFLAGS=-O2 -lm -mmcu=$(mcu)
EXE=main
HEX=$(EXE).hex

.PHONY: all clean
all: .depend.mk size $(EXE) $(HEX)
zip: Makefile $(SRC) $(HDR)
	zip -r mypackage.zip $^

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(EXE)
$(HEX): $(EXE)
	$(OBJCOPY) -I ihex $< $@
size: $(EXE)
	$(SIZE) $<
$(OBJ): %.o: %.c
.depend.mk: $(RESOURCES) Makefile
	$(CC) -MM $(CFLAGS) $(SRC) > .depend.mk
clean:
	rm -f $(EXE) $(OBJ)
-include .depend.mk
