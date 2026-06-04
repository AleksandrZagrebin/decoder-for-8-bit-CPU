CC = gcc
CFLAGS = -Wall -Wextra
TARGET = decoder

PREF_SRC = src/
PREF_OBJ = obj/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
        $(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o: $(PREF_SRC)%.c
        mkdir -p $(PREF_OBJ)
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -f $(TARGET)
        rm -rf $(PREF_OBJ)

.PHONY: all clean
