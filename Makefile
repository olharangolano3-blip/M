
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -Isrc/libft

LIBFT_DIR   = src/libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRC     =   minishell.c \
            src/parser/tokenize.c \
            src/parser/tokenize_utils.c \
            src/parser/parser.c \
            src/parser/parser_utils.c \
            src/parser/parser_argv.c \
            src/parser/parser_free.c \
            src/parser/parser_debug.c \
            src/parser/heredoc.c \
            src/parser/expander.c \
            src/parser/expander_quotes.c \
            src/parser/expander_var.c \
            src/parser/env.c \
            src/parser/parser_validate.c \
            src/builtins/echo.c \
            src/builtins/cd.c \
            src/builtins/pwd.c \
            src/builtins/export.c \
            src/builtins/unset.c \
            src/builtins/env.c \
            src/builtins/exit.c \
            src/executor/executor.c \
	    src/executor/executor_utils.c \
            src/executor/pipes.c \
            src/executor/redirections.c \
            src/utils/env_utils.c \
            src/utils/error_handling.c \
            src/utils/string_utils.c

OBJ     = $(SRC:.c=.o)
NAME    = minishell

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
