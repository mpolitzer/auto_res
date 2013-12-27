CPATH=-I.
#GL=shader.c shader.h util.c opengl.h
#DS=oco_string.c oco_string.h
#SRLA=srv4_sse.c srm4_sse.c
#GEOM=sphere.c sphere.h vertex.h
#RESOURCES=$(addprefix gfx/, ${GL})\
#	  $(addprefix cds/, ${DS})\
#	  $(addprefix la/, ${SRLA})\
#	  $(addprefix geom/, ${GEOM})\
#	  main.c

# .c, .h, .S
RESOURCES=main.c

SRC=$(filter %.c, ${RESOURCES})
HDR=$(filter %.h, ${RESOURCES})
OBJ=${SRC:.c=.o}

CFLAGS=-march=native -O2 -Wall -g $(CPATH)
LDFLAGS=-O2 -lm
#PKG=sdl2 glew gl
#CFLAGS +=`pkg-config $(PKG) --cflags`
#LDFLAGS+=`pkg-config $(PKG) --static --libs`
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
