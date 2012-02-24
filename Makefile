CC = clang
CFLAGS = -c -g -Wall -Werror -std=c++0x
LDFLAGS = -lstdc++ -levent
SOURCES = main.cc Ticker.cc Timestamp.cc
OBJECTS = $(SOURCES:.cc=.o)
EXCUTABLE = ticker

all: $(SOURCES) $(EXCUTABLE)

.PHONY: clean

$(EXCUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

Ticker.o: Ticker.h Ticker.cc Timestamp.h
Timestamp.o: Timestamp.h Timestamp.cc

clean:
	rm -rf *.o
