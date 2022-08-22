# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/19 09:07:48 by mikuiper      #+#    #+#                  #
#    Updated: 2022/08/22 15:17:36 by mikuiper      ########   odam.nl          #
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
FT_DIR = ./libft

SRCS		= 	$(SRC_DIR)main.c \
				$(SRC_DIR)init.c \
				$(SRC_DIR)parse_cmd.c \
				$(SRC_DIR)tools.c
OBJS		= $(SRCS:.c=.o)

# COLORS
GREEN = \033[92m
NOCOLOR = \033[0;38m

# RULES
all: $(NAME)

$(NAME): $(OBJS) $(FT)
	@echo "$(GREEN)[minishell] - \t Compiled $(NAME).$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(HEADERS) -o $(NAME) $(OBJS) $(LIBS)

$(FT):
	@$(MAKE) -sC $(FT_DIR)

leaks: fclean $(OBJS) $(FT)
	@$(CC) $(CFLAGS) $(LEAKS) $(HEADERS) -o $(NAME) $(OBJS) $(LIBS)
	
.c.o:
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

clean:
	@$(MAKE) -sC $(FT_DIR) clean
	@echo "$(GREEN)[minishell] - \t Running clean.$(NOCOLOR)"
	@$(RM) $(OBJS)

fclean:
	@$(MAKE) -sC $(FT_DIR) fclean
	@echo "$(GREEN)[minishell] - \t Running fclean.$(NOCOLOR)"
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

