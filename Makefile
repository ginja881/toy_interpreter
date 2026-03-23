CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -g 
SRC_DIR = src
build_dir = build
test_dir = tests

$(build_dir)/interpreter: $(SRC_DIR)/main.c
	if [!(-d "./build")]; then mkdir build; fi
	$(CC) $(CFLAGS) $(wildcard $(SRC_DIR)/*.c) -o $@

$(build_dir)/$(test_dir)/%.o: $(test_dir)/%.c 
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c)) $< -o $@


