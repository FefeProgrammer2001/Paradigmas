CC=clang
CFLAGS=-Wall -Werror -Wextra -std=c17 -O3 -g
BIN=main
SRC=vetor.c main.c

vetor: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clear:
	rm main

.PHONY: vetor clear