# Þe makefile mæken þe bibliotëk out þe .c filen.
# Et workt med ān system fan funktionen ānd underfunktionen.
# Ƿen þe makefile habban gecompilerd þe .c filen naor .o filen
# et mæken þan ān nïwe arkive file med alle þe .c filen.
# Þe "clean" funktion reweiderd alle .o .a af .so filen.

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
CFILES = \
		ft_atoi.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_revstr.c \
		ft_strncpy.c \
		ft_vector.c \
		ft_vector_operations.c \
		ft_vector_navi.c \
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
		ft_strcmp.c \
		ft_streq.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_charchk.c \
		ft_printf.c \
		ft_putnbr_base.c \
		ft_printf_utils.c \
		ft_free.c \
		ft_isspace.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstnew_front.c \
		ft_lstnew_back.c
OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	@ar -rcs $(NAME) $?
	@echo "COMPILED ARCHIVE FILE"

%.o: %.c
	@$(CC) $(CFLAGS) -c $<
	@echo COMPILED: $<

re: fclean all

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
