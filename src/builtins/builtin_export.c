/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:47:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 18:39:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
int	print_env_sorted(t_ms *ms)
{
	
	//char	**ordered_env;
	//ordered_env = hashmap_to_env_with_quotes(g_minishell.env);
	//quick_sort_2d_array(ordered_env, 0, get_2d_array_len(ordered_env));
	//join_2d_array("declare -x ", ordered_env);
	//print_2d_array_fd(ordered_env, STDOUT_FILENO);
	//free_2d_array(ordered_env);
	//return (0);
	


	(void)env_arrays;
	int i = 0;
	while (env_arrays[i])
	{
		printf("%s\n", env_arrays[i]);
		i++;
	}
	return (0);
}
*/



int	builtin_export(t_ms *ms, t_cmd *cmd_object)
{
	/*
	if (cmd_object->args[1])
		return (export_variable(cmd_object, 1));
	else
		return (print_ordered_env());
	*/
	(void)cmd_object;
	(void)ms;
	char **env_arrays;
	env_arrays = env_entries_to_arrays(ms->env);
	(void)env_arrays;
	int i;
	ft_sort_array_strings(env_arrays);

	i = 0;
	while (env_arrays[i])
	{
		printf("%s\n", env_arrays[i]);
		i++;
	}

	return (0);
}
