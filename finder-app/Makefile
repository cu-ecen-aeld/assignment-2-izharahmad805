# Makefile for AESD Assignment 2 "writer" utility
#
# Usage:
#   Native build:        make
#   Cross compile build: make CROSS_COMPILE=aarch64-none-linux-gnu-
#   Clean:                make clean

# CROSS_COMPILE is empty by default (native build). Pass it on the
# command line, e.g. CROSS_COMPILE=aarch64-none-linux-gnu- , to cross
# compile. Note the trailing '-' is expected to be part of the value.
CROSS_COMPILE ?=

CC := $(CROSS_COMPILE)gcc

CFLAGS ?= -Wall -Wextra -g -O0
LDFLAGS ?=

TARGET := writer
SRCS := writer.c
OBJS := $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
