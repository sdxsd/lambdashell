/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 12:27:13 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/12/09 17:18:51 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
GET_NEXT_LINE (An implementation of get_next_line for a Codam project)
Copyright (C) 2021  Will Maguire

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>

The definition of Free Software is as follows:
	- The freedom to run the program, for any purpose.
	- The freedom to study how the program works, and adapt it to your needs.
	- The freedom to redistribute copies so you can help your neighbor.
	- The freedom to improve the program, and release
	  your improvements to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "libft.h"
#include <stdlib.h>

char	*gnl_strncpy(char *dest, const char *src, size_t n)
{
	size_t	iterator;

	iterator = 0;
	while (iterator < n && src[iterator] != '\0')
	{
		dest[iterator] = src[iterator];
		++iterator;
	}
	while (iterator < n)
	{
		dest[iterator] = '\0';
		iterator++;
	}
	return (dest);
}

char	*gnl_strndup(const char *s1, size_t len)
{
	char	*dupe_str;

	dupe_str = malloc((sizeof(char) * len) + 1);
	if (!dupe_str)
		return (NULL);
	gnl_strncpy(dupe_str, s1, len);
	dupe_str[len] = '\0';
	return (dupe_str);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*b_str;
	int		s1_l;
	int		s2_l;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	str = malloc((s1_l + s2_l) + 1);
	if (!str)
		return (NULL);
	b_str = str;
	gnl_strncpy(str, (char *)s1, s1_l);
	str += s1_l;
	gnl_strncpy(str, (char *)s2, s2_l);
	str += s2_l;
	*str = '\0';
	return (b_str);
}
