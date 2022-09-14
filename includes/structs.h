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
}				t_env;

typedef struct s_ms
{
	char	*line;
	t_list	*tokens;
	t_env	**env;
}			t_ms;

typedef enum	e_token_type
{
	tkn_str,
	tkn_read,
	tkn_write,
	tkn_pipe,
	tkn_heredoc,
	tkn_append
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*val;
}				t_token;

/*
 * NOTE:
 *                     +-----+
 *    /example/file -> | cmd | -> stdout | /other/file
 *                     +-----+
*/

typedef struct	s_cmd
{
	int		i_fd;
	int		o_fd;
	char	**args;
	char	**env;
	char	*path;
}				t_cmd;

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
 */

typedef struct	s_pipe_blk
{
	int		i_fd;
	int		o_fd;
	int		pipe[2];
	t_cmd	*cmd_one;
	t_cmd	*cmd_two;
}				t_pipe_blk;

#endif
