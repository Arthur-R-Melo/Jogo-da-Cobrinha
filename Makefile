CC = gcc
CFLAGS = -Wall -std=c99
TARGET = snake.exe
LIBS = -lraylib -lm
OBJS = jogo.o snake.o main.o graphic.o coord.o food.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

jogo.o: jogo.c jogo.h
	$(CC) $(CFLAGS) -c jogo.c

snake.o: snake.c snake.h
	$(CC) $(CFLAGS) -c snake.c

main.o: main.c jogo.h snake.h
	$(CC) $(CFLAGS) -c main.c

graphic.o: graphic.c graphic.h
	$(CC) $(CFLAGS) -c graphic.c

coord.o: coord.c coord.h
	$(CC) $(CFLAGS) -c coord.c

food.o: food.c food.h
	$(CC) $(CFLAGS) -c food.c

teste:
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all teste clean
