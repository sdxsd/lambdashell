#ifndef MINISHELL_H
# define MINISHELL_H

/* HEADERS */
# include "structs.h"
# include "prototypes.h"
# include "splash.h"

/* LIBRARIES */
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* DEFINES */
# define READ 0
# define WRITE 1
# define TRUE 1
# define FALSE 0
# define FAILURE 1
# define SUCCESS 0
# define FORK_FAILURE -1
# define FORK_CHILD 0
# define FORK_PARENT 1

/* GLOBAL VARIABLE */
/* int		global_sig; */

#endif
