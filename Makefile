CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = main

SOURCES = $(shell find . -name "*.c" -not -path "./.vscode/*")

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)