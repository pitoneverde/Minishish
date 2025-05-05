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

NAME 				:= minishell

# Paths
LIB_DIR				:= libs
LIBFT_DIR			:= $(LIB_DIR)/libft
SRC_DIR				:= src
OBJ_DIR				:= obj
HEADERS_DIR 		:= include
LIBFT_HEADERS_DIR 	:= $(LIBFT_DIR)/include

# Compiler
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -g -I$(HEADERS_DIR) -I$(SRC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_HEADERS_DIR)

# Linker/Loader ld
LDFLAGS := -L$(LIBFT_DIR)

# Sources
SRCS 	:= $(SRC_DIR)/main.c \

LIBFT 	:= $(LIBFT_DIR)/libft_bonus.a

OBJS 	:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_CLEAN_ENABLED ?= 1

all: $(NAME)
	@echo "$(GREEN)---- Building of $(NAME) ----$(RESET)";

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(CYAN)---- Linking target $@ ---- $(RESET)using $^"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(LIBFT):
	@echo "$(YELLOW)---- Compiling $< $(RESET) ----> $@"
	$(MAKE) bonus -C $(LIBFT_DIR) --quiet

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)---- Compiling $< $(RESET) ----> $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	mkdir -p $(OBJ_DIR)

# Remove only temporary files
clean:
	@echo "$(RED)---- Removing .o files in $(NAME)----$(RESET)"
	@rm -rf $(OBJ_DIR)
ifeq ($(LIBFT_CLEAN_ENABLED),1)
	@echo "$(RED)---- Running clean libft ----$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
endif

# Remove temporary files and executables
fclean: clean 
	@if [ -n "$(NAME)" ] && [ -e "$(NAME)" ]; then \
		echo "$(RED)---- Removing executable $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
	fi
	@echo "$(RED)---- Running fclean libft ----$(RESET)"
	@$(MAKE) --no-print-directory LIBFT_CLEAN_ENABLED=0 clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent

re: fclean all
 
.PHONY: all clean fclean re
