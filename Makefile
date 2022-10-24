
CC = clang
CFLAGS = -g -Wall -Wextra -Werror
NAME = minishell
CFILES =		src/main.c \
				src/exec/path.c \
				src/exec/cmd.c \
				src/exec/exec.c \
				src/exec/exec_list.c \
				src/tokenizer/tokens.c \
				src/dealloc/dealloc_exec_list.c \
				src/debug/debug_print.c \
				src/env/env.c \
				src/error/error.c
OFILES = $(CFILES:.c=.o)
B_OFILES = $(BONUS_FILES:.c=.o)
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OFILES) $(LIB)

%.o: %.c
	@$(CC) $(CFLAGS) -c $<
	@echo COMPILED: $<

$(LIB):
	make -C libft/

re: fclean all

fclean: clean
	@rm -f $(NAME)
	@echo "DEEP CLEANING"

clean:
	@rm -f $(OFILES)
	@rm -f $(B_OFILES)
	@rm -f a.out
	@echo "CLEANED UP"
