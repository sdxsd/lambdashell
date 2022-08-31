int	init_env(t_ms *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->env = ft_calloc((i + 1), (sizeof(char *)));
	if (!ms->env)
		return (msg_err("Mem allocation for environment failed.", 1));
	i = 0;
	while (envp[i])
	{
		ms->env[i] = ft_strdup(envp[i]);
		if (!ms->env[i])
			return (1);
		i++;
	}
	return (0); 
}