# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/11 21:25:39 by mikuiper      #+#    #+#                  #
#    Updated: 2022/09/13 20:24:58 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell
COMP =			gcc
FLAGS_COMP =	-Wall -Wextra -Werror
FLAGS_LEAKS =	-g3 -fsanitize=address

# MISC CONFIG
GREEN =			\033[92m
NOCOLOR =		\033[m

# DIRECTORY NAMES
DIR_SRC =		sources
DIR_INC =		includes
DIR_OBJ =		objects
DIR_LIB_FT =	libft

# SOURCE NAMES
NAMES_SRCS =	main.c \
				init.c \
				error.c \
				builtins.c \
				input.c \
				prompt.c \
				env.c \
				debug.c \
				clean.c \
				commands.c \
				expander.c \
				tokenizer.c

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

$(NAME): lib_ft $(FULL_OBJS)
	@$(COMP) -g $(INC_HDRS) $(FULL_OBJS) $(INC_LIBS) -o $(NAME)
	@echo "███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░"
	@echo "████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░"
	@echo "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░"
	@echo "██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░"
	@echo "██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗"
	@echo "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "$(GREEN)[minishell] - Compiled minishell!$(NOCOLOR)"

lib_ft:
	@make -sC $(DIR_LIB_FT)

leaks: $(FULL_OBJS) lib_ft
	@echo "$(GREEN)[minishell] - Compiled with $(FLAGS_LEAKS).$(NOCOLOR)"
	@$(COMP) $(FLAGS_LEAKS) $(INC_HDRS) $(FULL_OBJS) $(INC_LIBS) -o $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(FULL_HDRS)
	@mkdir -p $(DIR_OBJ) 
	@$(COMP) -g $(FLAGS_COMP) $(INC_HDRS) -o $@ -c $<

clean:
	@rm -rf $(DIR_OBJ)
	@make clean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running clean.$(NOCOLOR)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running fclean.$(NOCOLOR)"

re : fclean all

.PHONY: all clean fclean re leaks lib_ft
