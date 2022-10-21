# Þe makefile mæken þe bibliotëk out þe .c filen.
# Et workt med ān system fan funktionen ānd underfunktionen.
# Ƿen þe makefile habban gecompilerd þe .c filen naor .o filen
# et mæken þan ān nïwe arkive file med alle þe .c filen.
# Þe "clean" funktion reweiderd alle .o .a af .so filen.

CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
BONUS_FILES = \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c
CFILES = \
		ft_atoi.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_revstr.c \
		ft_strncpy.c \
		ft_bzero.c \
		ft_memcmp.c \
		ft_split.c \
		ft_strndup.c \
		ft_calloc.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_strnstr.c \
		ft_isalnum.c \
		ft_memmove.c \
		ft_strdup.c \
		ft_strrchr.c \
		ft_isalpha.c \
		ft_memset.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_isascii.c \
		ft_putchar_fd.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_isdigit.c \
		ft_putendl_fd.c \
		ft_strlcpy.c \
		ft_tolower.c \
		ft_islower.c \
		ft_putnbr_fd.c \
		ft_strlen.c \
		ft_toupper.c \
		ft_isprint.c \
		ft_strmapi.c \
		ft_isupper.c \
		ft_putstr_fd.c \
		ft_striteri.c \
		ft_putstr.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_revnum.c \
		ft_numlen_t.c \
		ft_strncmp.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_charchk.c \
		ft_printf.c \
		ft_putnbr_base.c \
		ft_printf_utils.c
OFILES = $(CFILES:.c=.o)
B_OFILES = $(BONUS_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	@ar -rcs $(NAME) $?
	@echo "COMPILED ARCHIVE FILE"

%.o: %.c
	@$(CC) $(CFLAGS) -c $<
	@echo COMPILED: $<

re: fclean all

bonus: $(NAME)
	@echo "COMPILING BONUS"
	@$(CC) $(CFLAGS) -c $(BONUS_FILES)
	@echo "COMPILED BONUS"
	@echo "ARCHIVING BONUS"
	@ar -rc libft.a $(B_OFILES)
	@echo "ARCHIVED BONUS"

fclean: clean
	@rm -f $(NAME)
	@echo "DEEP CLEANING"

clean:
	@rm -f $(OFILES)
	@rm -f $(B_OFILES)
	@rm -f a.out
	@echo "CLEANED UP"

so: $(NAME)
	$(CC) $(CFLAGS) $(OFILES) -o libft.so
