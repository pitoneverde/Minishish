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

NAME = libft.a
BONUS_NAME = libft_bonus.a

HEADERS_DIR		= include
SRC_DIR			= src
OBJ_DIR			= obj

SRCS = 	\
		$(SRC_DIR)/chars/ft_isalnum.c \
		$(SRC_DIR)/chars/ft_isalpha.c \
		$(SRC_DIR)/chars/ft_isascii.c \
		$(SRC_DIR)/chars/ft_isdigit.c \
		$(SRC_DIR)/chars/ft_islower.c \
		$(SRC_DIR)/chars/ft_isprint.c \
		$(SRC_DIR)/chars/ft_ispunct.c \
		$(SRC_DIR)/chars/ft_isupper.c \
		$(SRC_DIR)/chars/ft_tolower.c \
		$(SRC_DIR)/chars/ft_toupper.c \
		$(SRC_DIR)/memory/ft_bzero.c \
		$(SRC_DIR)/memory/ft_calloc.c \
		$(SRC_DIR)/memory/ft_memset.c \
		$(SRC_DIR)/memory/ft_memcpy.c \
		$(SRC_DIR)/memory/ft_memmove.c \
		$(SRC_DIR)/memory/ft_memcmp.c \
		$(SRC_DIR)/memory/ft_memchr.c \
		$(SRC_DIR)/memory/ft_realloc.c \
		$(SRC_DIR)/output/ft_putchar_fd.c \
		$(SRC_DIR)/output/ft_putstr_fd.c \
		$(SRC_DIR)/output/ft_putendl_fd.c \
		$(SRC_DIR)/output/ft_putnbr_fd.c \
		$(SRC_DIR)/strings/copy_string.c \
		$(SRC_DIR)/strings/ft_strlen.c \
		$(SRC_DIR)/strings/ft_strlcpy.c \
		$(SRC_DIR)/strings/ft_strlcat.c \
		$(SRC_DIR)/strings/ft_strchr.c \
		$(SRC_DIR)/strings/ft_strrchr.c \
		$(SRC_DIR)/strings/ft_strncmp.c \
		$(SRC_DIR)/strings/ft_strcmp.c \
		$(SRC_DIR)/strings/ft_strnstr.c \
		$(SRC_DIR)/strings/ft_strdup.c \
		$(SRC_DIR)/strings/ft_substr.c \
		$(SRC_DIR)/strings/ft_strjoin.c \
		$(SRC_DIR)/strings/ft_strtrim.c \
		$(SRC_DIR)/strings/ft_split.c \
		$(SRC_DIR)/strings/ft_strmapi.c \
		$(SRC_DIR)/strings/ft_striteri.c \
		$(SRC_DIR)/matrix/mtx_count.c \
		$(SRC_DIR)/matrix/mtxdup_n.c \
		$(SRC_DIR)/matrix/mtxdup_str.c \
		$(SRC_DIR)/matrix/mtxdup.c \
		$(SRC_DIR)/matrix/mtxfree_n.c \
		$(SRC_DIR)/matrix/mtxfree_str.c \
		$(SRC_DIR)/matrix/mtxfree.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/get_next_line.c

SRCS_BONUS = 	\
		$(SRC_DIR)/list/ft_lstnew.c \
		$(SRC_DIR)/list/ft_lstadd_front.c \
		$(SRC_DIR)/list/ft_lstsize.c \
		$(SRC_DIR)/list/ft_lstlast.c \
		$(SRC_DIR)/list/ft_lstadd_back.c \
		$(SRC_DIR)/list/ft_lstdelone.c \
		$(SRC_DIR)/list/ft_lstclear.c \
		$(SRC_DIR)/list/ft_lstiter.c \
		$(SRC_DIR)/list/ft_lstmap.c \
		$(SRC_DIR)/list/lst_to_array.c \
		$(SRC_DIR)/list/lst_to_array_n.c \
		$(SRC_DIR)/list/lst_to_array_ex.c \
		$(SRC_DIR)/strings/strbuilder/sb_append_char.c \
		$(SRC_DIR)/strings/strbuilder/sb_append_n.c \
		$(SRC_DIR)/strings/strbuilder/sb_append_str.c \
		$(SRC_DIR)/strings/strbuilder/sb_build.c \
		$(SRC_DIR)/strings/strbuilder/sb_capacity.c \
		$(SRC_DIR)/strings/strbuilder/sb_clear.c \
		$(SRC_DIR)/strings/strbuilder/sb_create.c \
		$(SRC_DIR)/strings/strbuilder/sb_ensure_capacity.c \
		$(SRC_DIR)/strings/strbuilder/sb_free.c \
		$(SRC_DIR)/strings/strbuilder/sb_length.c \
		$(SRC_DIR)/strings/strbuilder/sb_shrink_to_fit.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(HEADERS_DIR) -I$(SRC_DIR)

all: $(NAME)
	@echo "$(GREEN)---- Building of $(NAME) ----$(RESET)";

$(NAME): $(OBJS)
	@echo "$(GREEN)---- Building archive $(NAME) ----$(RESET)";
	@ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)---- Compiling $< $(RESET) into $@ ----"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo "$(MAGENTA)---- Create folder $@ $(RESET)"
	@mkdir -p $(OBJ_DIR)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS) $(OBJS_BONUS)
	@echo "$(GREEN)---- Building bonus of $(NAME) ----$(RESET)";
	@ar rcs $(BONUS_NAME) $(OBJS) $(OBJS_BONUS)

clean:
	@echo "$(RED)---- Removing .o files in $(NAME)----$(RESET)"
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@if [ -n "$(NAME)" ] && [ -e "$(NAME)" ]; then \
		echo "$(RED)---- Removing executable $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
	fi
	@if [ -n "$(BONUS_NAME)" ] && [ -e "$(BONUS_NAME)" ]; then \
		echo "$(RED)---- Removing executable $(BONUS_NAME)...$(RESET)"; \
		rm -f $(BONUS_NAME); \
	fi

re: fclean $(NAME)

.PHONY:  all clean fclean re bonus