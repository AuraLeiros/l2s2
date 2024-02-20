CC = gcc
CFLAGS = -Wall -g
LIBS = -lm
SRCS = main.c main_aux.c entreeSortieLC.c entreeSortieH.c biblioLC.c biblioH.c test.c
TARGET = biblog

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
