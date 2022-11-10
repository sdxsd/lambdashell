
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
NAME = minishell
CFILES =		src/main.c \
				src/exec/path.c \
				src/exec/cmd.c \
				src/exec/exec.c \
				src/exec/exec_list.c \
				src/builtins/pwd.c \
				src/builtins/cd.c \
				src/builtins/builtins.c \
				src/tokenizer/tokens.c \
				src/dealloc/dealloc_exec_list.c \
				src/debug/debug_print.c \
				src/debug/debug_env.c \
				src/env/env.c \
				src/env/env_utils.c \
				src/parser/line_parser.c \
				src/error/error.c \
				src/cosmetic/colours.c \
				src/cosmetic/cosmetic.c
OFILES = $(CFILES:.c=.o)
LIB = libft/libft.a

all: $(NAME)

# TODO: These are needed in order to use rl_replace_line(), rl_clear_history() or rl_redisplay()
# INCLUDES := -I $(shell brew --prefix readline)/include
# LIBS := -L $(shell brew --prefix readline)/lib -lreadline

$(NAME): $(OFILES) $(LIB)
	$(CC) $(CFLAGS) -lreadline $(OFILES) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	$(MAKE) -C libft/

re: fclean all

fclean: clean
# TODO: Discuss whether fcleaning libft as well is desired
	$(MAKE) -C libft/ fclean
	@rm -f $(NAME)
	@echo "DEEP CLEANING"

# TODO: Discuss whether cleaning libft as well is desired
# $(MAKE) -C libft/ clean
clean:
	@rm -f $(OFILES)
	@echo "CLEANED UP"

.PHONY: all re fclean clean
