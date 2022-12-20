/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_safe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 12:41:20 by sbos          #+#    #+#                 */
/*   Updated: 2022/09/01 14:38:56 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <limits.h>

static int	ft_char_to_digit(const char chr)
{
	if ('0' <= chr && chr <= '9')
		return (chr - '0');
	return (-1);
}

/**
 * @brief Takes a @p str like "123" and returns -123. It returns a negative
 * number to circumvent overflow.
 *
 * @param str
 * @param out_of_range Set to true when multiplying by ten
 * or subtracting a digit results in underflow.
 * @return
 */
static int	get_negative_value(const char *str, bool *out_of_range)
{
	static const int	range_mult_ten = INT_MIN / 10;
	static const int	range_last_digit = -(INT_MIN % 10);
	int					value;
	size_t					i;
	int					digit;

	value = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		digit = ft_char_to_digit(str[i]);
		if (value < range_mult_ten)
			*out_of_range = true;
		else if (value == range_mult_ten && digit > range_last_digit)
			*out_of_range = true;
		value *= 10;
		value -= digit;
		i++;
	}
	return (value);
}

/**
 * @brief Converts @p str to a int. This function is only supposed to be
 * used by ft_atoi() and ft_atoi_safe().
 *
 * @param str May start with whitespace, and the first encountered number will
 * be converted to a int.
 * @param out_of_range
 * @return The converted value or 0 if no number was found in @p str.
 */
static int	ft_atoi_range(const char *str, bool *out_of_range)
{
	int		sign;
	int		value;
	bool	dummy_out_of_range;

	if (out_of_range == NULL)
		out_of_range = &dummy_out_of_range;
	*out_of_range = false;
	while (ft_isspace(str[0]))
		str++;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	else if (str[0] == '+')
		str++;
	value = get_negative_value(str, out_of_range);
	if (sign == 1 && value == INT_MIN)
		*out_of_range = true;
	return (-sign * value);
}

/**
 * @brief Converts @p str to an int and puts it in the pointer @p nbr.
 * This function is safer than ft_atoi() because it returns a boolean that
 * is false when no number was found in @p str.
 * With ft_atoi("0") and ft_atoi("a") you can't tell whether @p str
 * contains a number, because those calls both return 0.
 * If the return value is false, the value of @p nbr is undefined.
 *
 * @param str May start with whitespace, and the first encountered number will
 * be converted to an int.
 * @param nbr The int will be put in here.
 * The dereferenced value won't be touched if no number was found in the string.
 * @return true if a number was found in @p str, false otherwise.
 */
bool	ft_atoi_safe(const char *str, int *nbr)
{
	bool	out_of_range;
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		i++;
	else if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	*nbr = ft_atoi_range(str, &out_of_range);
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	return (str[i] == '\0');
}
