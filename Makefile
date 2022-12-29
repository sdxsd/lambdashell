
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
CFILES = \
	src/main.c \
	src/alloc/alloc.c \
	src/builtins/cd.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/pwd.c \
	src/builtins/unset.c \
	src/builtins/echo.c \
	src/cosmetic/cosmetic.c \
	src/dealloc/dealloc_lst.c \
	src/dealloc/dealloc.c \
	src/debug/debug_print.c \
	src/env/env_utils.c \
	src/env/env.c \
	src/env/expand_variables.c \
	src/env/mark_ambiguous_redirects.c \
	src/error/error.c \
	src/exec/exec.c \
	src/exec/path.c \
	src/heredoc/heredoc.c \
	src/parse/is_text_token.c \
	src/parse/parse.c \
	src/parse/skip_whitespace_tokens.c \
	src/stop/stop.c \
	src/tokenize/get_token.c \
	src/tokenize/check_token_syntax_errors.c \
	src/tokenize/whitespace_split_env_tokens.c \
	src/tokenize/subtokenizers.c \
	src/tokenize/tokenize.c \
	src/signals/signals.c \
	src/update_cwd/update_cwd.c

HEADERS = \
	include/minishell.h \
	include/prototypes.h \
	include/splash.h \
	include/structs.h

OFILES = $(CFILES:.c=.o)

LIBFT_PATH = libft/libft.a

LIB = -L libft -l ft
ifeq ($(shell uname), Linux)
LIB += -l readline
else
LIB += -L $(shell brew --prefix readline)/lib -lreadline
INCLUDES += -I $(shell brew --prefix readline)/include
endif

all: $(NAME)

$(NAME): $(OFILES) $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OFILES) $(LIB) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_PATH):
	$(MAKE) -C libft/

re: fclean all

fclean: clean
	@rm -f $(NAME)
	@echo "DEEP CLEANING"

clean:
	$(MAKE) -C libft/ fclean
	@rm -f $(OFILES)
	@echo "CLEANED UP"

.PHONY: all re fclean clean
