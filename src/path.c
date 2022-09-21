#include "../includes/minishell.h"

/* Returns number of elements freed */
/* Assumes list ends with null ptr */
int	free_ptr_array(char *ptr[])
{
	int	iter;

	iter = 0;
	while (ptr[iter] != NULL)
	{
		free(ptr[iter]);
		iter++;
	}
	free(ptr);
	return (iter);
}

/* NOTE: exit calls are temporary until proper error handling is implemented. */
/* Utility function for combining program name and the paths.  */
static char	*combine_path(char *dir, char *prog_n)
{
	char	*abs_path;
	char	*dir_slash;

	dir_slash = ft_strjoin(dir, "/");
	if (!dir_slash)
		exit(1);
	abs_path = ft_strjoin(dir_slash, prog_n);
	if (!abs_path)
		exit(1);
	free(dir_slash);
	return (abs_path);
}

/* Takes program name (prog_n), and environment strings (env) and returns */
/* the absolute path to the program. */
char	*get_path(char *prog_n, t_env **env)
{
	static char	*path_env;
	char		*abs_path;
	char		**exec_direcs;
	int			iter;

	iter = 0;
	if (!path_env)
		path_env = env_get_val(env, "PATH");
	if (!path_env)
		return (NULL);
	exec_direcs = ft_split(path_env, ':');
	while (exec_direcs[iter] != NULL)
	{
		abs_path = combine_path(exec_direcs[iter], prog_n);
		if (!access(abs_path, F_OK))
		{
			free_ptr_array(exec_direcs);
			return (abs_path);
		}
		free(abs_path);
		iter++;
	}
	free_ptr_array(exec_direcs);
	return (NULL);
}
