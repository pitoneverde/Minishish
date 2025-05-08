# === Colors ===
RED     			:= \033[0;31m
GREEN   			:= \033[0;32m
YELLOW  			:= \033[0;33m
BLUE    			:= \033[0;34m
MAGENTA 			:= \033[0;35m
CYAN    			:= \033[0;36m
RESET   			:= \033[0m
BOLD				:= \033[1m
UNDERLINE 			:= \033[4;32m
GREEN_BG 			:= \033[42m

# === Name ===
NAME		 		:= minishell

# === Paths ===
LIB_DIR				:= libs
SRC_DIR				:= src
OBJ_DIR				:= obj
TEST_DIR     		:= tests
TEST_OBJ_DIR		:= obj_tests
HEADERS_DIR 		:= include

# === Libft Paths===
LIBFT_DIR			:= $(LIB_DIR)/libft
LIBFT_HEADERS_DIR 	:= $(LIBFT_DIR)/include
LIBFT 				:= $(LIBFT_DIR)/libft_bonus.a

# === Unity ===
UNITY_DIR   		:= unity/src
UNITY_SRC   		:= $(UNITY_DIR)/unity.c
UNITY_OBJ			:= $(TEST_OBJ_DIR)/unity.o

# === Compiler ===
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -g \
			-I$(HEADERS_DIR) -I$(SRC_DIR) \
			-I$(LIBFT_DIR) -I$(LIBFT_HEADERS_DIR) \
			-I$(UNITY_DIR)

LDFLAGS := -L$(LIBFT_DIR) -lft_bonus -lreadline

# === Sources ===
SRCS_MAIN 	:= $(SRC_DIR)/main.c

SRCS 		:= \
	$(SRC_DIR)/parser/tokenize.c \
	$(SRC_DIR)/feature1/sum.c \
	$(SRC_DIR)/utils/utils.c
	
TEST_SRCS	:= \
	$(TEST_DIR)/test0.c

# Compile objects
MAIN_OBJ 		:= $(SRCS_MAIN:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
NO_MAIN_OBJS	:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS 			:= $(MAIN_OBJ) $(NO_MAIN_OBJS)

# Compile test objects
TEST_OBJS	:= $(TEST_SRCS:$(TEST_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)

LIBFT_CLEAN_ENABLED ?= 1

# Main target
all: $(NAME)
	@echo "$(GREEN)---- ✅ Building of $(NAME) ----$(RESET)";

# Link objects + library
$(NAME): $(OBJS) $(LIBFT)
	@echo "$(CYAN)---- Linking target $@ ---- $(RESET)using $^"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(LIBFT):
	@echo "$(YELLOW)---- Compiling $< $(RESET) ----> $@"
	@$(MAKE) bonus -C $(LIBFT_DIR) --quiet

# Compile src files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)---- Compiling $< $(RESET) ----> $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# === Compile Unity object ===
$(UNITY_OBJ): $(UNITY_SRC)
	@echo "$(YELLOW)Compiling Unity $<$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile test files
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(TEST_OBJ_DIR)
	@echo "$(YELLOW)Compiling test $<$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	@mkdir -p $(OBJ_DIR)

# Create test object directory
$(TEST_OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	@mkdir -p $(TEST_OBJ_DIR)

test: $(TEST_OBJS) $(NO_MAIN_OBJS) $(UNITY_OBJ)
	@echo "$(GREEN_BG)---- Compiling & running tests ---- $(RESET)"
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(NO_MAIN_OBJS) $(UNITY_OBJ) -o run_tests
	@./run_tests

# Remove only temporary files
clean:
	@echo "$(RED)---- Removing .o files in $(NAME)----$(RESET)"
	@rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR)
ifeq ($(LIBFT_CLEAN_ENABLED),1)
	@echo "$(RED)---- Running clean libft ----$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
endif

# Clean test
tclean:
	@echo "$(RED)---- Clean tests ----$(RESET)"
	@rm -f ./run_tests
	@rm -rf $(TEST_OBJ_DIR)

# Remove temporary files and executables
fclean: clean tclean
	@if [ -n "$(NAME)" ] && [ -e "$(NAME)" ]; then \
		echo "$(RED)---- Removing executable $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
	fi
	@echo "$(RED)---- Running fclean libft ----$(RESET)"
	@$(MAKE) --no-print-directory LIBFT_CLEAN_ENABLED=0 clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent

re: fclean all
 
.PHONY: all test clean fclean tclean re
