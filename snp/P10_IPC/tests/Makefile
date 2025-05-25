

# Path to the testlib
SNP_TESTLIB ?= ../../../testlib

# Source files
SOURCES = tests.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Compiler and linker settings
CC = gcc
CFLAGS = -Wall -pedantic -std=c99
CFLAGS += -I../src -I$(SNP_TESTLIB)/include
LDFLAGS = -L$(SNP_TESTLIB)/lib

# Target path
TARGET = runtest

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) -lcunit -lsnptest 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
