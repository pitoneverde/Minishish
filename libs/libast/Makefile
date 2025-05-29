# === Colors ===
RED     	= \033[0;31m
GREEN   	= \033[0;32m
YELLOW  	= \033[0;33m
BLUE    	= \033[0;34m
MAGENTA 	= \033[0;35m
CYAN    	= \033[0;36m
RESET   	= \033[0m
BOLD		= \033[1m
UNDERLINE 	= \033[4;32m
GREEN_BG 	= \033[42m

NAME = libast.a

HEADERS_DIR		:= include
SRC_DIR			:= src
OBJ_DIR			:= obj

# === Libft Paths===
LIB_DIR				:= ../../libs
LIBFT_DIR			:= $(LIB_DIR)/libft
LIBFT_HEADERS_DIR 	:= $(LIBFT_DIR)/include
LIBFT 				:= $(LIBFT_DIR)/libft_bonus.a

SRCS = 	\
	$(SRC_DIR)/ast_core/ast_attach_left.c \
	$(SRC_DIR)/ast_core/ast_attach_right.c \
	$(SRC_DIR)/ast_core/ast_free.c \
	$(SRC_DIR)/ast_core/ast_free_void.c \
	$(SRC_DIR)/ast_core/astdup.c \
	$(SRC_DIR)/ast_create/ast_binary_op.c \
	$(SRC_DIR)/ast_create/ast_cmd.c \
	$(SRC_DIR)/ast_create/ast_error.c \
	$(SRC_DIR)/ast_create/ast_new.c \
	$(SRC_DIR)/ast_filter/ast_filter.c \
	$(SRC_DIR)/ast_filter/ast_filter_n.c \
	$(SRC_DIR)/ast_filter/ast_filter_visit.c \
	$(SRC_DIR)/ast_filter/ast_leaf_nodes.c \
	$(SRC_DIR)/ast_filter/ast_leaf_nodes_n.c \
	$(SRC_DIR)/ast_flatten/ast_flatten_post.c \
	$(SRC_DIR)/ast_flatten/ast_flatten_pre.c \
	$(SRC_DIR)/ast_flatten/ast_flatten_visit.c \
	$(SRC_DIR)/ast_lst_to_array/ast_lst_to_array.c \
	$(SRC_DIR)/ast_lst_to_array/ast_lst_to_array_n.c \
	$(SRC_DIR)/ast_traverse/ast_traverse_post.c \
	$(SRC_DIR)/ast_traverse/ast_traverse_post_ctx.c \
	$(SRC_DIR)/ast_traverse/ast_traverse_pre.c \
	$(SRC_DIR)/ast_traverse/ast_traverse_pre_ctx.c \
	$(SRC_DIR)/ast_types/ast_is_command.c \
	$(SRC_DIR)/ast_types/ast_is_leaf.c \
	$(SRC_DIR)/ast_types/ast_is_operator.c \
	$(SRC_DIR)/ast_types/ast_is_redirection.c \
	$(SRC_DIR)/ast_types/ast_is_redirection_chain.c \
	$(SRC_DIR)/ast_types/ast_is_simple_pipeline.c \
	$(SRC_DIR)/ast_utils/ast_find.c \
	$(SRC_DIR)/ast_utils/ast_map.c \
	$(SRC_DIR)/ast_utils/ast_replace_subtree.c \
	$(SRC_DIR)/ast_utils/ast_stringify.c \
	$(SRC_DIR)/ast_utils/ast_to_string.c \
	$(SRC_DIR)/ast_validate/ast_has_error.c \
	$(SRC_DIR)/ast_validate/ast_is_valid.c

CC 		:= gcc
CFLAGS	:= -Wall -Wextra -Werror \
			-I$(HEADERS_DIR) -I$(SRC_DIR) \
			-I$(LIBFT_DIR) -I$(LIBFT_HEADERS_DIR)

LDFLAGS := -L$(LIBFT_DIR) -lft_bonus

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@echo "$(GREEN)---- Building of $(NAME) ----$(RESET)";

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)---- Building archive $(NAME) ----$(RESET)";
	@ar rcs $(NAME) $(OBJS)

$(LIBFT):
	@echo "$(YELLOW)---- Compiling $< $(RESET) ----> $@"
	@$(MAKE) bonus -C $(LIBFT_DIR) --quiet

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)---- Compiling $< $(RESET) into $@ ----"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)---- Removing .o files in $(NAME)----$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@if [ -n "$(NAME)" ] && [ -e "$(NAME)" ]; then \
		echo "$(RED)---- Removing executable $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
	fi

re: fclean $(NAME)

.PHONY:  all clean fclean re