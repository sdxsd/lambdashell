
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
NAME = minishell
CFILES = \
	src/main.c \
	src/builtins/cd.c \
	src/builtins/pwd.c \
	src/cosmetic/cosmetic.c \
	src/dealloc/dealloc_lambda.c \
	src/dealloc/dealloc_ptr_array.c \
	src/debug/debug_env.c \
	src/debug/debug_print.c \
	src/env/env_utils.c \
	src/env/env.c \
	src/env/expand_env_variables.c \
	src/error/error.c \
<<<<<<< HEAD
	src/exec/cmd.c \
	src/exec/exec.c \
	src/exec/exec_list.c \
=======
>>>>>>> origin/tokens
	src/exec/exec.c \
	src/exec/path.c \
	src/parse/is_ambiguous_redirect.c \
	src/parse/is_text_token.c \
	src/parse/parse.c \
	src/parse/skip_whitespace_tokens.c \
	src/tokenize/get_token.c \
	src/tokenize/subtokenizers.c \
	src/tokenize/tokenize.c

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
