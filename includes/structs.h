/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/14 13:43:24 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	t_list	*tokens;
	t_env	**env;
}	t_ms;

typedef enum	e_token_type
{
	tkn_str,
	tkn_cmd,
	tkn_read,
	tkn_write,
	tkn_pipe,
	tkn_heredoc,
	tkn_append
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*val;
}	t_token;

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
	int		i_fd;
	int		o_fd;
	char	**args;
	char	**env;
	char	*path;
}	t_cmd;

/*
 * NOTE:
 *      PIPE BLOCK
 * +--------------------+
 * | cmd_one -> cmd_two | -> stdout
 * +--------------------+
 * +--------------------+    +------------------+
 * | cmd_one -> cmd_two | -> | OTHER PIPE BLOCK |
 * +--------------------+    +------------------+
 * +--------------------+
 * | cmd_one -> cmd_two | -> /something/example.file
 * +--------------------+
 * ALLOCATOR   : pipe_blk_alloc()
 * DEALLOCATOR : pipe_blk_dealloc()
 */

typedef struct	s_pipe_blk
{
	int		i_fd;
	int		o_fd;
	int		pipe[2];
	t_cmd	*cmd_one;
	t_cmd	*cmd_two;
}				t_pipe_blk;

/*
 * NOTE:
 *      TOKEN LIST
 * +------------------+
 * | element[command] |
 * +------------------+
 *   | void *next
 *   ---> +----------------------+
 *        | element[redirection] |
 *        +----------------------+
 *        | void *next
 *        --------> +---------------+
 *                  | element[file] |
 *                  +---------------+
 * (int type) -> specifies the type of the element
 *               i.e. command
 *                    pipe
 *                    builtin
 *                    file
 *                    redirection
 * (void *value) -> structure of the element
 *                  i.e. t_cmd
 *                       t_pipe_blk
 * (void *next)  -> next token element in the list.
 *
 * ALLOCATOR   : token_list_generator();
 * DEALLOCATOR : token_list_deallocator();
*/

typedef struct s_token_element
{
	int		type;
	void	*value;
	void	*next;
}	t_token_element;

#endif
