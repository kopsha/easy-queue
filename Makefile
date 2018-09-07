HEADERS = easy_queue.h
SOURCES = easy_queue.c main.c
OBJECTS = $(SOURCES:.c=.o)

# TARGETS
TARGET_APP = easy_queue
.PHONY: all
all: $(TARGET_APP)

# COMPILER AND LINKER SETTINGS
CC		= gcc
CFLAGS 	= -std=gnu99 -pedantic -Wall -O2
LIBPATH = -L.
LIBS	= 
LDFLAGS = $(LIBPATH) $(LIBS)

$(SOURCES):$(HEADERS)

%.o: %.c
		$(CC) -c $(CFLAGS) $*.c

$(TARGET_APP): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET_APP)

clean:
	rm -f $(OBJECTS) $(TARGET_APP) a.out
