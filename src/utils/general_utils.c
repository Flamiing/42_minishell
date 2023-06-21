/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:24:36 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 18:05:57 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_strlen_x(char *str, char limit)
{
	size_t	size;

	if (!str)
		return (0);
	size = 0;
	while (str[size] && str[size] != limit)
		size++;
	return (size);
}

int	ft_is_lowercase(char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
	{
		if (str[count] >= 65 && str[count] <= 90)
			return (0);
		count++;
	}
	return (1);
}

int	ft_is_empty_with_quotes(char *arg)
{
	size_t	count;

	count = 0;
	while (arg[count])
	{
		if (arg[count] != '\0' && arg[count] != ' '
			&& (arg[count] <= 8 || arg[count] > 13)
			&& arg[count] != SINGLE_QUOTE && arg[count] != DOUBLE_QUOTE)
			return (0);
		count++;
	}
	return (1);
}

size_t	ft_atoul(const char *string)
{
	size_t	count;
	size_t	sign;
	size_t	number;

	count = 0;
	sign = 1;
	number = 0;
	while (string[count] == 32 || (string[count] > 8 && string[count] <= 13))
		count++;
	if (string[count] == 45 || string[count] == 43)
	{
		if (string[count] == 45)
			sign *= -1;
		count++;
	}
	while ((string[count] != '\0' && (string[count] >= 48
				&& string[count] <= 57)))
	{
		number += string[count] - 48;
		if (string[count + 1] >= 48 && string[count + 1] <= 57)
			number *= 10;
		count++;
	}
	return (number * sign);
}
