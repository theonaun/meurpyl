EXEC    = pyhobble_server
DESTDIR = /usr/local/bin
SRCDIR  = ./src
INCDIR  = ./include
STATDIR = ./static
CC      = gcc
CFLAGS  = -std=c11 -g -I$(INCDIR) #-Wall TODO
SOURCES = $(wildcard ./src/*.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean install uninstall

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

clean:
	rm -f $(EXEC) $(OBJECTS)

install:
	mkdir /etc/$(EXEC)
	cp ./$(EXEC) $(DESTDIR)/$(EXEC)
	cp $(STATDIR)/base.conf /etc/$(EXEC)/$(EXEC).conf

uninstall:
	rm -rf $(DESTDIR)/$(EXEC)
	rm -rf /etc/$(EXEC)


