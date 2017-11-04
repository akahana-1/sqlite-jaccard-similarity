CC = gcc
CFLAGS = -Wall -g -fPIC -shared -Isqlite3

TARGET = jaccard.so
SOURCES = $(wildcard jaccard*.c)

.PHONY: clean all

all: $(TARGET)

$(TARGET): %.so: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
