COMPILER = gcc
FLAGS = -Wall -lm -lncurses
SOURCE = main.c
TARGET = cr

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(COMPILER) $(SOURCE) $(FLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
