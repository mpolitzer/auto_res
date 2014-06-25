CPATH=-I.

TARGET=radio_drv_test
# .c, .h, .S
RESOURCES=$(TARGET).c           \
	  radio_dev.c   radio_dev.h \
	  radio_drv.c   radio_drv.h

SRC=$(filter %.c, ${RESOURCES})
HDR=$(filter %.h, ${RESOURCES})
OBJ=${SRC:.c=.o}

CFLAGS= -std=c99 -O2 -Wall -g $(CPATH)
LDFLAGS=-O2 -lm
EXE=$(TARGET)

.PHONY: all test clean
all: $(EXE)
zip: Makefile $(SRC) $(HDR)
	zip -r $(TARGET).zip $^

test: $(EXE)
	./$<

$(EXE): .depend.mk $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(EXE)

$(OBJ): %.o: %.c

.depend.mk: $(RESOURCES) Makefile
	$(CC) -MM $(CFLAGS) $(SRC) > .depend.mk

clean:
	rm -f $(EXE) $(OBJ)

-include .depend.mk
