/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:21:38 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:18:47 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_compare_nbr(size_t nbr, size_t last_nbr, char sign)
{
	if (nbr >= 922337203685477580)
	{
		if (sign == '-' && nbr == 922337203685477580 && last_nbr > 8)
			return (1);
		else if (sign != '-' && nbr == 922337203685477580 && last_nbr > 7)
			return (1);
		else if (nbr > 922337203685477580)
			return (1);
	}
	return (0);
}

static size_t	ft_count_numbers(char *str)
{
	size_t	index;
	size_t	count;
	int		first_nbr_found;

	if (!str)
		return (0);
	index = 0;
	count = 0;
	first_nbr_found = 0;
	while (str[index])
	{
		if (first_nbr_found == 0 && ft_isdigit(str[index]) && str[index] != '0')
			first_nbr_found = 1;
		if (first_nbr_found == 1 && ft_isdigit(str[index]))
			count++;
		index++;
	}
	return (count);
}

static size_t	ft_digits_check(char *input, size_t last_nbr, char sign)
{
	size_t	index;
	size_t	len;
	char	*number;

	if (!input)
		return (0);
	index = 0;
	len = ft_strlen(input);
	number = (char *)ft_calloc(len + 1, sizeof(char));
	if (!number)
		return (0);
	while (index < len)
	{
		number[index] = input[index];
		index++;
	}
	number[index - 1] = '\0';
	if (ft_compare_nbr(ft_atoul(number), last_nbr, sign))
	{
		free(number);
		return (1);
	}
	free(number);
	return (0);
}

static size_t	ft_find_max_or_min_nbr(char *input)
{
	size_t	last_digit;

	if (!input)
		return (0);
	if (ft_count_numbers(input) > 19)
		return (1);
	else if (ft_count_numbers(input) == 19)
	{
		last_digit = ft_atoi(input + (ft_strlen(input) - 1));
		if (input[0] != 45)
		{
			if (ft_digits_check(input, last_digit, 0))
				return (1);
		}
		else if (input[0] == 45)
		{
			if (ft_digits_check(input + 1, last_digit, '-'))
				return (1);
		}
	}
	return (0);
}

int	ft_max_or_min_nbr(char *str)
{
	if (!str)
		return (0);
	if (ft_find_max_or_min_nbr(str))
		return (1);
	return (0);
}
