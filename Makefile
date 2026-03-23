CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -g 
SRC_DIR = src
build_dir = build
test_dir = tests

$(build_dir)/interpreter: $(SRC_DIR)/main.c
	@[ -d $(build_dir) ] || mkdir -p $(build_dir)

	@$(CC) $(CFLAGS) $(wildcard $(SRC_DIR)/*.c) -o $@

$(build_dir)/$(test_dir)/%.o: $(test_dir)/%.c
	@[ -d $(build_dir)/$(test_dir) ] || mkdir -p $(build_dir)/$(test_dir)
	@$(CC) $(CFLAGS) -I$(SRC_DIR) $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c)) $< -o $@


