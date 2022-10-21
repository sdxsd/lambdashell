#include "../libft/libft.h"

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_env
{
	char	*key;
	char	*val;
	int		idx;
	void	*next;
}	t_env;

typedef struct s_ms
{
	char	*line;
	t_env	**env;
	char	**lines;
}	t_ms;

typedef enum	e_token_type
{
	tkn_str,
	tkn_bltin,
	tkn_cmd,
	tkn_read,
	tkn_write,
	tkn_pipe,
	tkn_heredoc,
	tkn_append
}	t_token_type;

/*
 * NOTE:
 *                     +-----+
 *    /example/file -> | cmd | -> stdout | /other/file
 *                     +-----+
 * ALLOCATOR   : cmd_constructor()
 * DEALLOCATOR : cmd_deallocator()
*/

typedef struct	s_cmd
{
	int		ret;
	int		i_fd;
	int		o_fd;
	char	**args;
	char	**env;
	char	*path;
}	t_cmd;

// NOTE:
//    EXECUTION LIST
// +------------------+
// | element[command] |
// +------------------+
//   | void *next
//   ---> +----------------------+
//        | element[redirection] |
//        +----------------------+
//        | void *next
//        --------> +---------------+
//                  | element[file] |
//                  +---------------+

// (int type) -> specifies the type of the element
//               i.e. command
//                    pipe
//                    builtin
//                    file
//                    redirection
// (void *value) -> structure of the element
//                  i.e. t_cmd
// (void *next)  -> next token element in the list.

// ALLOCATOR   : execution_list_generator();
// DEALLOCATOR : execution_list_deallocator();

typedef struct s_exec_element
{
	int		type;
	char	*line;
	void	*value;
	void	*next;
}	t_exec_element;

#endif
