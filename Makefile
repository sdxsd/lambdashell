
CC = clang
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
				src/dealloc/dealloc_ptr_array.c \
				src/debug/debug_print.c \
				src/debug/debug_env.c \
				src/env/env.c \
				src/env/env_utils.c \
				src/parser/line_parser.c \
				src/error/error.c \
				src/cosmetic/colours.c \
				src/cosmetic/cosmetic.c
OFILES = $(CFILES:.c=.o)

LIB = -L libft -l ft
ifeq ($(shell uname), Linux)
LIB += -l readline
else
LIB += -L $(shell brew --prefix readline)/lib -lreadline
INCLUDES += -I $(shell brew --prefix readline)/include
endif

all: $(NAME)

$(NAME): $(OFILES) $(LIB)
	$(CC) $(CFLAGS) $(OFILES) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
