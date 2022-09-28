/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:36:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/28 15:45:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countparts(const char *s, char c)
{
	size_t	i;
	int		nparts;

	i = 0;
	nparts = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			nparts++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] && s[i] == c)
			i++;
	}
	return (nparts);
}

static char	**dp_clean(char **dp, size_t dp_i)
{
	while (dp_i > 0)
	{
		dp_i--;
		free(dp[dp_i]);
	}
	free(dp);
	return (NULL);
}

static char	**ft_split_helper(char **dp, const char *s, char c)
{
	size_t	s_i;
	size_t	dp_i;
	size_t	wordstart;

	s_i = 0;
	dp_i = 0;
	while (s_i < ft_strlen(s))
	{
		if ((s[s_i] != c) && (s_i < ft_strlen(s)))
		{
			wordstart = s_i;
			while ((s[s_i] != c) && (s_i < ft_strlen(s)))
				s_i++;
			dp[dp_i] = ft_substr(s, wordstart, (s_i - wordstart));
			if (!dp[dp_i])
				return (dp_clean(dp, dp_i));
			dp_i++;
		}
		s_i++;
	}
	return (dp);
}

char	**ft_split(char const *s, char c)
{
	char	**dp;

	if (!(s))
		return (NULL);
	dp = ft_calloc((ft_countparts(s, c) + 1), sizeof(char *));
	if (!(dp))
		return (NULL);
	return (ft_split_helper(dp, s, c));
}
