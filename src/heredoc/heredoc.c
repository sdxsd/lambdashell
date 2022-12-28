#include "../../include/minishell.h"
#include <fcntl.h>

static int	create_heredoc_file(void)
{
	int		fd;
	int		iter;
	char	*file;
	char	*full_path;
	char	*num;

	iter = 1;
	num = ft_itoa(iter);
	file = ft_strjoin("heredoc_", num);
	full_path = ft_strjoin("/tmp/", file);
	while (!access(full_path, F_OK))
	{
		ft_free(&full_path);
		num = ft_itoa(iter);
		file = ft_strjoin("heredoc_", num);
		full_path = ft_strjoin("/tmp/", file);
		ft_free(&num);
		ft_free(&file);
		iter++;
	}
	printf("%s\n", full_path);
	fd = open(full_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	return (fd);
}

t_status	heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = create_heredoc_file();
	if (fd == -1)
		return (ERROR);
	while (TRUE)
	{
		line = readline("> ");
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		if (ft_streq(line, delimiter))
			break ;
	}
	return (OK);
}
