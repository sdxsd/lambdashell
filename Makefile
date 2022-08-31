# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/19 09:07:48 by mikuiper      #+#    #+#                  #
#    Updated: 2022/08/31 21:04:52 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# GENERAL CONFIG
NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LEAKS	= -g3 -fsanitize=address

# LIBRARIES
RD_LINE	= -lreadline -lncurses
LIBS	= -L $(FT_DIR) -lft $(RD_LINE)
FT = $(FT_DIR)/libft.a

# HEADERS
HEADERS	=	-I ./inc

# DIRECTORIES
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
FT_DIR		= ./libft

SRCS		= 	$(SRC_DIR)main.c \
				$(SRC_DIR)init.c \
				$(SRC_DIR)tools.c \
				$(SRC_DIR)builtins.c \
				$(SRC_DIR)input.c \
				$(SRC_DIR)prompt.c \
				$(SRC_DIR)env_tools.c \
				$(SRC_DIR)debug.c \
				$(SRC_DIR)clean.c
OBJS		= 	$(SRCS:.c=.o)

# COLORS
GREEN = \033[92m
NOCOLOR = \033[0;38m

# RULES
all: $(NAME)

$(NAME): $(OBJS) $(FT)
	@echo "$(GREEN)[minishell] - \t Compiled $(NAME).$(NOCOLOR)"
	@$(CC) $(CFLAGS) -L ~/.brew/opt/readline/lib -l readline -I ~/.brew/opt/readline/include $(HEADERS) -o $(NAME) $(OBJS) $(LIBS)

$(FT):
	@$(MAKE) -sC $(FT_DIR)

leaks: $(OBJS) $(FT)
	@echo "$(GREEN)[minishell] - \t Compiled with leak check.$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(LEAKS) $(HEADERS) -o $(NAME) $(OBJS) $(LIBS)
	
.c.o:
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

clean:
	#@$(MAKE) -sC $(FT_DIR) clean
	@echo "$(GREEN)[minishell] - \t Running clean.$(NOCOLOR)"
	@$(RM) $(OBJS)

fclean:
	#@$(MAKE) -sC $(FT_DIR) fclean
	@echo "$(GREEN)[minishell] - \t Running fclean.$(NOCOLOR)"
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

