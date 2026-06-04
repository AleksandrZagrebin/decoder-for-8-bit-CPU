CC = gcc
CFLAGS = -Wall -Wextra
TARGET = decoder

PREF_SRC = src/
PREF_OBJ = obj/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))


$(TARGET): $(OBJ)
        $(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o: $(PREF_SRC)%.c
        mkdir -p $(PREF_OBJ)
        $(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
        @cd tests && for i in *.dat; do \
                echo -n "$$i: "; \
                ../$(TARGET) < "$$i" | diff -Bw - "$${i%.dat}.ans" && echo " OK" || echo " FAIL"; \
        done

run: $(TARGET)
        ./$(TARGET)

clean:
        rm -f $(TARGET)
        rm -rf $(PREF_OBJ)

.PHONY: all clean test run
