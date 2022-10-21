# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/11 21:25:39 by mikuiper      #+#    #+#                  #
#    Updated: 2022/10/08 12:10:06 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell
CC =			gcc
FLAGS_COMP =	-Wall -Wextra -Werror
DIR_SRC =			src
DIR_INC =			include
DIR_OBJ =			obj
LIBFT =		libft

NAMES_SRC =	main.c \
				exec/path.c \
				exec/cmd.c \
				exec/exec.c \
				exec/exec_list.c \
				tokenizer/tokens.c \
				dealloc/dealloc_exec_list.c \
				debug/debug_print.c \
				error/error.c

# HEADER NAMES
NAMES_HDRS =	minishell.h

# OBJECT NAMES
NAMES_OBJS =	$(NAMES_SRCS:.c=.o)
FULL_OBJS =		$(addprefix $(DIR_OBJ)/,$(NAMES_OBJS))
FULL_HDRS =		$(addprefix $(DIR_INC)/,$(NAMES_HDRS))


# OS-based readline library configuration
SYS := $(shell gcc -dumpmachine)
ifneq (, $(findstring linux, $(SYS)))
	LIB_INC_RDLINE = -lreadline -lncurses
else
	LIB_INC_RDLINE = ~/.brew/opt/readline/lib -l readline -I \
	~/.brew/opt/readline/include
endif

LIBFT_NAME =	libft.a
INC_LIBFT =	$(LIBFT) $(LIBFT)/$(LIBFT_NAME)
INC_HDRS =		-I $(DIR_INC)
INC_LIBS =		-L $(INC_LIBFT) $(LIB_INC_RDLINE)

all: libft $(NAME)

$(NAME): libft make_obj_dirs $(FULL_OBJS)
	$(CC) -g $(INC_HDRS) $(FULL_OBJS) $(INC_LIBS) -o $(NAME)

libft:
	@make -sC $(LIBFT)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(FULL_HDRS)
	@mkdir -p $(DIR_OBJ) 
	@$(COMP) -g $(FLAGS_COMP) $(INC_HDRS) -o $@ -c $<

make_obj_dirs:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(DIR_OBJ)/builtins
	@mkdir -p $(DIR_OBJ)/env
	@mkdir -p $(DIR_OBJ)/expander
	@mkdir -p $(DIR_OBJ)/tokenizer
	@mkdir -p $(DIR_OBJ)/exec
	@mkdir -p $(DIR_OBJ)/parser
	@mkdir -p $(DIR_OBJ)/error
	@mkdir -p $(DIR_OBJ)/init
	@mkdir -p $(DIR_OBJ)/dealloc
	@mkdir -p $(DIR_OBJ)/debug
	@mkdir -p $(DIR_OBJ)/cosmetic
	@mkdir -p $(DIR_OBJ)/checks

clean:
	@rm -rf $(DIR_OBJ)
	@make clean -C $(LIBFT)
	@echo "$(GREEN)[minishell] - Running clean.$(NOCOLOR)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)
	@echo "$(GREEN)[minishell] - Running fclean.$(NOCOLOR)"

re : fclean all

.PHONY: all clean fclean re leaks libft make_obj_dirs
