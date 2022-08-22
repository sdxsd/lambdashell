/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 22:14:47 by mikuiper      ########   odam.nl         */
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

#include "minishell.h"


int     main(int argc, char **argv, char **envp)
{
	printf("\nSTART OF MINISHELL\n");	
	(void)argc;
	(void)argv;
	//(void)envp;
	if (init(envp))
		return (1);
	//env_add_entry("POKEMON", "Pikachu");
	env_add_entry("SHELL", "Mithras");
	int i = 0;
	while (env_global[i])
	{
		printf("%s\n", env_global[i]);
		i++;
	}
	printf("\nEND OF MINISHELL\n");	
	return 0;
}
