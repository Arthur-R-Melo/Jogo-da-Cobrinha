CC = gcc
CFLAGS = -Wall -std=c99
TARGET = snake
LIBS = -lraylib -lm
OBJS = jogo.o snake.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

jogo.o:
	$(CC) $(CFLAGS) -c jogo.c

snake.o:
	$(CC) $(CFLAGS) -c snake.c

teste: 
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all teste clean