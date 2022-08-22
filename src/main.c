/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 10:23:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
sudo apt-get install libreadline-dev
*/

/*
env = ft_calloc(1, sizeof(t_env));
if (!env)
	exit(1);
*/

int	init(char **envp)
{
	if (init_global(envp))
		return (1);
}

int     init_global(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	global_env = ft_calloc((i + 1), (sizeof(char *)));
	if (!global_env)
	{
		printf("Error: Mem allocation for global env. failed.\n");
		return (1);
	}
	return (0);
}

int     main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//(void)envp;
	if (init(envp))
		return (1);
	return 0;
}
