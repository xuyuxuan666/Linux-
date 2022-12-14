CFLAGS := -g -Wall -Wextra
LDFLAGS := -L.
LDLIBS := -lseg


all: client

client.o: client.c segdef.h


clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

indent:
	indent -linux -i4 -nut -ts2 *.c

.PHONY: all clean indent