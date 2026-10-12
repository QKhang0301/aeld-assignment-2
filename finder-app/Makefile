CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -g

TARGET := writer
SRC := writer.c
OBJ := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean