#include "../../include/minishell.h"

static int	create_heredoc_file(void)
{
	int		iter;
	char	*file;
	char	*full_path;
	char	*num;

	iter = 1;
	num = ft_itoa(iter);
	file = ft_strjoin("heredoc_", num);
	full_path = ft_strjoin("/tmp/", file);
	if (access(full_path, F_OK))
	{

	}
}

t_status	heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = create_heredoc_file();
	if (!fd)
	while (!ft_streq(line, delimiter))
	{
		line = readline("> ");
		ft_putstr_fd(line);
		ft_free(&line);
	}
	return (OK);
}
