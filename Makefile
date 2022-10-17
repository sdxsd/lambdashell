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
				exec/path.c \
				exec/cmd.c \
				exec/exec.c \
				exec/exec_list.c \
				tokenizer/tokens.c \
				expander/line_expander.c \
				builtins/builtin_env.c \
				builtins/builtin_pwd.c \
				builtins/builtin_unset.c \
				builtins/builtin_echo.c \
				builtins/builtin_export.c \
				builtins/builtin_cd.c \
				dealloc/clean_env.c \
				dealloc/dealloc_exec_list.c \
				debug/debug_env.c \
				debug/debug_print.c \
				cosmetic/splash.c \
				error/error.c \
				cosmetic/colors.c \
				checks/check_fd.c \
				tokenizer/tokens_tools.c \
				parser/line_parser.c \
				parser/line_split_into_lines.c \
				parser/line_parser_checks.c \
				init/init_ms_struct.c \
				init/init_env_struct.c \
				env/env_delete_var.c \
				env/env_to_arrays.c \
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
	@make clean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running clean.$(NOCOLOR)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(DIR_LIB_FT)
	@echo "$(GREEN)[minishell] - Running fclean.$(NOCOLOR)"

re : fclean all

.PHONY: all clean fclean re leaks lib_ft make_obj_dirs
