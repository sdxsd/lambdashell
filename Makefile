# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/11 21:25:39 by mikuiper      #+#    #+#                  #
#    Updated: 2022/09/17 23:05:13 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell
COMP =			gcc
FLAGS_COMP =	-Wall -Wextra -Werror
FLAGS_LEAKS =	-g3 -fsanitize=address

# COLOR CONFIG
GREEN =			\033[92m
NOCOLOR =		\033[m

# DIRECTORY NAMES
DIR_SRC =			src
DIR_SRC_BUILTINS =	builtins
DIR_SRC_ENV =		env
DIR_INC =			includes
DIR_OBJ =			obj
DIR_LIB_FT =		libft

# SOURCE NAMES
NAMES_SRCS =	main.c \
				init.c \
				error.c \
				input.c \
				prompt.c \
				debug.c \
				clean.c \
				commands.c \
				expander.c \
				path.c \
				pipe_block.c \
				exec.c \
				tokenizer.c \
				splash.c \
				colors.c \
				$(DIR_SRC_BUILTINS)/builtin_env.c \
				$(DIR_SRC_BUILTINS)/builtin_pwd.c \
				$(DIR_SRC_BUILTINS)/builtin_unset.c \
				$(DIR_SRC_ENV)/env.c

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

NAME_LIB_FT =	libft.a
INC_LIB_FT =	$(DIR_LIB_FT) $(DIR_LIB_FT)/$(NAME_LIB_FT)
INC_HDRS =		-I $(DIR_INC)
INC_LIBS =		-L $(INC_LIB_FT) $(LIB_INC_RDLINE)

all: lib_ft $(NAME) 

$(NAME): lib_ft make_obj_dirs $(FULL_OBJS)
	@$(COMP) -g $(INC_HDRS) $(FULL_OBJS) $(INC_LIBS) -o $(NAME)
	@echo "$(GREEN)[minishell] - Compiled minishell!$(NOCOLOR)"

lib_ft:
	@make -sC $(DIR_LIB_FT)

leaks: lib_ft make_obj_dirs $(FULL_OBJS)
	@echo "$(GREEN)[minishell] - Compiled with $(FLAGS_LEAKS).$(NOCOLOR)"
	@$(COMP) $(FLAGS_LEAKS) $(INC_HDRS) $(FULL_OBJS) $(INC_LIBS) -o $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(FULL_HDRS)
	@mkdir -p $(DIR_OBJ) 
	@$(COMP) -g $(FLAGS_COMP) $(INC_HDRS) -o $@ -c $<

make_obj_dirs:
	@mkdir -p obj
	@mkdir -p obj/builtins obj/env

clean:
	@rm -rf $(DIR_OBJ)
	@make clean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running clean.$(NOCOLOR)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running fclean.$(NOCOLOR)"

re : fclean all

.PHONY: all clean fclean re leaks lib_ft make_obj_dirs
