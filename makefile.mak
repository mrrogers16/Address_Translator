CC = gcc
CFLAGS = -Wall

OUTPUT = step1
SOURCE = step1.c

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)