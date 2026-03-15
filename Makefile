CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -g 
SRC_DIR = src
build_dir = build
test_dir = tests

$(build_dir)/interpreter: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $(wildcard $(SRC_DIR)/*.c) -o $@

$(build_dir)/$(test_dir)/test_symbol_table.o: 
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(SRC_DIR)/symbol.c $(SRC_DIR)/util.c $(test_dir)/test_symbol_table.c -o $@

