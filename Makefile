# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/11 21:25:39 by mikuiper      #+#    #+#                  #
#    Updated: 2022/09/21 12:43:11 by mikuiper      ########   odam.nl          #
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
DIR_INC =			includes
DIR_OBJ =			obj
DIR_LIB_FT =		libft

# SOURCE NAMES
NAMES_SRCS =	main.c \
				commands.c \
				path.c \
				pipe_block.c \
				exec.c \
				expander/line_expander.c \
				builtins/builtin_env.c \
				builtins/builtin_pwd.c \
				builtins/builtin_unset.c \
				misc/cleanup/clean_env.c \
				misc/cleanup/clean_tokenlist.c \
				misc/debug/debug_env.c \
				misc/debug/debug_tokenlist.c \
				misc/splash.c \
				misc/error.c \
				misc/colors.c \
				misc/check_fd.c \
				tokenizer/tokens_tools.c \
				tokenizer/tokens.c \
				parser/line_parser.c \
				parser/line_split_into_lines.c \
				parser/line_parser_checks.c \
				init/init_ms_struct.c \
				init/init_env_struct.c \
				env/env_delete_var.c \
				env/env_add_var.c \
				env/env_clone_env.c \
				env/env_tools.c

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
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(DIR_OBJ)/builtins
	@mkdir -p $(DIR_OBJ)/env
	@mkdir -p $(DIR_OBJ)/expander
	@mkdir -p $(DIR_OBJ)/tokenizer
	@mkdir -p $(DIR_OBJ)/executor
	@mkdir -p $(DIR_OBJ)/parser
	@mkdir -p $(DIR_OBJ)/error
	@mkdir -p $(DIR_OBJ)/init
	@mkdir -p $(DIR_OBJ)/misc
	@mkdir -p $(DIR_OBJ)/misc/cleanup
	@mkdir -p $(DIR_OBJ)/misc/debug

clean:
	#@rm -rf $(DIR_OBJ)
	@make clean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running clean.$(NOCOLOR)"

fclean: clean
	@rm -rf $(NAME)
	#@make fclean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running fclean.$(NOCOLOR)"

re : fclean all

.PHONY: all clean fclean re leaks lib_ft make_obj_dirs
