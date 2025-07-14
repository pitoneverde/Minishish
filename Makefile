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
UNIT_TEST_DIR     	:= $(TEST_DIR)/unit
INT_TEST_DIR     	:= $(TEST_DIR)/integration
UNIT_TEST_OBJ_DIR	:= unit_obj_tests
INT_TEST_OBJ_DIR	:= int_obj_tests
HEADERS_DIR 		:= include
TEST_MAINS			:= $(TEST_DIR)/mains

# === Libft Paths ===
LIBFT_DIR			:= $(LIB_DIR)/libft
LIBFT_HEADERS_DIR 	:= $(LIBFT_DIR)/include
LIBFT 				:= $(LIBFT_DIR)/libft_bonus.a

# === Ast Paths ===
LIBAST_DIR			:= $(LIB_DIR)/libast
LIBAST_HEADERS_DIR 	:= $(LIBAST_DIR)/include
LIBAST 				:= $(LIBAST_DIR)/libast.a

# === Unity ===
UNITY_DIR   		:= unity/src
UNITY_SRC   		:= $(UNITY_DIR)/unity.c
UNITY_OBJ			:= $(UNIT_TEST_OBJ_DIR)/unity.o

# === Compiler ===
CC			:= cc
CFLAGS		:= \
	-Wall -Werror -Wextra -g \
	-I$(HEADERS_DIR) \
	-I$(LIBFT_HEADERS_DIR) \
	-I$(LIBAST_HEADERS_DIR) \
	-I$(UNITY_DIR)

LDFLAGS 	:= \
	-L$(LIBFT_DIR) -lft_bonus \
	-L$(LIBAST_DIR) -last \
	-lreadline

# === Sources ===
SRCS_MAIN 	:= $(SRC_DIR)/main.c

SRCS 		:= \
	$(SRC_DIR)/parser/tokenize.c \
	$(SRC_DIR)/parser/parse.c \
	$(SRC_DIR)/parser/lex.c \
	$(SRC_DIR)/parser/validate/validate_ast.c \
	$(SRC_DIR)/parser/validate/ast_has_error.c \
	$(SRC_DIR)/parser/validate/ast_is_valid.c \
	$(SRC_DIR)/env/env.c \
	$(SRC_DIR)/env/env_internal.c \
	$(SRC_DIR)/env/env_utils.c \
	$(SRC_DIR)/feature1/sum.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/tokenizer_utils.c \
	$(SRC_DIR)/utils/lexer_utils.c \
	$(SRC_DIR)/utils/lexer_helpers.c \
	$(SRC_DIR)/utils/parser_utils.c \
	$(SRC_DIR)/utils/parser_helpers.c \
	$(SRC_DIR)/utils/matrix_utils.c \
	$(SRC_DIR)/expander/expand.c \
	$(SRC_DIR)/expander/expand_token.c \
	$(SRC_DIR)/expander/expander_utils.c \
	$(SRC_DIR)/debug.c \
	$(SRC_DIR)/signals/signals.c \
	$(SRC_DIR)/executor/executor.c \
	$(SRC_DIR)/executor/exec_cmd.c \
	$(SRC_DIR)/executor/handle_redir.c \
	$(SRC_DIR)/executor/handle_heredoc.c \
	$(SRC_DIR)/executor/fd_utils.c \
	$(SRC_DIR)/executor/exec_pipe.c \
	$(SRC_DIR)/executor/exec_builtin.c \
	$(SRC_DIR)/builtin/echo.c \
	$(SRC_DIR)/builtin/pwd.c \
	$(SRC_DIR)/builtin/cd.c \
	$(SRC_DIR)/builtin/exit.c \
	$(SRC_DIR)/builtin/env.c \
	$(SRC_DIR)/builtin/export.c \
	$(SRC_DIR)/builtin/export2.c \
	$(SRC_DIR)/builtin/unset.c \
	$(SRC_DIR)/preprocessor/preprocess.c \
	# $(TEST_MAINS)/parser.c
	
UNIT_TEST_SRCS	:= \
	$(UNIT_TEST_DIR)/all_tests.c \
	$(UNIT_TEST_DIR)/test_ast.c \
	$(UNIT_TEST_DIR)/test_lexer.c \
	$(UNIT_TEST_DIR)/test_tokenizer.c
# 	$(UNIT_TEST_DIR)/test_matrix.c \
# 	$(UNIT_TEST_DIR)/test_parser.c \
# 	$(UNIT_TEST_DIR)/test_env.c \
	
INT_TEST_SRCS	:= \
	$(INT_TEST_DIR)/all_tests.c \
	$(INT_TEST_DIR)/helpers_setup.c \
	$(INT_TEST_DIR)/test_args.c \
	$(INT_TEST_DIR)/test_prompt.c

