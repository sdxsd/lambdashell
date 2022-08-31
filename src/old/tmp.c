
// // Note the -1 return value for errors
// // This function assumes you have added indices using add_env_idx()
// //add_env_idx(ms->env);
// // get index for chosen env key
// int	get_env_key_idx(t_env **env, char *key)
// {
// 	t_env	*head;

// 	head = *env;
// 	if (!head)
// 		return (-1);
// 	else
// 	{
// 		while (head->next)
// 		{
// 			if (!ft_strncmp(head->key, key, ft_strlen(key)))
// 				return (head->idx);
// 			head = head->next;
// 		}
// 	}
// 	return (0);
// }


