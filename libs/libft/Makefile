# === Colors ===
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m
BOLD		= \033[1m
UNDERLINE = \033[4;32m
GREEN_BG = \033[42m

NAME = libft.a
BONUS_NAME = libft_bonus.a

HEADERS_DIR		= include
SRC_DIR			= src
OBJ_DIR			= obj

SRCS = 	$(SRC_DIR)/ft_isalpha.c \
		$(SRC_DIR)/ft_isdigit.c \
		$(SRC_DIR)/ft_isalnum.c \
		$(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isprint.c \
		$(SRC_DIR)/ft_strlen.c \
		$(SRC_DIR)/ft_memset.c \
		$(SRC_DIR)/ft_bzero.c \
		$(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c \
		$(SRC_DIR)/ft_strlcpy.c \
		$(SRC_DIR)/ft_strlcat.c \
		$(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_toupper.c \
		$(SRC_DIR)/ft_strchr.c \
		$(SRC_DIR)/ft_strrchr.c \
		$(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_memchr.c \
		$(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_strnstr.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_strdup.c \
		$(SRC_DIR)/ft_substr.c \
		$(SRC_DIR)/ft_strjoin.c \
		$(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_striteri.c \
		$(SRC_DIR)/ft_putchar_fd.c \
		$(SRC_DIR)/ft_putstr_fd.c \
		$(SRC_DIR)/ft_putendl_fd.c \
		$(SRC_DIR)/ft_putnbr_fd.c \
		$(SRC_DIR)/ft_printf.c \
		$(SRC_DIR)/ft_putptr_fd.c \
		$(SRC_DIR)/ft_putunbr_fd.c \
		$(SRC_DIR)/ft_puthex_fd.c \
		$(SRC_DIR)/get_next_line.c \
			
SRCS_BONUS = 	$(SRC_DIR)/ft_lstnew.c \
				$(SRC_DIR)/ft_lstadd_front.c \
				$(SRC_DIR)/ft_lstsize.c \
				$(SRC_DIR)/ft_lstlast.c \
				$(SRC_DIR)/ft_lstadd_back.c \
				$(SRC_DIR)/ft_lstdelone.c \
				$(SRC_DIR)/ft_lstclear.c \
				$(SRC_DIR)/ft_lstiter.c \
				$(SRC_DIR)/ft_lstmap.c

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