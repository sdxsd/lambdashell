
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Wfatal-errors -fsanitize=address
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
	src/dealloc/dealloc.c \
	src/debug/debug_print.c \
	src/env/env_utils.c \
	src/env/env.c \
	src/env/expand_variables.c \
	src/env/is_valid_identifier.c \
	src/env/mark_ambiguous_redirects.c \
	src/error/error.c \
	src/exec/exec.c \
	src/exec/get_absolute_path_from_env.c \
	src/heredoc/expand_heredoc_tokens.c \
	src/heredoc/heredoc.c \
	src/heredoc/heredocs.c \
	src/misc/null.c \
	src/parse/is_text_token.c \
	src/parse/parse.c \
	src/parse/skip_whitespace_tokens.c \
	src/signals/signals.c \
	src/stop/stop.c \
	src/tokenize/check_token_syntax_errors.c \
	src/tokenize/split_and_add_spaced_tokens.c \
	src/tokenize/subtokenizers_misc.c \
	src/tokenize/subtokenizers_quotes.c \
	src/tokenize/subtokenizers_redirections.c \
	src/tokenize/tokenize.c \
	src/tokenize/whitespace_split_env_tokens.c \
	src/tokenize/is_whitespace.c \
	src/update_cwd/update_cwd.c

HEADERS = \
	include/enums.h \
	include/minishell.h \
	include/prototypes.h \
	include/splash.h \
	include/structs.h

OFILES = $(addprefix obj/,$(CFILES:.c=.o))

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

# Will attempt to create the object's parent directory
obj/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_PATH):
	$(MAKE) -C libft/

re: fclean all

fclean: clean
	@rm -f $(NAME)
	@echo "DEEP CLEANING"

clean:
	$(MAKE) -C libft/ fclean
	@rm -rf obj/
	@echo "CLEANED UP"

.PHONY: all re fclean clean
