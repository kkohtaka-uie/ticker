CC = clang
CFLAGS = -c -g -Wall -Werror
LDFLAGS = -lstdc++ -levent
SOURCES = main.cc
OBJECTS = $(SOURCES:.cc=.o)
EXCUTABLE = ticker

all: $(SOURCES) $(EXCUTABLE)

.PHONY: clean

$(EXCUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
