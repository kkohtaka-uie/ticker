CC = clang
CFLAGS = -c -Wall
LDFLAGS = -lstdc++
SOURCES = main.cc
OBJECTS = $(SOURCES:.cc=.o)
EXCUTABLE = ticker

all: $(SOURCES) $(EXCUTABLE)

.PHONY: clean

$(EXCUTABLE): $(OBJECTS) Makefile
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
