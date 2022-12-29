#include "../../include/minishell.h"
#include <fcntl.h>

static char	*create_heredoc_file(void)
{
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
	return (full_path);
}

char	*heredoc(char *delimiter)
{
	char	*line;
	char	*full_path;
	int		fd;

	line = NULL;
	full_path = create_heredoc_file();
	fd = open(full_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		return (NULL);
	while (TRUE)
	{
		line = readline("> ");
		if (ft_streq(line, delimiter))
			break ;
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	return (full_path);
}
