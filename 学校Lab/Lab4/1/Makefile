CFLAGS := -g -Wall -Wextra
LDFLAGS := -L.
LDLIBS := -lseg

BIN := segserv segclt segclt_old
LIB := libseg.a

all: $(LIB) $(BIN)

#libseg.o: libseg.c libseg.h
#segserv.o: segserv.c segdef.h
segclt.o: segclt.c segdef.h
segclt_old.o: segclt_old.c segdef.h

#libseg.a: libseg.o
#	$(AR) r libseg.a libseg.o

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

indent:
	indent -linux -i4 -nut -ts2 *.c

.PHONY: all clean indent