# Compile objects
MAIN_OBJ 		:= $(SRCS_MAIN:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
NO_MAIN_OBJS	:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS 			:= $(MAIN_OBJ) $(NO_MAIN_OBJS)

# Compile test objects
UNIT_TEST_OBJS	:= $(UNIT_TEST_SRCS:$(UNIT_TEST_DIR)/%.c=$(UNIT_TEST_OBJ_DIR)/%.o)
INT_TEST_OBJS	:= $(INT_TEST_SRCS:$(INT_TEST_DIR)/%.c=$(INT_TEST_OBJ_DIR)/%.o)

LIBFT_CLEAN_ENABLED ?= 1
LIBAST_CLEAN_ENABLED ?= 1

# Main target
all: $(NAME)
	@echo "$(GREEN)---- ✅ Building of $(NAME) ----$(RESET)";

# Link objects + library
$(NAME): $(OBJS) $(LIBFT) $(LIBAST)
	@echo "$(CYAN)---- Linking target $@ ---- $(RESET)using $^"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBAST) $(LDFLAGS) -o $@

$(LIBFT):
	@echo "$(YELLOW)---- Compiling $< $(RESET) ----> $@"
	@$(MAKE) bonus -C $(LIBFT_DIR) --quiet

$(LIBAST):
	@echo "$(YELLOW)---- Compiling $< $(RESET) ----> $@"
	@$(MAKE) -C $(LIBAST_DIR) --quiet

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
$(UNIT_TEST_OBJ_DIR)/%.o: $(UNIT_TEST_DIR)/%.c | $(UNIT_TEST_OBJ_DIR)
	@echo "$(YELLOW)Compiling test $<$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile test files
$(INT_TEST_OBJ_DIR)/%.o: $(INT_TEST_DIR)/%.c | $(INT_TEST_OBJ_DIR)
	@echo "$(YELLOW)Compiling test $<$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	@mkdir -p $(OBJ_DIR)

# Create test object directory
$(UNIT_TEST_OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	@mkdir -p $(UNIT_TEST_OBJ_DIR)

$(INT_TEST_OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	@mkdir -p $(INT_TEST_OBJ_DIR)

unit_test: $(UNIT_TEST_OBJS) $(NO_MAIN_OBJS) $(UNITY_OBJ) $(LIBFT) $(LIBAST)
	@echo "$(GREEN_BG)---- Compiling & running tests ---- $(RESET)"
	@$(CC) $(CFLAGS) $(UNIT_TEST_OBJS) $(NO_MAIN_OBJS) $(UNITY_OBJ) $(LIBFT) $(LIBAST) $(LDFLAGS) -o run_unit_tests
	@./run_unit_tests

int_test: $(INT_TEST_OBJS) $(NO_MAIN_OBJS) $(UNITY_OBJ) $(LIBFT)
	@echo "$(GREEN_BG)---- Compiling & running tests ---- $(RESET)"
	@$(CC) $(CFLAGS) $(INT_TEST_OBJS) $(NO_MAIN_OBJS) $(UNITY_OBJ) $(LIBFT) $(LIBAST) -L$(LIBFT_DIR) -lft_bonus $(LDFLAGS) -o run_integration_tests
	@./run_integration_tests

test: unit_test int_test

# Remove only temporary files
clean:
	@echo "$(RED)---- Removing .o files in $(NAME)----$(RESET)"
	@rm -rf $(OBJ_DIR) $(UNIT_TEST_OBJ_DIR)
ifeq ($(LIBFT_CLEAN_ENABLED),1)
	@echo "$(RED)---- Running clean libft ----$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
endif
ifeq ($(LIBAST_CLEAN_ENABLED),1)
	@echo "$(RED)---- Running clean libft ----$(RESET)"
	@$(MAKE) clean -C $(LIBAST_DIR) --silent
endif

# Clean test
tclean:
	@echo "$(RED)---- Clean tests ----$(RESET)"
	@rm -f ./run_tests
	@rm -rf $(UNIT_TEST_OBJ_DIR) $(INT_TEST_OBJ_DIR)

# Remove temporary files and executables
fclean: clean tclean
	@if [ -n "$(NAME)" ] && [ -e "$(NAME)" ]; then \
		echo "$(RED)---- Removing executable $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
	fi
	@echo "$(RED)---- Running fclean libft ----$(RESET)"
	@$(MAKE) --no-print-directory LIBFT_CLEAN_ENABLED=0 clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@echo "$(RED)---- Running fclean libast ----$(RESET)"
	@$(MAKE) --no-print-directory LIBAST_CLEAN_ENABLED=0 clean
	@$(MAKE) fclean -C $(LIBAST_DIR) --silent

re: fclean all

.PHONY: all test test2 clean fclean tclean re
