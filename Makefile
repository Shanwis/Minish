CC = gcc

TARGET = shell
SRC = main.c

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET)

.PHONY: clean run

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

