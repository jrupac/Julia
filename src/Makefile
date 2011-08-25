CC=g++
TARGET=julia
INPUT_SRCS=main.cpp bmp.cpp
INPUT_OBJS=$(INPUT_SRCS:.cpp=.o)

CFLAGS=-o $(TARGET)
DEBUG=-g
LIBS=

all: $(INPUT_OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^

debug: $(INPUT_OBJS)
	$(CC) $(DEBUG) $(CFLAGS) $(LIBS) $^

clean:
	rm -f $(TARGET) $(INPUT_OBJS)

