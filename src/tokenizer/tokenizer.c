static t_token_type	subtokenize(char **line)
{
	if (**line == '\'')
		return (subtokenize_single_quote(line));
	else if (**line == '"')
		return (subtokenize_double_quote(line));
	else if (**line == '<' || **line == '>')
		return (subtokenize_redirection(line));
	else if (ft_isspace(**line))
		return (subtokenize_whitespace(line));
	else
		return (subtokenize_word(line));
}

t_list	*tokenizer(char *line)
{
	t_list			*tokens;
	char			*old_line_pos;
	t_token_type	token_type;
	char			*content;
	t_token			*token;

	tokens = NULL;

	while (*line)
	{
		old_line_pos = line;

		token_type = subtokenize(&line);

		content = ft_substr(old_line_pos, 0, line - old_line_pos);
		if (!content)
			return (NULL); // TODO: Free?

		token = get_token(token_type, content);
		if (!token || !ft_lstnew_back(&tokens, token))
			return (NULL); // TODO: Free?
	}

	return (tokens);
}
